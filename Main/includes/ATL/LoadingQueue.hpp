//  ========================================================================  //
//
//  File    : ATL/LoadingQueue.hpp
//  Project : atlresource
//  Author  : Luk2010
//  Date    : 25/10/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#ifndef LoadingQueue_hpp
#define LoadingQueue_hpp

#include <ATL/StdIncludes.hpp>
#include <ATL/IDGenerator.hpp>
#include <ATL/Performer.hpp>
#include <ATL/LoadingContext.hpp>

namespace atl
{
    ////////////////////////////////////////////////////////////
    class RenderWindow ;
    
    ////////////////////////////////////////////////////////////
    /// \brief Local identifier.
    ///
    ////////////////////////////////////////////////////////////
    typedef unsigned long long LoadingQueueId ;
    
    ////////////////////////////////////////////////////////////
    /// \brief Defines an object to load things with a defined
    /// context.
    ///
    ////////////////////////////////////////////////////////////
    class LoadingQueue
    {
        ////////////////////////////////////////////////////////////
        typedef void (*LoadingFunc) ( LoadingContext& );
        
        ////////////////////////////////////////////////////////////
        static IDGenerator < LoadingQueueId > s_generator ;
        
        ////////////////////////////////////////////////////////////
        Atomic < LoadingQueueId > m_id ;        ///< Local id.
        LoadingFunc               m_func ;      ///< Function to call with the context.
        Performer                 m_performer ; ///< Performer to perform the function.
        mutable Mutex             m_mutex ;     ///< Mutex to access data.
        LoadingContext            m_context ;   ///< Context created at initialization.
        
    public:
        
        ////////////////////////////////////////////////////////////
        /// \brief Constructs a loading queue with a simple context,
        /// without any renderwindow.
        ///
        ////////////////////////////////////////////////////////////
        LoadingQueue( LoadingFunc func , void* data = nullptr );
        
        ////////////////////////////////////////////////////////////
        /// \brief Creates a loading queue where the context has the
        /// given renderwindow.
        ///
        ////////////////////////////////////////////////////////////
        LoadingQueue( const Weak < RenderWindow >& renderwindow , LoadingFunc func , void* data = nullptr );
        
        ////////////////////////////////////////////////////////////
        virtual ~LoadingQueue();
        
        ////////////////////////////////////////////////////////////
        /// \brief Starts the loading queue synchroneously.
        ///
        /// The function is blocking and will return only when the loading
        /// queue has finished its task.
        ///
        ////////////////////////////////////////////////////////////
        virtual void Start();
        
        ////////////////////////////////////////////////////////////
        /// \brief Starts the loading queue asynchroneously.
        ///
        /// The function is non-blocking and 'Wait', 'IsFinished' and
        /// 'IsActive' are not available.
        ///
        ////////////////////////////////////////////////////////////
        virtual void StartAsync();
        
        ////////////////////////////////////////////////////////////
        /// \brief Return the performer used to perform the task.
        ///
        ////////////////////////////////////////////////////////////
        virtual const Performer& GetPerformer() const ;
        
        ////////////////////////////////////////////////////////////
        /// \brief Wait for the loading queue to finish.
        ///
        ////////////////////////////////////////////////////////////
        virtual void Wait();
        
        ////////////////////////////////////////////////////////////
        /// \brief See Performer::IsFinished.
        ///
        ////////////////////////////////////////////////////////////
        virtual bool IsFinished() const ;
    };
}

#endif /* LoadingQueue_hpp */
