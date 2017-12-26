//  ========================================================================  //
//
//  File    : ATL/Renderable.cpp
//  Project : atlresource
//  Author  : Luk2010
//  Date    : 21/10/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#include <ATL/Renderable.hpp>

namespace atl
{
    ////////////////////////////////////////////////////////////
    Renderable::Renderable() : m_dirty( false )
    {
        
    }
    
    ////////////////////////////////////////////////////////////
    Renderable::~Renderable()
    {
        
    }
    
    ////////////////////////////////////////////////////////////
    Weak < VertexCommand > Renderable::CreateAndAddVertexCommand()
    {
        auto command = std::make_shared < VertexCommand >();
        AddVertexCommand( command );
        return command ;
    }
    
    ////////////////////////////////////////////////////////////
    void Renderable::AddVertexCommand( const Shared < VertexCommand >& command )
    {
        if ( command )
        {
            MutexLocker lck( m_mutex );
            m_commands.push_back( command );
        }
    }
    
    ////////////////////////////////////////////////////////////
    void Renderable::RemoveVertexCommand( const Weak < VertexCommand >& command )
    {
        if ( command.expired() )
            return ;
        
        MutexLocker lck( m_mutex );
        auto it = std::find( m_commands.begin() , m_commands.end() , command.lock() );
        
        if ( it != m_commands.end() )
            m_commands.erase( it );
    }
    
    ////////////////////////////////////////////////////////////
    void Renderable::RemoveVertexCommand( const VertexCommandId& id )
    {
        MutexLocker lck( m_mutex );
        
        for ( auto it = m_commands.begin() ; it != m_commands.end() ; it++ )
        {
            if ( (*it)->GetId() == id )
            {
                m_commands.erase( it );
                break ;
            }
        }
    }
    
    ////////////////////////////////////////////////////////////
    Weak < VertexCommand > Renderable::GetVertexCommand( const VertexCommandId& id ) const
    {
        MutexLocker lck( m_mutex );
        
        for ( auto const& command : m_commands )
        {
            if (command->GetId() == id )
                return command;
        }
        
        return Weak < VertexCommand >();
    }
    
    ////////////////////////////////////////////////////////////
    SharedVector < VertexCommand > Renderable::CopyVertexCommands() const
    {
        SharedVector < VertexCommand > retvalue ;
        
        {
            MutexLocker lck( m_mutex );
            retvalue = m_commands ;
        }
        
        return retvalue ;
    }
}
