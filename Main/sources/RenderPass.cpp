//  ========================================================================  //
//
//  File    : ATL/RenderPass.cpp
//  Project : atlresource
//  Author  : Luk2010
//  Date    : 17/10/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#include <ATL/RenderPass.hpp>
#include <ATL/Context.hpp>

namespace atl
{
    ////////////////////////////////////////////////////////////
    IDGenerator < RenderPassId > RenderPass::s_generator ;
    
    ////////////////////////////////////////////////////////////
    RenderPass::RenderPass( const Weak < Program >& program )
    : m_id( s_generator.New() ) , m_program( program )
    {
        
    }
    
    ////////////////////////////////////////////////////////////
    RenderPass::~RenderPass()
    {
        
    }
    
    ////////////////////////////////////////////////////////////
    RenderPassId RenderPass::GetId() const
    {
        return m_id.load();
    }
    
    ////////////////////////////////////////////////////////////
    const Weak < Program > RenderPass::GetProgram() const
    {
        return m_program ;
    }
    
    ////////////////////////////////////////////////////////////
    void RenderPass::Draw( const Context& context , const Program& program ) const
    {
        m_mutex.lock();
        auto staticqueues = m_staticqueues ;
        m_mutex.unlock();
        
        for ( auto queue : staticqueues )
        {
            auto material = queue->GetMaterial();
            if ( material.expired() )
                continue ;
            
            material.lock()->Prepare( program );
            queue->Draw( context , program );
        }
        
        m_mutex.lock();
        auto dynamicqueues = m_dynamicqueues ;
        m_mutex.unlock();
        
        for ( auto queue : dynamicqueues )
        {
            auto material = queue->GetMaterial();
            if ( material.expired() )
                continue ;
            
            material.lock()->Prepare( program );
            queue->Draw( context , program );
        }
    }
    
    ////////////////////////////////////////////////////////////
    void RenderPass::_ResetDynamicRenderQueues()
    {
        MutexLocker lck( m_mutex );
        m_dynamicqueues.clear();
    }
    
    ////////////////////////////////////////////////////////////
    void RenderPass::AddRenderCommand( const Weak < Material >& material , const Weak < RenderCommand >& command , const RenderQueueCache& mode )
    {
        assert( !material.expired() && "Material given expired." );
        assert( !command.expired() && "RenderCommand given expired." );
        
        if ( mode == RenderQueueCache::Static )
        {
            return AddStaticRenderCommand( material , command );
        }
        
        else if ( mode == RenderQueueCache::Dynamic )
        {
            return AddDynamicRenderCommand( material , command );
        }
    }
    
    ////////////////////////////////////////////////////////////
    void RenderPass::AddRenderCommands( const Weak < Material >& material , const WeakVector < RenderCommand >& commands , const RenderQueueCache& mode )
    {
        assert( !material.expired() && "Material given expired." );
        
        if ( mode == RenderQueueCache::Static )
        {
            return AddStaticRenderCommands( material , commands );
        }
        
        else if ( mode == RenderQueueCache::Dynamic )
        {
            return AddDynamicRenderCommands( material , commands );
        }
    }
    
    ////////////////////////////////////////////////////////////
    void RenderPass::AddStaticRenderCommand( const Weak < Material >& material , const Weak < RenderCommand >& command )
    {
        assert( !material.expired() && "Material given expired." );
        assert( !command.expired() && "RenderCommand given expired." );
        
        auto renderqueue = CreateOrGetStaticRenderQueue( material );
        assert( renderqueue && "'CreateOrGetStaticQueue()' returned null." );
        
        renderqueue->AddRenderCommand( command );
    }
    
    ////////////////////////////////////////////////////////////
    void RenderPass::AddDynamicRenderCommand( const Weak < Material >& material , const Weak < RenderCommand >& command )
    {
        assert( !material.expired() && "Material given expired." );
        assert( !command.expired() && "RenderCommand given expired." );
        
        auto renderqueue = CreateOrGetDynamicRenderQueue( material );
        assert( renderqueue && "'CreateOrGetDynamicQueue()' returned null." );
        
        renderqueue->AddRenderCommand( command );
    }
    
    ////////////////////////////////////////////////////////////
    void RenderPass::AddStaticRenderCommands( const Weak < Material >& material , const WeakVector < RenderCommand >& commands )
    {
        assert( !material.expired() && "Material given expired." );
        
        auto renderqueue = CreateOrGetStaticRenderQueue( material );
        assert( renderqueue && "'CreateOrGetStaticQueue()' returned null." );
        
        renderqueue->AddRenderCommands( commands );
    }
    
    ////////////////////////////////////////////////////////////
    void RenderPass::AddDynamicRenderCommands( const Weak < Material >& material , const WeakVector < RenderCommand >& commands )
    {
        assert( !material.expired() && "Material given expired." );
        
        auto renderqueue = CreateOrGetDynamicRenderQueue( material );
        assert( renderqueue && "'CreateOrGetDynamicQueue()' returned null." );
        
        renderqueue->AddRenderCommands( commands );
    }
    
    ////////////////////////////////////////////////////////////
    Shared < RenderQueue > RenderPass::CreateOrGetStaticRenderQueue( const Weak < Material >& material )
    {
        assert( !material.expired() && "Material given expired." );
        ResourceId id = material.lock()->GetId();
        assert( id > 0 && "'Material::GetId()' returned invalid MaterialId." );
        
        MutexLocker lck( m_mutex );
        auto it = m_statqueuebyid.find( id );
        
        if ( it == m_statqueuebyid.end() )
        {
            auto renderqueue = CreateRenderQueue( material , RenderQueueCache::Static );
            assert( renderqueue && "'std::make_shared<RenderQueue>()' failed." );
            
            m_staticqueues.push_back( renderqueue );
            m_statqueuebyid[id] = renderqueue ;
            return renderqueue ;
        }
        
        else
        {
            return it->second.lock();
        }
    }
    
    ////////////////////////////////////////////////////////////
    Shared < RenderQueue > RenderPass::CreateOrGetDynamicRenderQueue( const Weak < Material >& material )
    {
        assert( !material.expired() && "Material given expired." );
        ResourceId id = material.lock()->GetId();
        assert( id > 0 && "'Material::GetId()' returned invalid MaterialId." );
        
        MutexLocker lck( m_mutex );
        auto it = m_dynaqueuebyid.find( id );
        
        if ( it == m_dynaqueuebyid.end() )
        {
            auto renderqueue = CreateRenderQueue( material , RenderQueueCache::Dynamic );
            assert( renderqueue && "'std::make_shared<RenderQueue>()' failed." );
            
            m_dynamicqueues.push_back( renderqueue );
            m_dynaqueuebyid[id] = renderqueue ;
            return renderqueue ;
        }
        
        else
        {
            return it->second.lock();
        }
    }
}
