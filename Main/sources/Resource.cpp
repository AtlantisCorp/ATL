//  ========================================================================  //
//
//  File    : ATL/Resource.cpp
//  Project : atlresource
//  Author  : Luk2010
//  Date    : 16/09/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#include <ATL/Resource.hpp>

namespace atl
{
    ////////////////////////////////////////////////////////////
    IDGenerator < ResourceId > Resource::s_generator ;
    
    ////////////////////////////////////////////////////////////
    Resource::Resource( void ) : m_id( s_generator.New() )
    {
        
    }
    
    ////////////////////////////////////////////////////////////
    Resource::Resource( va_list& args ) : m_id( s_generator.New() )
    {
        
    }
    
    ////////////////////////////////////////////////////////////
    Resource::Resource( const String& file , va_list& args ) : m_id( s_generator.New() )
    {
        
    }
    
    ////////////////////////////////////////////////////////////
    Resource::Resource( const CBuffer& buf , va_list& args ) : m_id( s_generator.New() )
    {
        
    }
    
    ////////////////////////////////////////////////////////////
    Resource::Resource( const String& file , const MimeType& mime ) : m_id( s_generator.New() ) , m_mimetype( mime ) , m_file( file )
    {
        
    }
    
    ////////////////////////////////////////////////////////////
    Resource::~Resource()
    {
        
    }
    
    ////////////////////////////////////////////////////////////
    ResourceId Resource::GetId() const
    {
        return m_id.load();
    }
    
    ////////////////////////////////////////////////////////////
    MimeType Resource::GetMimeType() const
    {
        Spinlocker lck( m_spinlock );
        return m_mimetype ;
    }
    
    ////////////////////////////////////////////////////////////
    String Resource::GetFile() const
    {
        Spinlocker lck( m_spinlock );
        return m_file ;
    }
}
