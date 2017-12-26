//  ========================================================================  //
//
//  File    : ATL/Context.hpp
//  Project : atlresource
//  Author  : Luk2010
//  Date    : 25/09/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#ifndef Context_hpp
#define Context_hpp

#include <ATL/StdIncludes.hpp>
#include <ATL/Color.hpp>
#include <ATL/Buffer.hpp>
#include <ATL/Stage.hpp>

namespace atl
{
    ////////////////////////////////////////////////////////////
    class Shader ;
    class Program ;
    class RenderCommand ;
    class VertexCommand ;
    struct Viewport ;
    
    ////////////////////////////////////////////////////////////
    /// \brief Defines a driver-created Context abstract object.
    ///
    ////////////////////////////////////////////////////////////
    class Context : public std::enable_shared_from_this < Context >
    {
    public:
        
        ////////////////////////////////////////////////////////////
        Context();
        
        ////////////////////////////////////////////////////////////
        virtual ~Context();
        
        ////////////////////////////////////////////////////////////
        /// \brief Makes the context active (or not).
        ///
        ////////////////////////////////////////////////////////////
        virtual void SetActive( bool active ) = 0 ;
        
        ////////////////////////////////////////////////////////////
        /// \brief Flush the context, swapping back and front buffer.
        ///
        ////////////////////////////////////////////////////////////
        virtual void Flush() const = 0 ;
        
        ////////////////////////////////////////////////////////////
        /// \brief Changes the internal clearing for color buffer.
        ///
        ////////////////////////////////////////////////////////////
        virtual void ClearColor( const Color4& color ) = 0 ;
        
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
        virtual Weak < Buffer > CreateVertexBuffer( const void* data , const size_t sz ) = 0 ;
        
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
        virtual Weak < Buffer > CreateIndexBuffer( const void* data , const size_t sz ) = 0 ;
        
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
        virtual Shared < Program > CreateProgram( const SharedVector < Shader >& shaders ) = 0 ;
        
        ////////////////////////////////////////////////////////////
        /// \brief Returns a Shader always available for given Stage, if
        /// it exists, or a null shared pointer.
        ///
        /// \note If the shader exists but is not loaded yet, this function
        /// is allowed to load it synchroneously when called.
        ///
        ////////////////////////////////////////////////////////////
        virtual Shared < Shader > GetDefaultShader( Stage stage ) = 0 ;
        
        ////////////////////////////////////////////////////////////
        /// \brief Draw a RenderCommand.
        ///
        /// \param command Weak pointer to the requested command to
        ///                draw to the currently bound context.
        /// \param program Reference guaranteed to be valid and retained
        ///                by the current RenderPass drawing its renderqueues.
        ///
        /// \note RenderCommand's parameters are already bound by the
        /// appropriate RenderQueue. Context should bind command's input
        /// (VertexLayout) to the program, and draw the underlying VertexCommand
        /// without taking care of program's binding. However, it should also
        /// bind appropriate buffers.
        ///
        ////////////////////////////////////////////////////////////
        virtual void DrawRenderCommand( const Weak < RenderCommand >& command , const Program& program ) const ;
        
        ////////////////////////////////////////////////////////////
        /// \brief Draw the given VertexCommand.
        ///
        /// Normally uses of this function should be preceded by a call
        /// to 'RenderWindow::Begin()' or 'Context::SetActive(true)', or
        /// any other function that call 'Context::SetActive()' (this can
        /// be 'RenderWindow::Draw()').
        ///
        /// The current context is picked up to draw the given VertexCommand,
        /// but nothing is done except this action. This is the final function
        /// call for the drawing cascade from RenderWindow to RenderPass.
        ///
        /// \param command VertexCommand to draw (Can't be expired).
        ///
        ////////////////////////////////////////////////////////////
        virtual void DrawVertexCommand( const Shared < VertexCommand >& command , const Program& program ) const = 0 ;
        
        ////////////////////////////////////////////////////////////
        /// \brief Binds the Viewport for the current Rasterizer Stage.
        ///
        ////////////////////////////////////////////////////////////
        virtual void BindViewport( const Viewport& viewport ) const = 0 ;
    };
}

#endif // Context_hpp
