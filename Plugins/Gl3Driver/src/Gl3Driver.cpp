//  ========================================================================  //
//
//  File    : Gl3Driver/Gl3Driver.cpp
//  Project : ATL/Gl3Driver
//  Author  : Luk2010
//  Date    : 15/10/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#include <Gl3Driver/Gl3Driver.h>
#include <Gl3Driver/Gl3Context.h>

////////////////////////////////////////////////////////////
Gl3Driver::Gl3Driver()
{
    
}

////////////////////////////////////////////////////////////
Gl3Driver::~Gl3Driver()
{
    
}

////////////////////////////////////////////////////////////
String Gl3Driver::GetName() const
{
    return "Gl3Driver" ;
}

////////////////////////////////////////////////////////////
Weak < RenderWindow > Gl3Driver::CreateRenderWindow( const Weak < Surface >& surface , const ContextSettings& settings )
{
    auto context = std::make_shared < Gl3Context >( surface , settings );
    assert( context && "Invalid Gl3Context creation." );
    
    auto renderwindow = std::make_shared < RenderWindow >( surface , context );
    assert( renderwindow && "Invalid RenderWindow creation." );
    
    Driver::AddRenderWindow( renderwindow );
    return renderwindow ;
}

////////////////////////////////////////////////////////////
void Gl3Driver::DrawVertexCommand( const Weak < VertexCommand >& command ) const
{
    
}

////////////////////////////////////////////////////////////
void Gl3Driver::DrawRenderCommand( const Weak < RenderCommand >& command , const Program& program ) const
{
    
}

