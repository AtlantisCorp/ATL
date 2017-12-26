//  ========================================================================  //
//
//  File    : ATL/RenderQueue.cpp
//  Project : atlresource
//  Author  : Luk2010
//  Date    : 17/10/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#include <ATL/RenderQueue.hpp>
#include <ATL/Context.hpp>
#include <ATL/Program.hpp>

namespace atl
{
    ////////////////////////////////////////////////////////////
    RenderQueue::RenderQueue( const Weak < Material >& material )
    : m_material( material )
    {
        
    }
    
    ////////////////////////////////////////////////////////////
    RenderQueue::~RenderQueue()
    {
        
    }
    
    ////////////////////////////////////////////////////////////
    const Weak < Material > RenderQueue::GetMaterial() const
    {
        return m_material ;
    }
    
    ////////////////////////////////////////////////////////////
    StaticRenderQueue::~StaticRenderQueue()
    {
        
    }
    
    ////////////////////////////////////////////////////////////
    RenderQueueCache StaticRenderQueue::GetCachePolicy() const
    {
        return RenderQueueCache::Static ;
    }
    
    ////////////////////////////////////////////////////////////
    void StaticRenderQueue::AddRenderCommand( const Weak < RenderCommand >& command )
    {
        assert( !command.expired() && "RenderCommand given expired." );
        MutexLocker lck( m_mutex );
        
        for ( auto it = m_commands.begin() ; it != m_commands.end() ; it++ )
        {
            if ( (*it).expired() ) {
                continue ;
            }
            
            else if ( (*it).lock() == command.lock() ) {
                m_commands.erase( it );
                break ;
            }
            
        }
        
        m_commands.push_back( command );
    }
    
    ////////////////////////////////////////////////////////////
    void StaticRenderQueue::AddRenderCommands( const WeakVector < RenderCommand >& commands )
    {
        for ( auto const& command : commands )
        {
            if ( command.expired() )
                continue ;
            
            AddRenderCommand( command );
        }
    }
    
    ////////////////////////////////////////////////////////////
    void StaticRenderQueue::Draw( const Context& context , const Program& program ) const
    {
        MutexLocker lck( m_mutex );
        
        for ( auto const& command : m_commands )
        {
            if ( command.expired() )
                continue ;
            
            auto scommand = command.lock();
            program.BindConstantParameters( scommand->GetConstParameters() );
            program.BindVaryingParameters( scommand->GetVarParameters() );
            context.DrawRenderCommand( command , program );
        }
    }
    
    ////////////////////////////////////////////////////////////
    DynamicRenderQueue::~DynamicRenderQueue()
    {
        
    }
    
    ////////////////////////////////////////////////////////////
    RenderQueueCache DynamicRenderQueue::GetCachePolicy() const
    {
        return RenderQueueCache::Dynamic ;
    }
    
    ////////////////////////////////////////////////////////////
    void DynamicRenderQueue::AddRenderCommand( const Weak < RenderCommand >& command )
    {
        assert( !command.expired() && "RenderCommand given expired." );
        Spinlocker lck( m_spinlock );
        m_commands.push_back( command );
    }
    
    ////////////////////////////////////////////////////////////
    void DynamicRenderQueue::AddRenderCommands( const WeakVector < RenderCommand >& commands )
    {
        Spinlocker lck( m_spinlock );
        
        for ( auto const& command : commands )
        {
            assert( !command.expired() && "RenderCommand in vector expired." );
            m_commands.push_back( command );
        }
    }
    
    ////////////////////////////////////////////////////////////
    void DynamicRenderQueue::Draw( const Context& context , const Program& program ) const
    {
        Spinlocker lck( m_spinlock );
        
        for ( auto const& command : m_commands )
        {
            if ( command.expired() )
                continue ;
            
            auto scommand = command.lock();
            program.BindConstantParameters( scommand->GetConstParameters() );
            program.BindVaryingParameters( scommand->GetVarParameters() );
            context.DrawRenderCommand( command , program );
        }
    }
    
    ////////////////////////////////////////////////////////////
    Shared < RenderQueue > CreateRenderQueue( const Weak < Material >& material , const RenderQueueCache& mode )
    {
        if ( mode == RenderQueueCache::Static )
            return std::make_shared < StaticRenderQueue >( material );
        else if ( mode == RenderQueueCache::Dynamic )
            return std::make_shared < DynamicRenderQueue >( material );
        
        return Shared < RenderQueue >();
    }
}
