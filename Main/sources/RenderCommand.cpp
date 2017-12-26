//  ========================================================================  //
//
//  File    : ATL/RenderCommand.cpp
//  Project : atlresource
//  Author  : Luk2010
//  Date    : 28/10/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#include <ATL/RenderCommand.hpp>
#include <ATL/Material.hpp>
#include <ATL/Program.hpp>
#include <ATL/RenderCommandGroup.hpp>

namespace atl
{
    ////////////////////////////////////////////////////////////
    IDGenerator < RenderCommandId > RenderCommand::s_generator ;
    
    ////////////////////////////////////////////////////////////
    RenderCommand::RenderCommand() : m_id( s_generator.New() )
    {
        
    }
    
    ////////////////////////////////////////////////////////////
    RenderCommand::RenderCommand( const Shared < VertexCommand >& command ,
                                  const Weak < Material >& material ,
                                  const Weak < Program >& program )
    : m_id( s_generator.New() ) , m_material( material ) , m_program( program )
    {
        m_commands.push_back( command );
    }
    
    ////////////////////////////////////////////////////////////
    RenderCommand::RenderCommand( const SharedVector < VertexCommand >& commands ,
                                  const Weak < Material >& material ,
                                  const Weak < Program >& program )
    : m_id( s_generator.New() ) , m_commands( commands ) , m_material( material ) , m_program( program )
    {
        
    }
    
    ////////////////////////////////////////////////////////////
    RenderCommand::~RenderCommand()
    {
        
    }
    
    ////////////////////////////////////////////////////////////
    RenderCommandId RenderCommand::GetId() const
    {
        return m_id.load();
    }
    
    ////////////////////////////////////////////////////////////
    void RenderCommand::AddVertexCommand( const Shared < VertexCommand >& command )
    {
        MutexLocker lck( m_mutex );
        m_commands.push_back( command );
    }
    
    ////////////////////////////////////////////////////////////
    void RenderCommand::AddVertexCommands( const SharedVector < VertexCommand >& commands )
    {
        MutexLocker lck( m_mutex );
        m_commands.insert( m_commands.end() , commands.begin() , commands.end() );
    }
    
    ////////////////////////////////////////////////////////////
    void RenderCommand::ResetVertexCommands()
    {
        MutexLocker lck( m_mutex );
        m_commands.clear();
    }
    
    ////////////////////////////////////////////////////////////
    Weak < Material > RenderCommand::GetMaterial() const
    {
        return m_material ;
    }
    
    ////////////////////////////////////////////////////////////
    Weak < Program > RenderCommand::GetProgram() const
    {
        return m_program ;
    }
    
    ////////////////////////////////////////////////////////////
    Weak < RenderCommandGroup > RenderCommand::GetParentGroup() const
    {
        return m_parentgroup ;
    }
    
    ////////////////////////////////////////////////////////////
    void RenderCommand::SetProgram( const Weak < Program >& program )
    {
        m_program = program ;
    }
    
    ////////////////////////////////////////////////////////////
    SharedVector < VertexCommand > RenderCommand::GetVertexCommands() const
    {
        MutexLocker lck( m_mutex );
        return m_commands ;
    }
}
