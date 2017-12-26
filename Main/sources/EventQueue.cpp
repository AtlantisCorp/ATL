//  ========================================================================  //
//
//  File    : EventQueue.cpp
//  Project : atlresource
//  Author  : Luk2010
//  Date    : 03/10/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //

#include <ATL/EventQueue.hpp>

namespace atl
{
    Shared < EventQueue > EventQueue::iMainQueue = std::make_shared < EventQueue >();

    EventQueue & EventQueue::GetMainQueue()
    {
        assert( iMainQueue && "Invalid main queue." );
        return *iMainQueue ;
    }

    EventQueue::EventQueue() : iRunning( false )
    {

    }

    EventQueue::~EventQueue()
    {
        Stop();
        Join();
    }

    void EventQueue::Add( const Shared < Event > & event )
    {
        Spinlocker lck( iSpinlock );
        iEvents.push( event );
    }

    Shared < Event > EventQueue::NextEvent()
    {
        Spinlocker lck( iSpinlock );

        if ( iEvents.empty() )
        return Shared < Event >();

        auto event = iEvents.front();
        iEvents.pop();

        return event ;
    }

    void EventQueue::Reset()
    {
        Stop();
        Join();

        iShouldStop.store( false );
        Spinlocker lck( iSpinlock );

        SharedQueue < Event > tmp ;
        iEvents.swap( tmp );

        iClassicEmitter.Reset();
    }

    void EventQueue::Run()
    {
        Stop();
        Join();

        iShouldStop.store( false );
        iRunning.store( true );
        iRunThread = std::thread( [this]() {

            while ( !iShouldStop.load() )
            {
                auto event = NextEvent();

                if ( event )
                iClassicEmitter.SendEvent( event );
            }

            iRunning.store( false );
        });
    }

    bool EventQueue::Running() const
    {
        return iRunning.load();
    }

    void EventQueue::Stop()
    {
        iShouldStop.store( true );
    }

    void EventQueue::Join()
    {
        if ( iRunThread.joinable() )
        iRunThread.join();
    }

    void EventQueue::AddListener( const Shared < Listener > & listener )
    {
        iClassicEmitter.AddListener( listener );
    }

    SharedVector < Listener > EventQueue::GetListeners()
    {
        return iClassicEmitter.GetListeners();
    }

    void EventQueue::RemoveListener( const Shared < Listener > & listener )
    {
        iClassicEmitter.RemoveListener( listener );
    }
}
