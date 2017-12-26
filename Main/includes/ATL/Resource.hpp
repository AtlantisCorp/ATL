//  ========================================================================  //
//
//  File    : ATL/Resource.hpp
//  Project : atlresource
//  Author  : Luk2010
//  Date    : 16/09/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#ifndef Resource_hpp
#define Resource_hpp

#include <ATL/StdIncludes.hpp>
#include <ATL/MimeType.hpp>
#include <ATL/IDGenerator.hpp>
#include <ATL/CBuffer.hpp>

namespace atl
{
    ////////////////////////////////////////////////////////////
    typedef unsigned long long ResourceId ;

    ////////////////////////////////////////////////////////////
    /// \brief Describes an interface to access physical files loaded
    /// as structures, as Shaders, Textures, etc.
    ///
    /// A Resource is always associated to a MIME type and a physical
    /// file. The MIME type is found upon request to the MIME type
    /// manager, or is given by the user. The File is given by the user,
    /// but a Resource might be loaded also from a raw buffer containing
    /// the same informations.
    ///
    /// A Resource is created from a Metaclass object, that acts as a
    /// factory to create the resource. In order to conform to the
    /// Metaclass creation process (and to simplify Metaclass implementation),
    /// it was decided Resource can implement four constructors:
    /// - Resource( void )
    /// - Resource( const String& , va_list& )
    /// - Resource( const CBuffer < char >& , va_list& )
    /// - Resource( const std::istream& , va_list& )
    ///
    /// Each constructor is optional but at least one of those must be present
    /// for the metaclass to be usable. 'va_list' holds always the same pattern
    /// of arguments: a list of void* pointers. When creating the resource using
    /// the Metaclass subsystem, 'IMetaclass::DCreate()' convert every variadic
    /// arguments into pointers and that is what is passed to the resource
    /// constructor. Imagine you use the following:
    ///
    /// auto myresource = mymeta->Create( 5, "blah", my_shared_class );
    ///
    /// 'va_list' will hold the following objects: 'int*', 'const char**', and
    /// 'Shared < Class >*'. Think about this when converting those parameters
    /// by using 'va_arg'. This convertion is needed as C-style variadics needs
    /// non-POD types (which pointers are all naturally) and C++11 variadic templates
    /// captures the passed object natural type. Notes also that references are not
    /// conserved and thus types as 'const String&*' are converted into 'const String*'.
    ///
    /// Derived of Resource should use wisely the 'va_list&' argument as it
    /// may not provide correct arguments or corrupted memories.
    /// Also, notes that default implementation does nothing, as argument
    /// order matter. It is the derived object that should implement those
    /// constructors to manage argument in the order they want to.
    ///
    ////////////////////////////////////////////////////////////
    class Resource
    {
        ////////////////////////////////////////////////////////////
        static IDGenerator < ResourceId > s_generator ;
        
        ////////////////////////////////////////////////////////////
        Atomic < ResourceId > m_id ;       ///< Local resource ID.
        MimeType              m_mimetype ; ///< Mimetype associated to this resource.
        String                m_file ;     ///< File associated to this resource, or empty if it was loaded from a buffer.
        mutable Spinlock      m_spinlock ; ///< Access to data. 
        
    public:
        
        ////////////////////////////////////////////////////////////
        Resource( void );
        
        ////////////////////////////////////////////////////////////
        Resource( va_list& args );
        
        ////////////////////////////////////////////////////////////
        Resource( const String& file , va_list& args );
        
        ////////////////////////////////////////////////////////////
        Resource( const CBuffer& buf , va_list& args );
        
    protected:
        
        ////////////////////////////////////////////////////////////
        Resource( const String& file , const MimeType& mime );
        
    public:
        
        ////////////////////////////////////////////////////////////
        virtual ~Resource();
        
        ////////////////////////////////////////////////////////////
        virtual ResourceId GetId() const ;
        
        ////////////////////////////////////////////////////////////
        virtual MimeType GetMimeType() const ;
        
        ////////////////////////////////////////////////////////////
        virtual String GetFile() const ;
    };
}

#endif /* Resource_hpp */
