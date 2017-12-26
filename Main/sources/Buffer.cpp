//  ========================================================================  //
//
//  File    : ATL/Buffer.cpp
//  Project : atlresource
//  Author  : Luk2010
//  Date    : 25/10/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#include <ATL/Buffer.hpp>

namespace atl
{
    ////////////////////////////////////////////////////////////
    IDGenerator < BufferId > Buffer::s_generator ;
    
    ////////////////////////////////////////////////////////////
    Buffer::Buffer() : m_id( s_generator.New() )
    {
        
    }
    
    ////////////////////////////////////////////////////////////
    Buffer::~Buffer()
    {
        
    }
}
