//  ========================================================================  //
//
//  File    : ATL/VertexLayout.cpp
//  Project : atlresource
//  Author  : Luk2010
//  Date    : 13/11/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#include <ATL/VertexLayout.hpp>

namespace atl
{
    ////////////////////////////////////////////////////////////
    VertexLayout::VertexLayout()
    {
        
    }
    
    ////////////////////////////////////////////////////////////
    VertexLayout::VertexLayout( const Vector < VertexAttrib >& attribs )
    : m_attribs( attribs )
    {
        
    }
    
    ////////////////////////////////////////////////////////////
    VertexLayout::~VertexLayout()
    {
        
    }
    
    ////////////////////////////////////////////////////////////
    bool VertexLayout::SetAttribute( Attribute attribute , uint32_t slot , uint32_t type )
    {
        MutexLocker lck( m_mutex );
        
        auto it = std::find_if( m_attribs.begin() , m_attribs.end() ,
                                [slot](const VertexAttrib& attrib) -> bool { return attrib.GetSlot() == slot ; });
        
        if ( it == m_attribs.end() )
            return false ;
        
        if ( type && (*it).GetType() != type )
            return false ;
        
        m_attribsbyalias[attribute] = &(*it);
        return true ;
    }
    
    ////////////////////////////////////////////////////////////
    bool VertexLayout::SetAttribute( Attribute attribute , const String& name , uint32_t type )
    {
        MutexLocker lck( m_mutex );
        
        auto it = std::find_if( m_attribs.begin() , m_attribs.end() ,
                               [name](const VertexAttrib& attrib) -> bool { return attrib.GetName() == name ; });
        
        if ( it == m_attribs.end() )
            return false ;
        
        if ( type && (*it).GetType() != type )
            return false ;
        
        m_attribsbyalias[attribute] = &(*it);
        return true ;
    }
    
    ////////////////////////////////////////////////////////////
    const VertexAttrib* VertexLayout::GetAttribute( Attribute attribute ) const
    {
        MutexLocker lck( m_mutex );
        auto it = m_attribsbyalias.find( attribute );
        
        if ( it == m_attribsbyalias.end() )
            return nullptr ;
        
        return it->second ;
    }
    
    ////////////////////////////////////////////////////////////
    void VertexLayout::AddVertexAttrib( const VertexAttrib& attrib )
    {
        MutexLocker lck( m_mutex );
        m_attribs.push_back( attrib );
    }
}
