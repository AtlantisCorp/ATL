//  ========================================================================  //
//
//  File    : ATL/Manager.hpp
//  Project : atlresource
//  Author  : Luk2010
//  Date    : 14/11/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#ifndef Manager_hpp
#define Manager_hpp

#include <ATL/Instanced.hpp>
#include <ATL/Metaclass.hpp>
#include <ATL/ManagerEvent.hpp>

#include <ATL/MimeDatabase.hpp>
#include <ATL/Metaclasser.hpp>

namespace atl
{
    ////////////////////////////////////////////////////////////
    /// \brief Manages several Resource's lifetime.
    ///
    /// For a category of Resource, like Material or Texture, a Manager
    /// is available to manage them in one place. If you want to create
    /// your own manager for a custom resource, derive from this class.
    /// Wether creator is available depends on the Resource managed,
    /// conformly to Metaclass. However, as a Manager does not know the
    /// derived type, only the blank constructor and the constructor from
    /// a file are supported.
    ///
    /// A Manager also inform its listeners when a resource is added
    /// or released from it, by using ManagerCreateEvent and
    /// ManagerReleaseEvent.
    ///
    /// \see Metaclass , Resource
    ///
    ////////////////////////////////////////////////////////////
    template < typename Class >
    class Manager : public Instanced < Manager < Class > > , public Emitter
    {
        ////////////////////////////////////////////////////////////
        SharedVector < Class > m_objs ; ///< Objects loaded by this manager.
        mutable Mutex          m_mutex ; ///< Mutex to access data.
        
    protected:
        
        ////////////////////////////////////////////////////////////
        Manager() { }
        
        ////////////////////////////////////////////////////////////
        virtual ~Manager() { }
        
        ////////////////////////////////////////////////////////////
        /// \brief Find the MIME type for given file, or return an
        /// empty MIME type.
        ///
        /// \internal
        ////////////////////////////////////////////////////////////
        const MimeType pFindFileMime( const String& file )
        {
            auto mimemanager = MimeDatabase::Get();
            assert( mimemanager && "No MIME Manager installed." );
            return mimemanager->FindHigherForFile( file );
        }
        
        ////////////////////////////////////////////////////////////
        /// \brief Find the Detail::IMetaclass interface pointer for
        /// the given MIME type or null if it can't be found.
        ///
        ////////////////////////////////////////////////////////////
        Detail::IMetaclass* pFindMetaclass( const MimeType& mime )
        {
            auto metaclasser = Metaclasser::Get();
            assert( metaclasser && "No Metaclasser installed." );
            return metaclasser->GetMetaclass( mime );
        }
        
    public:
        
        ////////////////////////////////////////////////////////////
        Weak < Class > Create()
        {
            auto sptr = std::static_pointer_cast < Class >( Metaclass < Class >().Create() );
            
            if ( sptr )
            {
                MutexLocker lck( m_mutex );
                m_objs.push_back( sptr );
                
                SendEvent < ManagerCreateEvent >( sptr->GetId() );
            }
            
            return sptr ;
        }
        
        ////////////////////////////////////////////////////////////
        template < typename... Args >
        Weak < Class > Create( bool reload , const String& file , Args&&... args )
        {
            if ( !reload )
            {
                MutexLocker lck( m_mutex );
                auto it = std::find_if( m_objs.begin() , m_objs.end() , [file]( const Shared < Class >& obj ) -> bool {
                    return obj ? obj->GetFile() == file : false ;
                });
                
                if ( it != m_objs.end() )
                    return (*it);
            }
            
            auto mimetype = pFindFileMime( file );
            if ( mimetype.IsEmpty() )
                return Weak < Class >();
            
            auto metaclass = pFindMetaclass( mimetype );
            if ( !metaclass )
                return Weak < Class >();
            
            auto sptr = std::static_pointer_cast < Class >( metaclass->Create( reload , file , std::forward < Args >( args )... ) );
            
            if ( sptr )
            {
                MutexLocker lck( m_mutex );
                m_objs.push_back( sptr );
                
                SendEvent < ManagerCreateEvent >( sptr->GetId() ,
                                                  sptr->GetFile() );
            }
            
            return sptr ;
        }
        
        ////////////////////////////////////////////////////////////
        void Release( const Weak < Class >& object )
        {
            MutexLocker lck( m_mutex );
            auto sptr = object.lock();
            auto it   = std::find( m_objs.begin() , m_objs.end() , sptr );
            
            if ( it != m_objs.end() )
            {
                SendEvent < ManagerReleaseEvent >( sptr->GetId() );
                m_objs.erase( it );
            }
        }
    };
}

#endif /* Manager_hpp */
