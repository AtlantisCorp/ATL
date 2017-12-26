//  ========================================================================  //
//
//  File    : ATL/Metaclass.hpp
//  Project : atlresource
//  Author  : Luk2010
//  Date    : 02/11/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#ifndef Metaclass_hpp
#define Metaclass_hpp

#include <ATL/StdIncludes.hpp>
#include <ATL/Resource.hpp>
#include <ATL/ErrorCenter.hpp>

namespace atl
{
    namespace Detail
    {
        ////////////////////////////////////////////////////////////
        struct IMetaclass
        {
            ////////////////////////////////////////////////////////////
            virtual ~IMetaclass()
            {
                
            }
            
            ////////////////////////////////////////////////////////////
            virtual MimeType GetMimeType() const = 0 ;
            
            ////////////////////////////////////////////////////////////
            Shared < Resource > Create()
            {
                return DCreate();
            }
            
            ////////////////////////////////////////////////////////////
            template < typename... Args >
            Shared < Resource > Create( bool reload , const String& file , Args&&... args )
            {
                constexpr int num = sizeof...( Args );
                return DCreate( reload , file , num , ( &args )... );
            }
            
            ////////////////////////////////////////////////////////////
            template < typename... Args >
            Shared < Resource > Create( const CBuffer& buf , Args&&... args )
            {
                constexpr int num = sizeof...( Args );
                return DCreate( buf , num , ( &args )... );
            }
            
            ////////////////////////////////////////////////////////////
            template < typename... Args >
            Shared < Resource > Create( std::istream& is , Args&&... args )
            {
                constexpr int num = sizeof...( Args );
                return DCreate( is , num , ( &args )... );
            }
            
        protected:
            
            ////////////////////////////////////////////////////////////
            virtual Shared < Resource > DCreate() { return nullptr ; }
            
            ////////////////////////////////////////////////////////////
            virtual Shared < Resource > DCreate( bool reload , const String& file , int num , ... ) { return nullptr ; }
            
            ////////////////////////////////////////////////////////////
            virtual Shared < Resource > DCreate( const CBuffer& buf , int num , ... ) { return nullptr ; }
            
            ////////////////////////////////////////////////////////////
            virtual Shared < Resource > DCreate( std::istream& is , int num , ... ) { return nullptr ; }
        };
        
        ////////////////////////////////////////////////////////////
        template < typename Class , typename Enable = void >
        Shared < Class > HelperCreate( int , ... )
        {
            return nullptr ;
        }
        
        ////////////////////////////////////////////////////////////
        template < typename Class ,
                   typename std::enable_if< std::is_default_constructible< Class >::value >::type* = nullptr >
        Shared < Class > HelperCreate( int , int )
        {
            return std::make_shared < Class >();
        }
        
        ////////////////////////////////////////////////////////////
        template < typename Class , typename Enable = void >
        Shared < Class > HelperCreate2( const String& , va_list& , ... )
        {
            return nullptr ;
        }
        
        ////////////////////////////////////////////////////////////
        template < typename Class ,
                   typename std::enable_if< std::is_constructible< Class , const String& , va_list& >::value >::type* = nullptr >
        Shared < Class > HelperCreate2( const String& f , va_list& args , int dummy )
        {
            return std::make_shared < Class >( f , args );
        }
        
        ////////////////////////////////////////////////////////////
        template < typename Class , typename Enable = void >
        Shared < Class > HelperCreate3( const CBuffer& , va_list& , ... )
        {
            return nullptr ;
        }
        
        ////////////////////////////////////////////////////////////
        template < typename Class ,
        typename std::enable_if< std::is_constructible< Class , const CBuffer& , va_list& >::value >::type* = nullptr >
        Shared < Class > HelperCreate3( const CBuffer& f , va_list& args , int dummy )
        {
            return std::make_shared < Class >( f , args );
        }
        
        ////////////////////////////////////////////////////////////
        template < typename Class , typename Enable = void >
        Shared < Class > HelperCreate4( std::istream& , va_list& , ... )
        {
            return nullptr ;
        }
        
        ////////////////////////////////////////////////////////////
        template < typename Class ,
                   typename std::enable_if< std::is_constructible< Class , std::istream& , va_list& >::value >::type* = nullptr >
        Shared < Class > HelperCreate4( std::istream& is , va_list& args , int dummy )
        {
            return std::make_shared < Class >( is , args );
        }
    }
    
    ////////////////////////////////////////////////////////////
    /// \brief Represents a metaclass englobing an external resource
    /// object, loaded from a plugin (generally).
    ///
    /// A Metaclass can create and give type informations about externally
    /// loaded types for a given MIME type. A Resource should always implement
    /// two constructors to be stored in a metaclass.
    ///
    /// The Metaclass is stored in the Metaclasser manager, which use the
    /// interface 'Detail::IMetaclass' to store and let the user access
    /// them. You are heavily recommended to use the 'auto' keyword
    /// to use metaclasses returned by the Metaclasser, as their type
    /// are 'Detail::IMetaclass*'.
    ///
    /// All protected 'DCreate' functions are enabled only if constructors
    /// are detected in the given derived class. This way, you can declare only
    /// the constructor you want in the derived resource class. 
    ///
    ////////////////////////////////////////////////////////////
    template < typename Class >
    class Metaclass : public Detail::IMetaclass
    {
        ////////////////////////////////////////////////////////////
        MimeType                           m_mime ;     ///< MIME type for this class.
        mutable Spinlock                   m_spinlock ; ///< Spinlock to access the MIME type.
        Map < String , Weak < Resource > > m_lastfile ; ///< Retain resource weak pointer for file loaded.
        
