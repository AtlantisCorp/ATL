//  ========================================================================  //
//
//  File    : ATL/Context.cpp
//  Project : atlresource
//  Author  : Luk2010
//  Date    : 25/09/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#include <ATL/Context.hpp>
#include <ATL/RenderCommand.hpp>
#include <ATL/Program.hpp>

namespace atl
{
    ////////////////////////////////////////////////////////////
    Context::Context()
    {

    }

    ////////////////////////////////////////////////////////////
    Context::~Context()
    {
        
    }
    
    ////////////////////////////////////////////////////////////
    void Context::DrawRenderCommand( const Weak < RenderCommand >& command , const Program& program ) const
    {
        assert( !command.expired() && "'command' expired." );
        auto vertexcommands = command.lock()->GetVertexCommands();
        
        for ( auto const& vcommand : vertexcommands )
        {
            DrawVertexCommand( vcommand , program );
        }
    }
}
