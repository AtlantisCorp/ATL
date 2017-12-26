//  ========================================================================  //
//
//  File    : ATL/RenderPass.hpp
//  Project : atlresource
//  Author  : Luk2010
//  Date    : 17/10/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#ifndef RenderPass_hpp
#define RenderPass_hpp

#include <ATL/StdIncludes.hpp>
#include <ATL/RenderCommand.hpp>
#include <ATL/RenderQueue.hpp>
#include <ATL/Program.hpp>

namespace atl
{
    ////////////////////////////////////////////////////////////
    class Context ;
    
    ////////////////////////////////////////////////////////////
    /// \brief Local unique ID for a RenderPass.
    ///
    ////////////////////////////////////////////////////////////
    typedef unsigned long long RenderPassId ;
    
    ////////////////////////////////////////////////////////////
    /// \brief Defines a rendering pass in a rendertarget.
    ///
    /// It corresponds to a set of rendering queues attached to a
    /// particular pass and which will use a particular program to
    /// be drawed by the driver.
    ///
    /// 2 types of rendering queues are currently supported: static
    /// queues for Mutex locked, cached renderqueues and dynamic queues
    /// for Spinlock locked, not cached renderqueues. Creates VertexCommand
    /// accordingly to how often you will update them.
    ///
    /// RenderQueues are used in Shared pointer and not Unique pointer,
    /// because of multithreaded purpose. Also, queues' vector is locked
    /// when modifying it but copied when reading from it because it is
    /// assumed that you can always modify the vector while the pass is
    /// looking at it and iterating over it when drawing. So just copy it
    /// and perform the drawing.
    ///
    ////////////////////////////////////////////////////////////
    class RenderPass
    {
        ////////////////////////////////////////////////////////////
        typedef Map < ResourceId , Weak < RenderQueue > > RenderQueueMap ;
        
        ////////////////////////////////////////////////////////////
        static IDGenerator < RenderPassId > s_generator ;
        
        ////////////////////////////////////////////////////////////
        Atomic < RenderPassId >      m_id ;            ///< Local unique identifier.
        SharedVector < RenderQueue > m_staticqueues ;  ///< Static renderqueues for the pass.
        RenderQueueMap               m_statqueuebyid ; ///< Static renderqueues by MaterialId.
        SharedVector < RenderQueue > m_dynamicqueues ; ///< Dynamic renderqueues for the pass.
        RenderQueueMap               m_dynaqueuebyid ; ///< Dynamic renderqueues by MaterialId.
        Weak < Program >             m_program ;       ///< Program set to draw the pass.
        mutable Mutex                m_mutex ;         ///< Mutex to access renderqueues arrays.
        
    public:
        
        ////////////////////////////////////////////////////////////
        RenderPass( const Weak < Program >& program );
        
        ////////////////////////////////////////////////////////////
        virtual ~RenderPass();
        
        ////////////////////////////////////////////////////////////
        /// \brief Returns the local id.
        ///
        ////////////////////////////////////////////////////////////
        RenderPassId GetId() const ;
        
        ////////////////////////////////////////////////////////////
        /// \brief Returns the used program.
        ///
        ////////////////////////////////////////////////////////////
        virtual const Weak < Program > GetProgram() const ;
        
        ////////////////////////////////////////////////////////////
        /// \brief Draw its renderqueues.
        ///
        /// \param context  A reference to the current context drawing this
        ///                 renderpass. Generally this parameter is given
        ///                 by RenderCommandGroup.
        /// \param program  A reference to the currently bound program. This
        ///                 program is bound to the target by RenderCommandGroup
        ///                 before drawing the pass and is guaranteed not to be
        ///                 destroyed before 'Draw()' finishes.
        ///
        ////////////////////////////////////////////////////////////
        virtual void Draw( const Context& driver , const Program& program ) const ;
        
        ////////////////////////////////////////////////////////////
        /// \brief Reset the dynamic queues only.
        ///
        ////////////////////////////////////////////////////////////
        virtual void _ResetDynamicRenderQueues();
        
        ////////////////////////////////////////////////////////////
        /// \brief Select the correct renderqueue based on material
        /// and mode selection and add the given VertexCommand.
        ///
        /// \note If the renderqueue does not exist, it will be created
        /// as a new renderqueue.
        ///
        /// \param material Material to select the renderqueue.
        /// \param command  VertexCommand to add to the selected renderqueue.
        /// \param mode     Caching mode selected for the renderqueue.
        ///
        ////////////////////////////////////////////////////////////
        virtual void AddRenderCommand( const Weak < Material >& material ,
                                       const Weak < RenderCommand >& command ,
                                       const RenderQueueCache& mode );
        