    public:
        
        ////////////////////////////////////////////////////////////
        Metaclass()
        {
           
        }
        
        ////////////////////////////////////////////////////////////
        Metaclass( const MimeType& mime ) : m_mime( mime )
        {
            
        }
        
        ////////////////////////////////////////////////////////////
        ~Metaclass()
        {
            
        }
        
        ////////////////////////////////////////////////////////////
        MimeType GetMimeType() const
        {
            Spinlocker lck( m_spinlock );
            return m_mime ;
        }
        
    protected:
        
        ////////////////////////////////////////////////////////////
        Shared < Resource > DCreate()
        {
            try
            {
                return std::static_pointer_cast< Resource >( Detail::HelperCreate< Class >( int{} , int{} ) );
            }
            
            catch( const std::exception& exception )
            {
                ErrorCenter::CatchException( exception ,
                                             Error::MetaclassCreate ,
                                             "Catched exception while defaulting class '%s'." ,
                                             typeid( Class ).name() );
                
                return nullptr ;
            }
        }
        
        ////////////////////////////////////////////////////////////
        Shared < Resource > DCreate( bool reload , const String& file , int num , ... )
        {
            try
            {
                Spinlocker lck( m_spinlock );
                auto it = m_lastfile.find( file );
                
                if ( it == m_lastfile.end() || it->second.expired() || reload )
                {
                    va_list args ;
                    va_start( args , num );
                    
                    auto sptr = Detail::HelperCreate2 < Class >( file , args , int{} );
                    
                    va_end( args );
                    m_lastfile[file] = std::static_pointer_cast< Resource >( sptr );
                    return std::static_pointer_cast< Resource >( sptr );
                }
                
                else
                {
                    return it->second.lock();
                }
            }
            
            catch( const std::exception& exception )
            {
                ErrorCenter::CatchException( exception ,
                                             Error::MetaclassCreate ,
                                             "Catched exception while creating class '%s'." ,
                                             typeid( Class ).name() );
                
                return nullptr ;
            }
        }
        
        ////////////////////////////////////////////////////////////
        Shared < Resource > DCreate( const CBuffer& buf , int num , ... )
        {
            try
            {
                va_list args ;
                va_start( args , num );
                
                auto sptr = Detail::HelperCreate3 < Class >( buf , args , int{} );
                
                va_end( args );
                
                return std::static_pointer_cast < Resource >( sptr );
            }
            
            catch( const std::exception& exception )
            {
                ErrorCenter::CatchException( exception ,
                                             Error::MetaclassCreate ,
                                             "Catched exception while creating class '%s'." ,
                                             typeid( Class ).name() );
                
                return nullptr ;
            }
        }
        
        ////////////////////////////////////////////////////////////
        Shared < Resource > DCreate( std::istream& is , int num , ... )
        {
            try
            {
                va_list args ;
                va_start( args , num );
                auto sptr = Detail::HelperCreate4 < Class >( is , args , int{} );
                va_end( args );
                
                return std::static_pointer_cast < Resource >( sptr );
            }
            
            catch( const std::exception& exception )
            {
                ErrorCenter::CatchException( exception ,
                                             Error::MetaclassCreate ,
                                             "Catched exception while creating class '%s'." ,
                                             typeid( Class ).name() );
                
                return nullptr ;
            }
        }
    };
    
    ////////////////////////////////////////////////////////////
    /// \brief Helper to create a new Metaclass for given type, with
    /// its MIME type.
    ///
    /// \return A std::unique_ptr representing the metaclass. It should
    /// be immediatly added to the Metaclasser by the plugin/user before
    /// using it.
    ///
    ////////////////////////////////////////////////////////////
    template < class Class >
    Unique < Metaclass < Class > > CreateMetaclass( const MimeType& mime )
    {
        return atl::make_unique < Metaclass < Class > >( mime );
    }
    
    ////////////////////////////////////////////////////////////
    /// \brief Creates the same object as 'CreateMetaclass' but with
    /// a class that has a 's_mime' static object representing the
    /// MIME type associated to this Metaclass.
    ///
    ////////////////////////////////////////////////////////////
    template < class Class >
    Unique < Metaclass < Class > > CreateMetaclassS( void )
    {
        return CreateMetaclass < Class >( Class :: s_mime );
    }
}

////////////////////////////////////////////////////////////
/// \brief Returns the next argument as given type, when called
/// from a Metaclass'ed object.
///
/// Object created with Metaclass see their arguments given always
/// as pointer to the base type, to ensure non-POD types are well
/// transmitted. Those types can be converted implicitely into references
/// if necessary.
///
////////////////////////////////////////////////////////////
#define AtlMetaArg( type ) * ( va_arg( args , type * ) )

#endif /* Metaclass_hpp */
