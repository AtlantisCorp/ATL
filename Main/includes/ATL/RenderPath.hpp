//  ========================================================================  //
//
//  File    : ATL/RenderPath.hpp
//  Project : atlresource
//  Author  : Luk2010
//  Date    : 20/10/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#ifndef RenderPath_hpp
#define RenderPath_hpp

#include <ATL/StdIncludes.hpp>
#include <ATL/RenderWindow.hpp>

namespace atl
{
    ////////////////////////////////////////////////////////////
    /// \brief Defines a 'path' for rendering onto a main renderwindow.
    ///
    /// A renderpath organizes targets into rendering suboperations,
    /// in order to make subtargets to draw finally to the main
    /// renderwindow.
    ///
    /// The renderpath optimizes the targets rendering in a multithreaded
    /// fashion: independent targets are computed in separate thread.
    /// However, if the updating is always multithreaded, the rendering
    /// must lock/unlock the target context. In most cases, every targets
    /// share the same context (the one of the renderwindow) and so a
    /// multithreaded rendering is impossible (rendering simultaneously from
    /// different thread to the same context is impossible in OpenGL and
    /// DirectX, as of today or how far i know).
    ///
    ////////////////////////////////////////////////////////////
    class RenderPath
    {
        ////////////////////////////////////////////////////////////
        /// \brief An internal rendering operation.
        ///
        ////////////////////////////////////////////////////////////
        struct Operation
        {
            SharedVector < Operation > previouses ; ///< Operations before this one.
            Weak < RenderTarget >      target ;     ///< Target to draw.
            Atomic < bool >            done ;       ///< Boolean true if target has been drawed, false otherwise.
                                                    ///  This boolean must be resetted before each loop cycle.
            Mutex                      mutex ;      ///< Mutex used by the condition variable.
            std::condition_variable    cv ;         ///< Condition variable used by the operation.
        };
        
        ////////////////////////////////////////////////////////////
        Shared < Operation >     m_first ;      ///< The first operation, which is always a renderwindow.
        Weak < RenderWindow >    m_window ;     ///< The renderwindow this path is associated with.
        WeakVector < Operation > m_operations ; ///< Every operations created by this path.
        mutable Mutex            m_mutex ;      ///< Access to this path's data.
        
    public:
        
        ////////////////////////////////////////////////////////////
        RenderPath( const Weak < RenderWindow >& window );
        
        ////////////////////////////////////////////////////////////
        virtual ~RenderPath();
        
        ////////////////////////////////////////////////////////////
        /// \brief Performs 'Draw' and 'Flush' while the renderwindow
        /// isn't closed.
        ///
        ////////////////////////////////////////////////////////////
        virtual void Easyloop();
        
        ////////////////////////////////////////////////////////////
        /// \brief Performs the path looing rendering.
        ///
        ////////////////////////////////////////////////////////////
        virtual void Draw();
        
        ////////////////////////////////////////////////////////////
        /// \brief Performs 'RenderWindow::Flush' and 'RenderWindow::Display()'
        /// on main window.
        ///
        ////////////////////////////////////////////////////////////
        virtual void Flush();
        
        ////////////////////////////////////////////////////////////
        /// \brief Initializes every operation's 'done' property to
        /// false.
        ///
        /// Methods called by 'Draw' before '_RecursiveDrawLook' to
        /// initialize states before rendering.
        ///
        ////////////////////////////////////////////////////////////
        virtual void _Init();
        
        ////////////////////////////////////////////////////////////
        /// \brief Draw the given operation, recursively calling this
        /// method for undone targets.
        ///
        ////////////////////////////////////////////////////////////
        virtual void _RecursiveDrawLook( Shared < Operation >& operation );
    };
}

#endif /* RenderPath_hpp */
