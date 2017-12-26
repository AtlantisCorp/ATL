//  ========================================================================  //
//
//  File    : EventQueue.hpp
//  Project : atlresource
//  Author  : Luk2010
//  Date    : 03/10/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //

#ifndef ATL_EventQueue_hpp
#define ATL_EventQueue_hpp

#include <ATL/Listener.hpp>

namespace atl
{
    class EventQueue
    {
        SharedQueue < Event >   iEvents ;
        mutable Spinlock        iSpinlock ;
        Atomic < bool >         iShouldStop ;
        Atomic < bool >         iRunning ;
        std::thread             iRunThread ;
        Emitter                 iClassicEmitter ;

        static Shared < EventQueue > iMainQueue ;

    public:

        static EventQueue & GetMainQueue();

    public:

        EventQueue();
        virtual ~EventQueue();

        virtual void Add( const Shared < Event > & event );
        virtual Shared < Event > NextEvent();
        virtual void Reset();

        virtual void Run();
        virtual bool Running() const ;
        virtual void Stop();
        virtual void Join();

        virtual void AddListener( const Shared < Listener > & listener );
        virtual SharedVector < Listener > GetListeners();
        virtual void RemoveListener( const Shared < Listener > & listener );
    };
}

#endif // ATL_EventQueue_hpp
