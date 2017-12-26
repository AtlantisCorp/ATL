//  ========================================================================  //
//
//  File    : Gl3Driver/main.cpp
//  Project : ATL/Gl3Driver
//  Author  : Luk2010
//  Date    : 15/10/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#include <Gl3Driver/Gl3Driver.h>
#include <Gl3Driver/Gl3VertexShader.h>
#include <Gl3Driver/Gl3FragmentShader.h>
#include <ATL/Root.hpp>

////////////////////////////////////////////////////////////
extern "C" void StartPlugin( void )
{
    auto& root = atl::Root::Get();
    
    auto plugin = std::make_shared < Plugin >();
    plugin->SetAuthor( "Luk2010" );
    plugin->SetDesc( "OpenGL3 Driver plugin." );
    plugin->SetName( "Gl3Driver" );
    
    root.GetMetaclasser().lock()->CreateAndRegister < Gl3VertexShader >();
    plugin->AddMimeType( Gl3VertexShader::s_mime );
    
    root.GetMetaclasser().lock()->CreateAndRegister < Gl3FragmentShader >();
    plugin->AddMimeType( Gl3FragmentShader::s_mime );
    
    root.InstallPlugin( plugin );
    
    auto gldriver = std::make_shared < Gl3Driver >();
    assert( gldriver && "Can't allocate Gl3Driver." );
    root.InstallDriver( gldriver );
    
    root.GetLogger().info( "Gl3Driver Plugin - Started." );
}
