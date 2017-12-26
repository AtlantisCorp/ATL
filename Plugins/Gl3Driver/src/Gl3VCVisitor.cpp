//  ========================================================================  //
//
//  File    : Gl3Driver/Gl3VCVisitor.cpp
//  Project : ATL/Gl3Driver
//  Author  : Luk2010
//  Date    : 18/11/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#include <Gl3Driver/Gl3VCVisitor.h>
#include <Gl3Driver/Gl3Context.h>
#include <ATL/VertexCommand.hpp>
using namespace atl ;

////////////////////////////////////////////////////////////
Gl3VAOGetterVisitor::Gl3VAOGetterVisitor() : VAO( 0 )
{
    
}

////////////////////////////////////////////////////////////
void Gl3VAOGetterVisitor::Visit( const VertexCommand& command )
{
    VAO = static_cast < GLuint* >( GetContextData( command ) );
}

////////////////////////////////////////////////////////////
Gl3VAOSetterVisitor::Gl3VAOSetterVisitor( GLuint* vao ) : VAO( vao )
{
    
}

////////////////////////////////////////////////////////////
void Gl3VAOSetterVisitor::Visit( const VertexCommand& command )
{
    GetContextData( command ) = static_cast < void* >( VAO );
}