        ////////////////////////////////////////////////////////////
        /// \brief Select the correct renderqueue based on material and
        /// mode selection and add the given batch of VertexCommands.
        ///
        /// \note If the renderqueue does not exist, it will be created
        /// as a new renderqueue. Use this function if you have multiple
        /// VertexCommand to submit to the target, because it will lock the
        /// internal mutex/spinlock only once for every VertexCommands and
        /// issue less atomic operations.
        ///
        /// \param material Material to select the renderqueue.
        /// \param commands VertexCommand batch to add to the selected
        ///                 renderqueue.
        /// \param mode     Caching mode selected for the renderqueue.
        ///
        ////////////////////////////////////////////////////////////
        virtual void AddRenderCommands( const Weak < Material >& material ,
                                        const WeakVector < RenderCommand >& commands ,
                                        const RenderQueueCache& mode );
        
        ////////////////////////////////////////////////////////////
        /// \brief Adds a VertexCommand to the static renderqueues.
        ///
        /// Normally this is called from 'AddVertexCommand' with mode
        /// 'RenderQueueCache::Static'. Use this mode only when you don't
        /// want to change the VertexCommand every frames. The vertexcommand
        /// is so in a 'persistent' state.
        ///
        /// \param material Material to select the renderqueue from.
        /// \param command  VertexCommand to add.
        ///
        ////////////////////////////////////////////////////////////
        virtual void AddStaticRenderCommand( const Weak < Material >& material ,
                                             const Weak < RenderCommand >& command );
        
        ////////////////////////////////////////////////////////////
        /// \brief Adds a VertexCommand to the dynamic renderqueues.
        ///
        /// Normally this is called from 'AddVertexCommand' with mode
        /// 'RenderQueueCache::Dynamic'. Use this mode only when you want
        /// to modify the VertexCommand every updates, or at least, very
        /// often. This mode let build up a new renderqueue each frame,
        /// with only a spinlock instead of mutex operations.
        ///
        /// \param material Material to select the renderqueue from.
        /// \param command  VertexCommand to add.
        ///
        ////////////////////////////////////////////////////////////
        virtual void AddDynamicRenderCommand( const Weak < Material >& material ,
                                              const Weak < RenderCommand >& command );
        
        ////////////////////////////////////////////////////////////
        /// \brief Adds a batch of VertexCommands to the static renderqueues.
        ///
        /// Normally this is called from 'AddVertexCommands' with mode
        /// 'RenderQueueCache::Static'. Use this mode only when you don't
        /// want to change the VertexCommand every frames. The vertexcommand
        /// is so in a 'persistent' state.
        ///
        /// \param material Material to select the renderqueue from.
        /// \param commands VertexCommands to add.
        ///
        ////////////////////////////////////////////////////////////
        virtual void AddStaticRenderCommands( const Weak < Material >& material ,
                                              const WeakVector < RenderCommand >& commands );
        
        ////////////////////////////////////////////////////////////
        /// \brief Adds a batch of VertexCommand to the dynamic renderqueues.
        ///
        /// Normally this is called from 'AddVertexCommands' with mode
        /// 'RenderQueueCache::Dynamic'. Use this mode only when you want
        /// to modify the VertexCommand every updates, or at least, very
        /// often. This mode let build up a new renderqueue each frame,
        /// with only a spinlock instead of mutex operations.
        ///
        /// \param material Material to select the renderqueue from.
        /// \param commands VertexCommands to add.
        ///
        ////////////////////////////////////////////////////////////
        virtual void AddDynamicRenderCommands( const Weak < Material >& material ,
                                               const WeakVector < RenderCommand >& commands );
        
        ////////////////////////////////////////////////////////////
        /// \brief Creates or return a static renderqueue selected with
        /// the given material.
        ///
        /// \param material Material to select the renderqueue from.
        ///
        ////////////////////////////////////////////////////////////
        virtual Shared < RenderQueue > CreateOrGetStaticRenderQueue( const Weak < Material >& material );
        
        ////////////////////////////////////////////////////////////
        /// \brief Creates or return a dynamic renderqueue selected with
        /// the given material.
        ///
        /// \param material Material to select the renderqueue from.
        ///
        ////////////////////////////////////////////////////////////
        virtual Shared < RenderQueue > CreateOrGetDynamicRenderQueue( const Weak < Material >& material );
    };
}

#endif /* RenderPass_hpp */
