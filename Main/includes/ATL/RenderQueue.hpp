//  ========================================================================  //
//
//  File    : ATL/RenderQueue.hpp
//  Project : atlresource
//  Author  : Luk2010
//  Date    : 17/10/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#ifndef RenderQueue_hpp
#define RenderQueue_hpp

#include <ATL/StdIncludes.hpp>
#include <ATL/Material.hpp>
#include <ATL/RenderCommand.hpp>

namespace atl
{
    ////////////////////////////////////////////////////////////
    class Context ;
    class Program ;
    
    ////////////////////////////////////////////////////////////
    /// \brief Defines the renderqueue caching behaviour.
    ///
    ////////////////////////////////////////////////////////////
    enum class RenderQueueCache
    {
        Static ,  ///< Implies mutex locking, caching enabled.
        Dynamic , ///< Implies spinlock locking, caching disabled.
        
        Default = Static
    };
    
    ////////////////////////////////////////////////////////////
    /// \brief Defines a rendering queue to submit RenderCommands
    /// to the driver.
    ///
    /// It also holds the material that should be used to draw the
    /// RenderCommands. This material should never be null, but the
    /// Weak directive implies that is could be. RenderQueues with an
    /// expired Weak material will be ignored.
    ///
    ////////////////////////////////////////////////////////////
    class RenderQueue
    {
        ////////////////////////////////////////////////////////////
        Weak < Material > m_material ; ///< Material to use to execute the commands.
        
    public:
        
        ////////////////////////////////////////////////////////////
        RenderQueue( const Weak < Material >& material );
        
        ////////////////////////////////////////////////////////////
        virtual ~RenderQueue();
        
        ////////////////////////////////////////////////////////////
        virtual RenderQueueCache GetCachePolicy() const = 0 ;
        
        ////////////////////////////////////////////////////////////
        virtual const Weak < Material > GetMaterial() const ;
        
        ////////////////////////////////////////////////////////////
        /// \brief Adds a RenderCommand to this queue.
        ///
        ////////////////////////////////////////////////////////////
        virtual void AddRenderCommand( const Weak < RenderCommand >& command ) = 0 ;
        
        ////////////////////////////////////////////////////////////
        /// \brief Adds a batch of RenderCommands to this queue.
        ///
        ////////////////////////////////////////////////////////////
        virtual void AddRenderCommands( const WeakVector < RenderCommand >& commands ) = 0 ;
        
        ////////////////////////////////////////////////////////////
        /// \brief Draws the renderqueue with the current driver.
        ///
        /// \param context  The current context. It is guaranteed to be valid
        ///                 untill 'Draw' finished and is retained by 'RenderTarget'.
        /// \param program  The program currently bound and retained by
        ///                 'RenderCommandGroup'. As context, it is guaranteed to
        ///                 be valid.
        ///
        /// \note When 'Draw' is called, the renderqueue material is already
        /// bound (prepared) to program. RenderQueue's drawing function should
        /// only bind its parameters to the program and draw vertex commands.
        ///
        ////////////////////////////////////////////////////////////
        virtual void Draw( const Context& context , const Program& program ) const = 0 ;
    };
    
    ////////////////////////////////////////////////////////////
    /// \brief Implementation of a static renderqueue.
    ///
    /// A 'static' renderqueue is specialized for caching RenderCommands
    /// and iterating over the vertex commands for rendering. A mutex is
    /// used to access the vertex commands, and the batch of vertex commands
    /// is contained into a vector for quicker iterating over insertion.
    /// This is the best choice for multiple RenderCommands that are not
    /// modified very often. Modifying a static queue is more expensive than
    /// a dynamic queue which use a spinlock and a list.
    ///
    /// Finally, as a static render queue caches its RenderCommands, not
    /// modifying them will make the updater able not to do anything to the
    /// queue before rendering and thus, make update time a lot quicker.
    ///
    ////////////////////////////////////////////////////////////
    class StaticRenderQueue : public RenderQueue
    {
        ////////////////////////////////////////////////////////////
        WeakVector < RenderCommand > m_commands ; ///< Commands for this queue.
        mutable Mutex                m_mutex ;    ///< Mutex to access the queue.
        
    public:
        using RenderQueue::RenderQueue ;
        
