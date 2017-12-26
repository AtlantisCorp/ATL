//  ========================================================================  //
//
//  File    : ATL/LoadingQueue.cpp
//  Project : atlresource
//  Author  : Luk2010
//  Date    : 25/10/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#include <ATL/LoadingQueue.hpp>
#include <ATL/Root.hpp>

namespace atl
{
    ////////////////////////////////////////////////////////////
    IDGenerator < LoadingQueueId > LoadingQueue::s_generator ;
    
    ////////////////////////////////////////////////////////////
    LoadingQueue::LoadingQueue( LoadingQueue::LoadingFunc func , void* data )
    : m_id( s_generator.New() ) , m_func( func )
    {
        m_context.renderwindow = Weak < RenderWindow >();
        m_context.driver       = Root::Get().GetDriver();
        m_context.surfacer     = Root::Get().GetSurfacer();
        m_context.data         = data ;
    }
    
    ////////////////////////////////////////////////////////////
    LoadingQueue::LoadingQueue( const Weak < RenderWindow >& renderwindow , LoadingQueue::LoadingFunc func , void* data )
    : m_id( s_generator.New() ) , m_func( func )
    {
        m_context.renderwindow = renderwindow ;
        m_context.driver       = Root::Get().GetDriver();
        m_context.surfacer     = Root::Get().GetSurfacer();
        m_context.data         = data ;
    }
    
    ////////////////////////////////////////////////////////////
    LoadingQueue::~LoadingQueue()
    {
        
    }
    
    ////////////////////////////////////////////////////////////
    void LoadingQueue::Start()
    {
        MutexLocker lck( m_mutex );
        m_performer.StartSynced();
        
        if ( m_func )
        {
            m_func( m_context );
        }
        
        m_performer.EndSynced();
    }
    
    ////////////////////////////////////////////////////////////
    void LoadingQueue::StartAsync()
    {
        m_performer.Start( [this](){
            
            m_mutex.lock();
            auto func = m_func ;
            auto ctxt = m_context ;
            m_mutex.unlock();
            
            func( ctxt );
        });
    }
    
    ////////////////////////////////////////////////////////////
    const Performer& LoadingQueue::GetPerformer() const
    {
        MutexLocker lck( m_mutex );
        return m_performer ;
    }
    
    ////////////////////////////////////////////////////////////
    void LoadingQueue::Wait()
    {
        MutexLocker lck( m_mutex );
        return m_performer.Wait();
    }
    
    ////////////////////////////////////////////////////////////
    bool LoadingQueue::IsFinished() const
    {
        MutexLocker lck( m_mutex );
        return m_performer.IsFinished();
    }
}
