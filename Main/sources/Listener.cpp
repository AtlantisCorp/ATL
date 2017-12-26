//  ========================================================================  //
//
//  File    : Listener.cpp
//  Project : atlresource
//  Author  : Luk2010
//  Date    : 03/10/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //

#include <ATL/Listener.hpp>
#include <ATL/EventQueue.hpp>

namespace atl
{
    Emitter::Emitter()
    {

    }

    Emitter::~Emitter()
    {

    }

    void Emitter::SendEvent( const Shared < Event > & event )
    {
        auto listeners = GetListeners();

        for ( auto listener : listeners )
        {
            if ( listener )
            listener -> ProceedEvent( event );
        }
    }

    void Emitter::SendAsyncEvent( const Shared < Event > & event )
    {
        std::thread thread( [this]( const Shared < Event > & event ) {

            SendEvent( event );

        } , event );

        thread.detach();
    }

    void Emitter::SendGlobalEvent( const Shared < Event > & event )
    {
        EventQueue & mainqueue = EventQueue::GetMainQueue();
        mainqueue.Add( event );
    }
    
    void Emitter::AddListener( const Shared < Listener > & listener )
    {
        MutexLocker lck( iMutex );
        iListeners.push_back( listener );
    }
    
    SharedVector < Listener > Emitter::GetListeners()
    {
        MutexLocker lck( iMutex );
        return iListeners ;
    }
    
    void Emitter::RemoveListener( const Shared < Listener > & listener )
    {
        MutexLocker lck( iMutex );
        auto it = std::find( iListeners.begin() , iListeners.end() , listener );
        
        if ( it != iListeners.end() )
        iListeners.erase( it );
    }
    
    void Emitter::Reset()
    {
        MutexLocker lck( iMutex );
        iListeners.clear();
    }
}