        ////////////////////////////////////////////////////////////
        virtual ~StaticRenderQueue();
        
        ////////////////////////////////////////////////////////////
        virtual RenderQueueCache GetCachePolicy() const ;
        
        ////////////////////////////////////////////////////////////
        /// \brief Adds a RenderCommand to this queue.
        ///
        ////////////////////////////////////////////////////////////
        virtual void AddRenderCommand( const Weak < RenderCommand >& command );
        
        ////////////////////////////////////////////////////////////
        /// \brief Adds a batch of RenderCommands to this queue.
        ///
        ////////////////////////////////////////////////////////////
        virtual void AddRenderCommands( const WeakVector < RenderCommand >& commands );
        
        ////////////////////////////////////////////////////////////
        /// \brief Draws the renderqueue with the current driver.
        ///
        /// \param context  The current context. It is guaranteed to be valid
        ///                 untill 'Draw' finished and is retained by 'RenderTarget'.
        /// \param program  The program currently bound and retained by
        ///                 'RenderCommandGroup'. As context, it is guaranteed to
        ///                 be valid.
        ///
        /// \note When 'Draw' is called, the renderqueue material is already
        /// bound (prepared) to program. RenderQueue's drawing function should
        /// only bind its parameters to the program and draw vertex commands.
        ///
        ////////////////////////////////////////////////////////////
        virtual void Draw( const Context& context , const Program& program ) const ;
    };
    
    ////////////////////////////////////////////////////////////
    /// \brief Implementation of a dynamic renderqueue.
    ///
    /// A dynamic queue is optimized for quick insertion/deletion
    /// of vertex commands. As a dynamic queue is never cached by
    /// the RenderPass, objects have to buil a new queue for each
    /// frame. This is a good behaviour for objects that needs constant
    /// or very often updating of their RenderCommands.
    ///
    /// A list is used for fast insertion, and a spinlock for fast
    /// locking. However, iterating through the dynamic queue is slower
    /// than over a static queue. Dynamic queues should be used for
    /// a less number of RenderCommands but that are updated a lot more
    /// frequently than a static queue.
    ///
    ////////////////////////////////////////////////////////////
    class DynamicRenderQueue : public RenderQueue
    {
        ////////////////////////////////////////////////////////////
        WeakList < RenderCommand > m_commands ; ///< Commands for this queue.
        mutable Spinlock           m_spinlock ; ///< Spinlock to access the list.
        
    public:
        using RenderQueue::RenderQueue ;
        
        ////////////////////////////////////////////////////////////
        virtual ~DynamicRenderQueue();
        
        ////////////////////////////////////////////////////////////
        virtual RenderQueueCache GetCachePolicy() const ;
        
        ////////////////////////////////////////////////////////////
        /// \brief Adds a RenderCommand to this queue.
        ///
        ////////////////////////////////////////////////////////////
        virtual void AddRenderCommand( const Weak < RenderCommand >& command );
        
        ////////////////////////////////////////////////////////////
        /// \brief Adds a batch of RenderCommands to this queue.
        ///
        ////////////////////////////////////////////////////////////
        virtual void AddRenderCommands( const WeakVector < RenderCommand >& commands );
        
        ////////////////////////////////////////////////////////////
        /// \brief Draws the renderqueue with the current driver.
        ///
        /// \param context  The current context. It is guaranteed to be valid
        ///                 untill 'Draw' finished and is retained by 'RenderTarget'.
        /// \param program  The program currently bound and retained by
        ///                 'RenderCommandGroup'. As context, it is guaranteed to
        ///                 be valid.
        ///
        /// \note When 'Draw' is called, the renderqueue material is already
        /// bound (prepared) to program. RenderQueue's drawing function should
        /// only bind its parameters to the program and draw vertex commands.
        ///
        ////////////////////////////////////////////////////////////
        virtual void Draw( const Context& context , const Program& program ) const ;
    };
    
    ////////////////////////////////////////////////////////////
    /// \brief Creates a renderqueue depending on its cache policy.
    ///
    ////////////////////////////////////////////////////////////
    Shared < RenderQueue > CreateRenderQueue( const Weak < Material >& material , const RenderQueueCache& policy );
}

#endif /* RenderQueue_hpp */
