//  ========================================================================  //
//
//  File    : ATL/Metaclasser.hpp
//  Project : atlresource
//  Author  : Luk2010
//  Date    : 02/11/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#ifndef Metaclasser_hpp
#define Metaclasser_hpp

#include <ATL/Instanced.hpp>
#include <ATL/Metaclass.hpp>

namespace atl
{
    ////////////////////////////////////////////////////////////
    /// \brief Organize Metaclasses upon MIME types.
    ///
    ////////////////////////////////////////////////////////////
    class Metaclasser : public Instanced < Metaclasser >
    {
        ////////////////////////////////////////////////////////////
        UniqueVector < Detail::IMetaclass >    m_metaclasses ; ///< List of metaclasses.
        Map < MimeType , Detail::IMetaclass* > m_metabymime ;  ///< Maps metaclasses by MIME types.
        mutable Mutex                          m_mutex ;       ///< Access datas.
        
    public:
        
        ////////////////////////////////////////////////////////////
        Metaclasser();
        
        ////////////////////////////////////////////////////////////
        virtual ~Metaclasser();
        
        ////////////////////////////////////////////////////////////
        virtual Detail::IMetaclass* GetMetaclass( const MimeType& mime );
        
        ////////////////////////////////////////////////////////////
        virtual const Detail::IMetaclass* GetMetaclass( const MimeType& mime ) const ;
        
        ////////////////////////////////////////////////////////////
        /// \brief Registers a newly created metaclass pointer to the
        /// Metaclasser. Given unique pointer is released in the operation
        /// and holds a null pointer at the end of the process.
        ///
        ////////////////////////////////////////////////////////////
        template < typename DMetaclass >
        void RegisterMetaclass( Unique < DMetaclass >& sptr )
        {
            MutexLocker lck( m_mutex );
            assert( sptr && "'sptr' is invalid." );
            
            MimeType mime = sptr->GetMimeType();
            std::unique_ptr < Detail::IMetaclass > tmp( static_cast < Detail::IMetaclass* >( sptr.release() ) );
            
            m_metabymime[mime] = tmp.get();
            m_metaclasses.push_back( std::move( tmp ) );
        }
        
        ////////////////////////////////////////////////////////////
        /// \brief Creates a Metaclass with 'CreateMetaclass' and registers
        /// it to the Metaclasser.
        ///
        ////////////////////////////////////////////////////////////
        template < class Class >
        void CreateAndRegister( const MimeType& mime )
        {
            auto sptr = CreateMetaclass < Class >( mime );
            return RegisterMetaclass( sptr );
        }
        
        ////////////////////////////////////////////////////////////
        /// \brief Creates a Metaclass with 'CreateMetaclassS' and registers
        /// it to the Metaclasser.
        ///
        ////////////////////////////////////////////////////////////
        template < class Class >
        void CreateAndRegister( void )
        {
            auto sptr = CreateMetaclassS < Class >();
            return RegisterMetaclass( sptr );
        }
    };
}

#endif /* Metaclasser_hpp */
