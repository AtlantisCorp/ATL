//  ========================================================================  //
//
//  File    : ATL/VertexAttrib.cpp
//  Project : atlresource
//  Author  : Luk2010
//  Date    : 13/11/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#include <ATL/VertexAttrib.hpp>

namespace atl
{
    ////////////////////////////////////////////////////////////
    VertexAttrib::VertexAttrib( uint32_t slot , const String& name , uint32_t type )
    : m_slot( slot ) , m_type( type ) , m_name( name )
    {
        
    }
    
    ////////////////////////////////////////////////////////////
    VertexAttrib::VertexAttrib( const VertexAttrib& rhs )
    : m_slot( rhs.m_slot.load() ) , m_type( rhs.m_type.load() ) , m_name( rhs.m_name )
    {
        
    }
    
    ////////////////////////////////////////////////////////////
    VertexAttrib::~VertexAttrib()
    {
        
    }
    
    ////////////////////////////////////////////////////////////
    uint32_t VertexAttrib::GetSlot() const
    {
        return m_slot.load();
    }
    
    ////////////////////////////////////////////////////////////
    uint32_t VertexAttrib::GetType() const
    {
        return m_type.load();
    }
    
    ////////////////////////////////////////////////////////////
    String VertexAttrib::GetName() const
    {
        Spinlocker lck( m_spinlock );
        return m_name ;
    }
}
