//  ========================================================================  //
//
//  File    : Gl3Driver/Gl3Context.h
//  Project : ATL/Gl3Driver
//  Author  : Luk2010
//  Date    : 15/10/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#ifndef Gl3Context_h
#define Gl3Context_h

#include <Gl3Driver/Gl3Includes.h>
#include <Gl3Driver/Gl3VertexShader.h>
#include <Gl3Driver/Gl3FragmentShader.h>

#include <ATL/ContextSettings.hpp>
#include <ATL/Context.hpp>
#include <ATL/Surface.hpp>
#include <ATL/Program.hpp>

using namespace atl ;

#if ATL_PLATFORM == ATL_PLATFORM_DARWIN

#   ifdef __OBJC__
#       include <Gl3Driver/OSX/Gl3OpenGLView.h>
        typedef Gl3OpenGLView* Gl3OpenGLViewRef ;
#   else
        typedef void* Gl3OpenGLViewRef ;
#   endif

#endif

////////////////////////////////////////////////////////////
/// \brief Defines a multiplatform OpenGL3 Context.
///
/// ( OSX ) : It is defined by a custom Gl3OpenGLView object that
/// derives from NSView. Its parent is always a NSView (see OSXWindow
/// plugin for implementation detail). At creation, it will use the
/// context settings as pixel format settings and will create a new
/// Gl3OpenGLView. This view will create a NSOpenGLPixelFormat and
/// a NSOpenGLContext and maintain them. Sharing this context with
/// other RenderTarget is possible.
///
////////////////////////////////////////////////////////////
class Gl3Context : public atl::Context
{

    ////////////////////////////////////////////////////////////
#if ATL_PLATFORM == ATL_PLATFORM_DARWIN
    Gl3OpenGLViewRef m_view ;
#endif
    
    ////////////////////////////////////////////////////////////
    SharedVector < Buffer >      m_buffers ;    ///< Buffers created by this Context.
    Shared < Gl3VertexShader >   m_defvshader ; ///< Default Vertex Shader.
    Shared < Gl3FragmentShader > m_deffshader ; ///< Default Fragment Shader.
    mutable Mutex                m_mutex ;      ///< Access to vector data.
    Vector < GLuint >            m_vaos ;       ///< VAOs created for VertexCommands.
    
public:
    
    ////////////////////////////////////////////////////////////
    /// \brief Creates a Gl3Context.
    ///
    /// ( OSX ) : Creates a NSOpenGLPixelFormat from ContextSettings
    /// and initializes a Gl3OpenGLView with that format. The view is
    /// then set as a subchild of the given surface, and takes its
    /// frame as size. Autoresizing must occur to resize the view.
    /// When viewWillStartLiveResizing, the gl context is not updated
    /// and when viewDidEndLiveResizing, the gl context is updated again.
    ///
    ////////////////////////////////////////////////////////////
    Gl3Context( const Weak < Surface >& surface , const ContextSettings& settings );
    
    ////////////////////////////////////////////////////////////
    virtual ~Gl3Context();
    
    ////////////////////////////////////////////////////////////
    virtual void SetActive( bool active );
    
    ////////////////////////////////////////////////////////////
    virtual void Flush() const ;
    
    ////////////////////////////////////////////////////////////
    virtual void ClearColor( const Color4& color );
    
    ////////////////////////////////////////////////////////////
    /// \brief Creates a vertex buffer (the context must be active
    /// before calling this function).
    ///
    /// \param data Data to initialize the buffer with. If null, the
    ///        behaviour is not defined but APIs should be able to
    ///        create empty buffers of given size.
    /// \param size Size of the data in bytes.
    ///
    /// \note The returned buffer is owned only by the context object.
    /// At destruction, the context must destroy the buffers and invalidate
    /// every Weak pointers.
    ///
    ////////////////////////////////////////////////////////////
    virtual Weak < Buffer > CreateVertexBuffer( const void* data , const size_t sz );
    
    ////////////////////////////////////////////////////////////
    /// \brief Creates an index buffer (the context must be active
    /// before calling this function).
    ///
    /// \param data Data to initialize the buffer with. If null, the
    ///        behaviour is not defined but APIs should be able to
    ///        create empty buffers of given size.
    /// \param size Size of the data in bytes.
    ///
    /// \note The returned buffer is owned only by the context object.
    /// At destruction, the context must destroy the buffers and invalidate
    /// every Weak pointers.
    ///
    ////////////////////////////////////////////////////////////
    virtual Weak < Buffer > CreateIndexBuffer( const void* data , const size_t sz );
    
    ////////////////////////////////////////////////////////////
    /// \brief Creates a Program from given loaded shader list.
    ///
    /// \param shaders A list of shaders created by the metaclass
    /// and under this context.
    ///
    /// \return A loaded Program object, that is not owned by the
    /// Context but which use must be done within this Context.
    ///
    ////////////////////////////////////////////////////////////
    virtual Shared < Program > CreateProgram( const SharedVector < Shader >& shaders );
    
    ////////////////////////////////////////////////////////////
    /// \brief Returns a Shader always available for given Stage, if
    /// it exists, or a null shared pointer.
    ///
    /// \note If the shader exists but is not loaded yet, this function
    /// is allowed to load it synchroneously when called.
    ///
    ////////////////////////////////////////////////////////////
    virtual Shared < Shader > GetDefaultShader( Stage stage );
    
    ////////////////////////////////////////////////////////////
    /// \brief Draw the given VertexCommand.
    ///
    /// \param command VertexCommand to draw (Can't be expired).
    ///
    ////////////////////////////////////////////////////////////
    virtual void DrawVertexCommand( const Shared < VertexCommand >& command , const Program& program ) const ;
    
    ////////////////////////////////////////////////////////////
    virtual void BindViewport( const Viewport& viewport ) const ;
};

#endif /* Gl3Context_h */
