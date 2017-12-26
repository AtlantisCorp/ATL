//  ========================================================================  //
//
//  File    : ATL/Object.cpp
//  Project : atlresource
//  Author  : Luk2010
//  Date    : 20/10/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#include <ATL/Object.hpp>
#include <ATL/ObjectGroup.hpp>

namespace atl
{
    ////////////////////////////////////////////////////////////
    IDGenerator < ObjectId > Object::s_generator ;
    
    ////////////////////////////////////////////////////////////
    Object::Object() : m_id( s_generator.New() )
    {
        
    }
    
    ////////////////////////////////////////////////////////////
    Object::~Object()
    {
        
    }
    
    ////////////////////////////////////////////////////////////
    ObjectId Object::GetId() const
    {
        return m_id.load();
    }
    
    ////////////////////////////////////////////////////////////
    Weak < ObjectGroup > Object::GetGroup() const
    {
        return m_group ;
    }
    
    ////////////////////////////////////////////////////////////
    void Object::SetGroup( const Weak < ObjectGroup >& group )
    {
        m_group = group ;
    }
}
