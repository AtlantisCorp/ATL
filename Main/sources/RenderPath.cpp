//  ========================================================================  //
//
//  File    : ATL/RenderPath.cpp
//  Project : atlresource
//  Author  : Luk2010
//  Date    : 20/10/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#include <ATL/RenderPath.hpp>

namespace atl
{
    ////////////////////////////////////////////////////////////
    RenderPath::RenderPath( const Weak < RenderWindow >& window ) : m_window( window )
    {
        auto operation = std::make_shared < Operation >();
        operation->done.store( false );
        operation->target = std::static_pointer_cast < RenderTarget >( window.lock() );
        m_first = operation ;
        m_operations.push_back( operation );
    }
    
    ////////////////////////////////////////////////////////////
    RenderPath::~RenderPath()
    {
        
    }
    
    ////////////////////////////////////////////////////////////
    void RenderPath::Draw()
    {
        MutexLocker lck( m_mutex );
        assert( m_first && "'m_first' has expired." );

        _Init();
        _RecursiveDrawLook( m_first );
    }
    
    ////////////////////////////////////////////////////////////
    void RenderPath::Flush()
    {
        assert( !m_window.expired() && "'m_window' has expired." );
        m_window.lock()->Display();
    }
    
    ////////////////////////////////////////////////////////////
    void RenderPath::Easyloop()
    {
        assert( !m_window.expired() && "'m_window' has expired." );
        auto window = m_window.lock();
        
        while ( !window->Closed() )
        {
            this->Draw();
            this->Flush();
        }
    }
    
    ////////////////////////////////////////////////////////////
    void RenderPath::_Init()
    {
        for ( auto& operation : m_operations )
        {
            operation.lock()->done.store( false );
        }
    }
    
    ////////////////////////////////////////////////////////////
    void RenderPath::_RecursiveDrawLook( Shared < Operation >& operation )
    {
        std::unique_lock < Mutex > lck( operation->mutex );
        
        if ( operation->done.load() )
        {
            operation->cv.notify_all();
            return ;
        }
        
        std::thread thread = std::thread([this,operation]()
        {
            for ( auto& subop : operation->previouses )
            {
                std::unique_lock < Mutex > lck( subop->mutex );
                _RecursiveDrawLook( subop );
                subop->cv.wait( lck );
            }
        });
        
        thread.join();
        
        operation->target.lock()->Update();
        operation->target.lock()->Draw();
        operation->done.store( true );
        operation->cv.notify_all();
    }
}
