//  ========================================================================  //
//
//  File    : Listener.hpp
//  Project : atlresource
//  Author  : Luk2010
//  Date    : 03/10/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //

#ifndef Listener_hpp
#define Listener_hpp

#include <ATL/StdIncludes.hpp>

namespace atl
{
    class Event : public std::enable_shared_from_this < Event >
    {
    public:

        Event() { }
        virtual ~Event() { }

        template < class Derived , class... Args >
        static Shared < Event > Create( Args&&... args )
        {
            auto event = std::make_shared < Derived >( std::forward < Args >( args )... );
            assert( event && "Can't allocate event." );
            return std::static_pointer_cast < Event >( event );
        }

        template < class Derived >
        bool Is() const {
            return typeid( *this ) == typeid( Derived ) ;
        }

        template < class Derived >
        const Shared < const Derived > To() const {
            return std::static_pointer_cast < const Derived >( shared_from_this() );
        }
    };

    class Listener
    {
    public:
        Listener() { }
        virtual ~Listener() { }
        virtual void ProceedEvent( const Shared < Event > & event ) { }
    };

    class Emitter
    {
        SharedVector < Listener > iListeners ;
        Mutex iMutex ;

    public:

        Emitter();
        virtual ~Emitter();

        template < class Derived , class... Args >
        void SendEvent( Args&&... args )
        {
            auto event = Event::Create < Derived >( std::forward < Args >( args )... );
            assert( event && "Can't create event." );
            return SendEvent( event );
        }

        template < class Derived , class... Args >
        void SendAsyncEvent( Args&&... args )
        {
            auto event = Event::Create < Derived >( std::forward < Args >( args )... );
            assert( event && "Can't create event." );
            return SendAsyncEvent( event );
        }

        template < class Derived , class... Args >
        void SendGlobalEvent( Args&&... args )
        {
            auto event = Event::Create < Derived >( std::forward < Args >( args )... );
            assert( event && "Can't create event." );
            return SendGlobalEvent( event );
        }

        virtual void SendEvent( const Shared < Event > & event );
        virtual void SendAsyncEvent( const Shared < Event > & event );
        virtual void SendGlobalEvent( const Shared < Event > & event );

        virtual void AddListener( const Shared < Listener > & listener );
        virtual SharedVector < Listener > GetListeners();
        virtual void RemoveListener( const Shared < Listener > & listener );
        virtual void Reset();
    };
    
    ////////////////////////////////////////////////////////////
    /// \brief A basic listener that responds only to one event type,
    /// by calling the given callable object.
    ///
    ////////////////////////////////////////////////////////////
    template < class EventClass , typename Callable >
    class AutoListener : public Listener
    {
        ////////////////////////////////////////////////////////////
        Callable m_callable ;
        
    public:
        
        ////////////////////////////////////////////////////////////
        AutoListener( Callable callable ) : m_callable( callable ) { }
        
        ////////////////////////////////////////////////////////////
        virtual ~AutoListener() { }
        
        ////////////////////////////////////////////////////////////
        virtual void ProceedEvent( const Shared < Event >& event )
        {
            assert( event && "'event' is null." );
            
            if ( event -> Is< EventClass >() )
            {
                auto sptr = event -> To < EventClass >();
                m_callable( *( sptr ) );
            }
        }
    };
    
    ////////////////////////////////////////////////////////////
    /// \brief Creates an AutoListener for given Event class and with
    /// given Callable.
    ///
    ////////////////////////////////////////////////////////////
    template < class EventClass , typename Callable >
    Shared < Listener > CreateAutoListener( Callable callable )
    {
        return std::static_pointer_cast < Listener >( std::make_shared < AutoListener < EventClass , Callable > >( callable ) );
    }
}

#endif // Listener_hpp
