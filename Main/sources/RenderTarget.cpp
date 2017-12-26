//  ========================================================================  //
//
//  File    : ATL/RenderTarget.cpp
//  Project : atlresource
//  Author  : Luk2010
//  Date    : 10/10/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#include <ATL/RenderTarget.hpp>

namespace atl
{
    ////////////////////////////////////////////////////////////
    RenderTarget::RenderTarget( const Weak < Context >& context )
    : m_updated( false ) , m_viewport({ { 0 , 0 } , { 0 , 0 } }) , m_lockupdate( TargetLocking::PerUpdate )
    {
        m_context = context ;
    }
    
    ////////////////////////////////////////////////////////////
    RenderTarget::~RenderTarget()
    {
        
    }
    
    ////////////////////////////////////////////////////////////
    Weak < Context > RenderTarget::GetContext() const
    {
        return m_context ;
    }
    
    ////////////////////////////////////////////////////////////
    void RenderTarget::SetClearColor( const Color4& color )
    {
        m_clearcolor = color ;
    }
    
    ////////////////////////////////////////////////////////////
    void RenderTarget::Draw() const
    {
        if ( !m_updated.load() )
            return ;
        if ( m_context.expired() )
            return ;
        
        m_mutex.lock();
        auto tmpgroups  = m_rendergroups ;
        auto context    = m_context.lock();
        auto clearcolor = m_clearcolor ;
        auto viewport   = m_viewport ;
        m_mutex.unlock();
        
        for ( auto group : tmpgroups )
        {
            context->SetActive( true );
            context->ClearColor( clearcolor );
            context->BindViewport( viewport );
            
            group->Draw( *this );
            
            context->SetActive( false );
        }
        
        m_updated.store( false );
    }
    
    ////////////////////////////////////////////////////////////
    void RenderTarget::Begin() const
    {
        if ( !m_context.expired() )
        {
            auto context = m_context.lock();
            context->SetActive( true );
            context->BindViewport( m_viewport );
        }
    }
    
    ////////////////////////////////////////////////////////////
    void RenderTarget::End() const
    {
        if ( !m_context.expired() )
        {
            m_context.lock()->SetActive( false );
        }
        
        m_updated.store( false );
    }
    
    ////////////////////////////////////////////////////////////
    void RenderTarget::Update()
    {
        m_mutex.lock();
        auto groups = m_groups ;
        m_mutex.unlock();
        
        switch( m_lockupdate.load() )
        {
            case TargetLocking::Manual:
                
                for ( auto const& group : groups )
                {
                    if ( group )
                    {
                        group -> Update( *this , false );
                    }
                }
                break ;
                
            case TargetLocking::PerObject:
                
                for ( auto const& group : groups )
                {
                    if ( group )
                    {
                        group -> Update( *this , true );
                    }
                }
                break ;
                
            case TargetLocking::PerGroup:
                
                for ( auto const& group : groups )
                {
                    if ( group )
                    {
                        Begin();
                        group -> Update( *this , false );
                        End();
                    }
                }
                break ;
                
            case TargetLocking::PerUpdate:
            default:
                
                Begin();
                for ( auto const& group : groups )
                {
                    if ( group )
                    {
                        group -> Update( *this , false );
                    }
                }
                End();
                break ;
        }
        
        m_updated.store( true );
    }
    
    ////////////////////////////////////////////////////////////
    void RenderTarget::AddObjectGroup( const Weak < ObjectGroup >& group )
    {
        assert( !group.expired() && "ObjectGroup expired." );
        
        if ( !FindObjectGroup( group.lock()->GetId() ).expired() )
            return ;
        
        MutexLocker lck( m_mutex );
        m_groups.push_back( group.lock() );
    }
    
    ////////////////////////////////////////////////////////////
    Weak < ObjectGroup > RenderTarget::FindObjectGroup( const ObjectGroupId& id ) const
    {
        MutexLocker lck( m_mutex );
        
        for ( auto const& group : m_groups )
        {
            if ( group->GetId() == id )
                return group ;
        }
        
        return Weak < ObjectGroup >();
    }
    
    ////////////////////////////////////////////////////////////
    void RenderTarget::AddRenderCommandGroup( const Shared < RenderCommandGroup >& group )
    {
        MutexLocker lck( m_mutex );
        m_rendergroups.push_back( group );
    }
    
    ////////////////////////////////////////////////////////////
    Viewport RenderTarget::GetViewport() const
    {
        MutexLocker lck( m_mutex );
        return m_viewport ;
    }
    
    ////////////////////////////////////////////////////////////
    void RenderTarget::SetViewport( const Viewport& rhs )
    {
        MutexLocker lck( m_mutex );
        m_viewport = rhs ;
    }
    
    ////////////////////////////////////////////////////////////
    TargetLocking RenderTarget::GetLockBehaviour() const
    {
        return m_lockupdate.load();
    }
    
    ////////////////////////////////////////////////////////////
    void RenderTarget::SetLockBehaviour( const TargetLocking& behaviour )
    {
        m_lockupdate.store( behaviour );
    }
}
