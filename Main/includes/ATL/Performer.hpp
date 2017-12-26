//  ========================================================================  //
//
//  File    : ATL/Performer.hpp
//  Project : atlresource
//  Author  : Luk2010
//  Date    : 17/09/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#ifndef Performer_hpp
#define Performer_hpp

#include <ATL/StdIncludes.hpp>

namespace atl
{
    ////////////////////////////////////////////////////////////
    /// \brief Calculates time for doing a task.
    ///
    /// You can use this object to perform an asynchroneous task
    /// (calculating performance time between begin and end of that
    /// task) or to start/end a performance timer for synchronous
    /// tasks.
    ///
    ////////////////////////////////////////////////////////////
    class Performer
    {
        Timepoint iStart ;
        Timepoint iEnd ;

        Atomic < bool > iEnded ;
        Atomic < bool > iStarted ;

        mutable Spinlock iSpinlock ;
        std::future < void > iFuture ;

    public:

        ////////////////////////////////////////////////////////////
        Performer();

        ////////////////////////////////////////////////////////////
        virtual ~Performer();

        template < typename Callable , class... Args >
        void Start( Callable callable , Args&&... args )
        {
            assert( !iStarted.load() && "Performer already started." );
            assert( iEnded.load() && "Performer not ended yet." );

            Spinlocker lck( iSpinlock );
            iStart = Clock::now();

            iFuture = std::async( std::launch::async , [this, callable, args...](){
                
                callable( args... );

                Spinlocker lck( iSpinlock );
                iEnd = Clock::now();
                iStarted.store( false );
                iEnded.store( true );
            });

            iStarted.store( true );
            iEnded.store( false );
        }

        bool IsFinished() const;

        bool IsActive() const;

        bool IsStarted() const;

        Duration GetDuration() const;

        void Wait();

        Seconds GetSeconds() const ;

        double GetMillis() const ;

        double GetMicros() const ;

        double GetNanos() const ;
        
        ////////////////////////////////////////////////////////////
        /// \brief Starts the timer, sets state to 'started'.
        ///
        /// When using this function, 'Wait()' will lead you to an infinite
        /// waiting if performed from the same thread. However, a thread can
        /// use 'StartSynced()' to start the timer, and then launch another
        /// threaded task that will use 'EndSynced()'. But you should use
        /// 'Start()' when doing such an action.
        ///
        ////////////////////////////////////////////////////////////
        void StartSynced();
        
        ////////////////////////////////////////////////////////////
        /// \brief Ends the timer, sets state to 'finished'.
        ///
        ////////////////////////////////////////////////////////////
        void EndSynced();
    };

    class Performable
    {
        Performer iPerformer ;

    public:

        Performer& GetPerformer() { return iPerformer ; }
        const Performer& GetPerformer() const { return iPerformer ; }
    };
}

#endif /* Performer_hpp */
