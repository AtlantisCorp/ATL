//  ========================================================================  //
//
//  File    : ATL/VertexCommandVisitor.cpp
//  Project : atlresource
//  Author  : Luk2010
//  Date    : 18/11/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#include <ATL/VertexCommandVisitor.hpp>
#include <ATL/VertexCommand.hpp>

namespace atl
{
    ////////////////////////////////////////////////////////////
    VertexCommandVisitor::VertexCommandVisitor()
    {
        
    }
    
    ////////////////////////////////////////////////////////////
    void*& VertexCommandVisitor::GetContextData( const VertexCommand& command )
    {
        return command.m_ctxtdata ;
    }
    
    ////////////////////////////////////////////////////////////
    VertexCommandVisitor::~VertexCommandVisitor()
    {
        
    }
}
