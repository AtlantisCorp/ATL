//  ========================================================================  //
//
//  File    : ATL/RenderWindow.hpp
//  Project : atlresource
//  Author  : Luk2010
//  Date    : 09/10/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#ifndef RenderWindow_h
#define RenderWindow_h

#include <ATL/StdIncludes.hpp>
#include <ATL/RenderTarget.hpp>
#include <ATL/Surface.hpp>
#include <ATL/CBuffer.hpp>

namespace atl
{
    ////////////////////////////////////////////////////////////
    /// \brief Defines a RenderWindow.
    ///
    /// A RenderWindow generally associates a Context to a Surface,
    /// and is created by a Driver. The RenderWindow is a RenderTarget
    /// but you can consider that the RenderWindow is a Window with,
    /// as default RenderTarget, its backbuffer.
    ///
    /// A RenderWindow always takes ownership of the Surface and the Context
    /// passed to it. Considers that when destroying a RenderWindow, you also
    /// destroy its Surface and its Context. However, as the Surface is already
    /// managed by the Surfacer, the RenderWindow removes it when destroyed.
    ///
    /// ( OpenGL ) : The RenderWindow only binds and unbinds the GlContext
    /// as the default framebuffer is the associated surface backbuffer.
    /// ( DirectX ) : The RenderWindow creates a RenderTargetView with the
    /// Surface backbuffer pointer. On display, it will set this view to
    /// the DeviceContext and then present it.
    ///
    ////////////////////////////////////////////////////////////
    class RenderWindow : public RenderTarget
    {
        ////////////////////////////////////////////////////////////
        Weak < Surface >   m_surface ;    ///< Surface associated to this RenderWindow.
        Shared < Context > m_context ;    ///< Owned Context associated to the Surface.
        Atomic < bool >    m_displayed ;  ///< True once the 'Display' method is called, false otherwise.
        mutable Mutex      m_mutex ;      ///< Local thread protection.
        Atomic < bool >    m_slistened ;  ///< Flag indicating wether the Surface's Autolistener is created or not.
                                          ///  As the Surface's listener must hold a Weak pointer to this object, it
                                          ///  cannot be created in the constructor and is instanciated in 'Display()'.
        Atomic < bool >    m_autoresize ; ///< Flag indicating wether the RenderWindow's Viewport should be resized
                                          ///  automatically when Surface is resized (true) or not (false). Default value
                                          ///  is always true, as a RenderWindow should be tightly linked to its Surface.
        
    public:
        
        ////////////////////////////////////////////////////////////
        /// \brief Construct the renderwindow with a surface and a
        /// given context.
        ///
        /// \param surface Surface to fill with this RenderWindow.
        /// \param context Context associated.
        ///
        ////////////////////////////////////////////////////////////
        RenderWindow( const Weak < Surface >& surface , const Weak < Context >& context );
        
        ////////////////////////////////////////////////////////////
        virtual ~RenderWindow();
        
        ////////////////////////////////////////////////////////////
        /// \brief Returns the underlying surface.
        ///
        ////////////////////////////////////////////////////////////
        virtual Weak < Surface > GetSurface() const ;
        
        ////////////////////////////////////////////////////////////
        /// \brief Adds a listener to the Surface object.
        ///
        /// \param listener Listener to add.
        ///
        ////////////////////////////////////////////////////////////
        virtual void AddSurfaceListener( const Shared < Listener > & listener );
        
        ////////////////////////////////////////////////////////////
        /// \brief Resets surface listeners.
        ///
        ////////////////////////////////////////////////////////////
        virtual void ResetSurfaceListeners( void );
        
        ////////////////////////////////////////////////////////////
        /// \brief Process events pending ( call Surface::ProcessEvents() ).
        ///
        ////////////////////////////////////////////////////////////
        virtual void ProcessEvents( void );
        
        ////////////////////////////////////////////////////////////
        /// \brief Return 'true' if the Surface is closed.
        ///
        ////////////////////////////////////////////////////////////
        virtual bool Closed( void ) const ;
        
        ////////////////////////////////////////////////////////////
        /// \brief If the internal surface is valid, calls 'Surface::Show()'.
        ///
        ////////////////////////////////////////////////////////////
        virtual void Show() const ;
        
        ////////////////////////////////////////////////////////////
        /// \brief Flush the internal context.
        ///
        ////////////////////////////////////////////////////////////
        virtual void Flush() const ;
        
        ////////////////////////////////////////////////////////////
        /// \brief Flush and ProcessEvent of this RenderWindow.
        ///
        ////////////////////////////////////////////////////////////
        virtual void Display();
        
        ////////////////////////////////////////////////////////////
        /// \brief Creates a VertexCommand.
        ///
        /// \param components VertexComponents list used to elaborate
        ///                   Buffer's related VertexComponents for the
        ///                   resulting VertexCommand.
        /// \param vcbuffers  Vertex CBuffers list used to create Vertex
        ///                   Buffers then used to generate VertexComponents.
        /// \param vcount     Number of Vertexes to draw. It is used only if
        ///                   'icount' is 0.
        /// \param icbuffer   Index CBuffer used to create the Index Buffer.
        /// \param icount     Number of Indexes to draw.
        /// \param itype      IndexType for the indexes in the resulting
        ///                   VertexCommand.
        ///
        ////////////////////////////////////////////////////////////
        virtual Shared < VertexCommand > CreateVertexCommand( const Vector < VertexComponent >& components ,
                                                              const SharedVector < CBuffer >& vcbuffers ,
                                                              uint32_t vcount ,
                                                              const Shared < CBuffer >& icbuffer = nullptr ,
                                                              uint32_t icount = 0 ,
                                                              IndexType itype = IndexType::Unknown );
        
        ////////////////////////////////////////////////////////////
        /// \brief Tries to load given list of shader files, and on success,
        /// return a Program object with every shaders bound to it.
        ///
        ////////////////////////////////////////////////////////////
        virtual Shared < Program > CreateProgram( const StringVector& shadfiles );
        
        ////////////////////////////////////////////////////////////
        /// \brief Creates a program object from given shaders. 
        ///
        ////////////////////////////////////////////////////////////
        virtual Shared < Program > CreateProgram( const SharedVector < Shader >& shaders );
        
        ////////////////////////////////////////////////////////////
        virtual void SetAutoresize( bool autoresize );
        
        ////////////////////////////////////////////////////////////
        virtual bool ShouldAutoresize() const ;
    };
}

#endif /* RenderWindow_h */
