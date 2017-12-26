//  ========================================================================  //
//
//  File    : OSXWindow/main.cpp
//  Project : ATL/OSXWindow
//  Author  : Luk2010
//  Date    : 09/10/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#include <OSXWindow/OSXSurfacer.h>
#include <ATL/Root.hpp>

////////////////////////////////////////////////////////////
extern "C" void StartPlugin( void )
{
    auto& root = atl::Root::Get();
    
    auto osxsurfacer = std::make_shared < OSXSurfacer >();
    assert( osxsurfacer && "Can't allocate OSXSurfacer." );
    root.InstallSurfacer( osxsurfacer );
    
    root.GetLogger().info( "OSXWindow - Plugin started." );
}
