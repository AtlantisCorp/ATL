//  ========================================================================  //
//
//  File    : ATL/RenderTarget.hpp
//  Project : atlresource
//  Author  : Luk2010
//  Date    : 09/10/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#ifndef RenderTarget_h
#define RenderTarget_h

#include <ATL/StdIncludes.hpp>
#include <ATL/Context.hpp>
#include <ATL/Color.hpp>
#include <ATL/ObjectGroup.hpp>
#include <ATL/RenderCommandGroup.hpp>
#include <ATL/Viewport.hpp>

namespace atl
{
    ////////////////////////////////////////////////////////////
    /// \brief Defines target locking behaviour when updating objects
    /// groups.
    ///
    ////////////////////////////////////////////////////////////
    enum class TargetLocking
    {
        Manual ,    ///< No locking of the render target is performed and objects must call 'Begin()'
                    ///  and 'End()' when using context-related functions/objects.
        PerObject , ///< Lock is performed between two objects update.
        PerGroup ,  ///< Lock is performed between two object groups.
        PerUpdate   ///< Lock is performed at the beginning and the end of the update.
    };
    
    ////////////////////////////////////////////////////////////
    /// \brief Defines a rendertarget object.
    ///
    /// Basically, a rendertarget is a context-specific object that
    /// can be drawn using 'begin()' and 'end()' function to begin/end
    /// render frame.
    ///
    /// A rendertarget holds numerous passes which describe how
    /// the rendertarget draw its shared renderqueues. Those passes
    /// are created when a VertexCommand is added with a Program that
    /// was not registered with its own Pass already.
    ///
    ////////////////////////////////////////////////////////////
    class RenderTarget : public std::enable_shared_from_this < RenderTarget >
    {
    protected:
        
        ////////////////////////////////////////////////////////////
        Weak < Context >                    m_context ;      ///< Context associated to this RenderTarget.
        Color4                              m_clearcolor ;   ///< Clear Color used when clearing the buffer.
        SharedVector < RenderCommandGroup > m_rendergroups ; ///< RenderCommand groups.
        mutable Mutex                       m_mutex ;        ///< Used to access passes.
        SharedVector < ObjectGroup >        m_groups ;       ///< Holds every groups related to this rendertarget.
        mutable Atomic < bool >             m_updated ;      ///< true when the rendertarget is updated, false when 'Draw()' is called.
        Viewport                            m_viewport ;     ///< Viewport for this RenderTarget. Default is ( 0 , 0 , 0 , 0 ).
        Atomic < TargetLocking >            m_lockupdate ;   ///< Flag to indicate wether 'Begin()' and 'End()' are called between updates,
                                                             ///  groups or objects themself. This is a performance concern in multithreaded
                                                             ///  applications, because locking a Context in another thread blocks the
                                                             ///  drawing thread from rendering and is a slow operation. If your objects are
                                                             ///  not updated very often, you should let the default value (PerUpdate).
        
    public:
        
        ////////////////////////////////////////////////////////////
        RenderTarget( const Weak < Context >& context );
        
        ////////////////////////////////////////////////////////////
        virtual ~RenderTarget();
        
        ////////////////////////////////////////////////////////////
        /// \brief Retrieve the Context associated with this rendertarget.
        ///
        ////////////////////////////////////////////////////////////
        virtual Weak < Context > GetContext() const ;
        
        ////////////////////////////////////////////////////////////
        /// \brief Changes the color when clearing the buffer.
        ///
        ////////////////////////////////////////////////////////////
        virtual void SetClearColor( const Color4& color );
        
        ////////////////////////////////////////////////////////////
        /// \brief Called by RenderPath::Draw().
        ///
        /// Calls Pass::Draw() for each pass, also calls Begin() and
        /// End() before and after every pass draw.
        /// Context associated with this RenderTarget is used to draw
        /// the current set of RenderCommandGroup in this RenderTarget.
        ///
        /// \note Implementing this function does not call 'Begin()' and
        /// 'End()' for optimization purpose. Furthermore, 'Begin()' does
        /// not clear buffers for rendering, whereas this function does.
        ///
        ////////////////////////////////////////////////////////////
        virtual void Draw() const ;
        
        ////////////////////////////////////////////////////////////
        /// \brief Lock the current context in the current thread, and
        /// actualize the context viewport to this target.
        ///
        ////////////////////////////////////////////////////////////
        virtual void Begin() const ;
        
        ////////////////////////////////////////////////////////////
        /// \brief Drop off the rendertarget after use, or unlock the
        /// current context from the calling thread. 
        ///
        ////////////////////////////////////////////////////////////
        virtual void End() const ;
        
        ////////////////////////////////////////////////////////////
        /// \brief Updates the rendertarget's groups.
        ///
        /// This process calls 'Begin()' and 'End()' functions. Therefore,
        /// the context is locked for object update in the calling thread
        /// and the drawing thread must wait for the context to be lockable
        /// again before drawing.
        /// If you want to enable real multithreaded rendering (allowing objects
        /// to update their content without stopping the rendering loop), set
        /// 'm_lockupdate' flag to 'Manual' to disable automatic locking of the
        /// target. Object must call 'Begin()' and 'End()' manually before
        /// any modification of Context-related objects.
        ///
        /// \see TargetLocking
        ///
        ////////////////////////////////////////////////////////////
        virtual void Update();
        
        ////////////////////////////////////////////////////////////
        /// \brief Add a group to this target system.
        ///
        ////////////////////////////////////////////////////////////
        virtual void AddObjectGroup( const Weak < ObjectGroup >& group );
        
        ////////////////////////////////////////////////////////////
        /// \brief Find and return the group with given id.
        ///
        ////////////////////////////////////////////////////////////
        virtual Weak < ObjectGroup > FindObjectGroup( const ObjectGroupId& id ) const ;
        
        ////////////////////////////////////////////////////////////
        virtual void AddRenderCommandGroup( const Shared < RenderCommandGroup >& group );
        
        ////////////////////////////////////////////////////////////
        Viewport GetViewport() const ;
        
        ////////////////////////////////////////////////////////////
        void SetViewport( const Viewport& rhs );
        
        ////////////////////////////////////////////////////////////
        TargetLocking GetLockBehaviour() const ;
        
        ////////////////////////////////////////////////////////////
        void SetLockBehaviour( const TargetLocking& behaviour );
    };
}

#endif /* RenderTarget_h */
