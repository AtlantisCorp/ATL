//  ========================================================================  //
//
//  File    : Gl3Driver/Gl3Context.cpp
//  Project : ATL/Gl3Driver
//  Author  : Luk2010
//  Date    : 08/11/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#include <Gl3Driver/Gl3Context.h>
#include <Gl3Driver/Gl3VertexBuffer.h>
#include <Gl3Driver/Gl3IndexBuffer.h>
#include <Gl3Driver/Gl3Program.h>
#include <Gl3Driver/Gl3VCVisitor.h>
#include <ATL/VertexCommand.hpp>
#include <ATL/Metaclass.hpp>
#include <ATL/Viewport.hpp>

////////////////////////////////////////////////////////////
String s_defvshader = R"glsl(

#version 150 core

in vec3 position ;
in vec3 color ;

out vec4 fragcolor ;

void main()
{
    gl_Position = vec4( position , 1.0 );
    fragcolor = vec4( color , 1.0 );
}

)glsl" ;

String s_deffshader = R"glsl(

#version 150 core

in vec4 fragcolor ;

out vec4 outColor ;

void main()
{
    outColor = fragcolor ;
}

)glsl" ;

////////////////////////////////////////////////////////////
GLenum GlEnumFromVertexComponent( uint32_t type )
{
    switch ( type )
    {
        case VertexComponent::R32Float:
        case VertexComponent::R32G32Float:
        case VertexComponent::R32G32B32Float:
        case VertexComponent::R32G32B32A32Float:
            return GL_FLOAT ;
            
        case VertexComponent::R32Uint:
        case VertexComponent::R32G32Uint:
        case VertexComponent::R32G32B32Uint:
        case VertexComponent::R32G32B32A32Uint:
            return GL_UNSIGNED_INT ;
            
        case VertexComponent::R32Sint:
        case VertexComponent::R32G32Sint:
        case VertexComponent::R32G32B32Sint:
        case VertexComponent::R32G32B32A32Sint:
            return GL_INT ;
            
        default:
            return GL_NONE ;
    }
}

////////////////////////////////////////////////////////////
GLenum GlEnumFromIndexType( const IndexType& type )
{
    switch( type )
    {
        case IndexType::UI8: return GL_UNSIGNED_BYTE ;
        case IndexType::UI16: return GL_UNSIGNED_SHORT ;
        case IndexType::UI32: return GL_UNSIGNED_INT ;
            
        case IndexType::I8: return GL_BYTE ;
        case IndexType::I16: return GL_SHORT ;
        case IndexType::I32: return GL_INT ;
            
        default:
            return GL_NONE ;
    }
}

////////////////////////////////////////////////////////////
Weak < Buffer > Gl3Context::CreateVertexBuffer( const void* data , const size_t sz )
{
    if ( sz > 0 )
    {
        auto buffer = std::make_shared < Gl3VertexBuffer >( data , sz );
        assert( buffer && "Invalid Gl3Buffer allocation (null)." );
        
        MutexLocker lck( m_mutex );
        m_buffers.push_back( std::static_pointer_cast < Buffer >( buffer ) );
        return buffer ;
    }
    
    return Weak < Buffer >();
}

////////////////////////////////////////////////////////////
Weak < Buffer > Gl3Context::CreateIndexBuffer( const void* data , const size_t sz )
{
    if ( sz > 0 )
    {
        auto buffer = std::make_shared < Gl3IndexBuffer >( data , sz );
        assert( buffer && "Invalid Gl3Buffer allocation (null)." );
        
        MutexLocker lck( m_mutex );
        m_buffers.push_back( std::static_pointer_cast < Buffer >( buffer ) );
        return buffer ;
    }
    
    return Weak < Buffer >();
}

////////////////////////////////////////////////////////////
Shared < Program > Gl3Context::CreateProgram( const SharedVector < Shader >& shaders )
{
    try
    {
        auto sptr = std::static_pointer_cast < Gl3Context >( shared_from_this() );
        return std::static_pointer_cast < Program >( std::make_shared < Gl3Program >( shaders , sptr ) );
    }
    
    catch( Gl3Exception const& e )
    {
        ErrorCenter::CatchException( e , Error::ProgramCreate , "Error while creating Gl3Program." );
        return nullptr ;
    }
}

////////////////////////////////////////////////////////////
Shared < Shader > Gl3Context::GetDefaultShader( Stage stage )
{
    if ( stage == Stage::Vertex )
    {
        if ( !m_defvshader )
        {
            std::istringstream is( s_defvshader );
            m_defvshader = std::static_pointer_cast < Gl3VertexShader >( Metaclass < Gl3VertexShader >().Create( is ) );
            assert( m_defvshader && "'m_defvshader' is null." );
        }
        
        return m_defvshader ;
    }
    
    else if ( stage == Stage::Fragment )
    {
        if ( !m_deffshader )
        {
            std::istringstream is( s_deffshader );
            m_deffshader = std::static_pointer_cast < Gl3FragmentShader >( Metaclass < Gl3FragmentShader >().Create( is ) );
            assert( m_deffshader && "'m_deffshader' is null." );
        }
        
        return m_deffshader ;
    }
    
    return nullptr ;
}

////////////////////////////////////////////////////////////
void Gl3Context::DrawVertexCommand( const Shared < VertexCommand >& command , const Program& program ) const
{
    Gl3VAOGetterVisitor visitor ;
    command -> AcceptVisitor( visitor );
    GLuint* VAO = visitor.VAO;
    
    if ( !VAO )
    {
        MutexLocker lck( m_mutex );
        const_cast< Gl3Context* >(this)->m_vaos.push_back( 0 );
        VAO = &(const_cast< Gl3Context* >(this)->m_vaos.back());
        
        glGenVertexArrays( 1 , VAO );
        Gl3VAOSetterVisitor setter( VAO );
        command -> AcceptVisitor( setter );
    }
    
    glBindVertexArray( *VAO );
    assert( glGetError() == GL_NO_ERROR && "'glBindVertexArray()' failed." );
    
    auto components = command -> GetVertexComponents();
    auto layout     = program.GetVertexLayout().lock();
    auto enabled    = Vector < GLuint >();
    
    for ( auto const& component : components )
    {
        auto buffer = component.GetBuffer();
        if ( buffer.expired() ) continue ;
        
        auto attribute = layout->GetAttribute( component.GetAttribute() );
        if ( !attribute ) continue ;
        
        buffer.lock()->Bind();
        
        GLuint    index      = static_cast < GLuint >( attribute -> GetSlot() );
        GLint     size       = static_cast < GLint >( component.GetElementCount() );
        GLenum    type       = GlEnumFromVertexComponent( component.GetType() );
        GLboolean normalized = false ;
        GLsizei   stride     = static_cast < GLsizei >( component.GetStride() );
        GLvoid*   pointer    = reinterpret_cast < GLvoid* >( component.GetOffset() );
        
        glEnableVertexAttribArray( index );
        enabled.push_back( index );
        
        glVertexAttribPointer(index, size, type, normalized, stride, pointer);
        assert( glGetError() == GL_NO_ERROR && "'glVertexAttribPointer()' failed." );
        
        buffer.lock()->Unbind();
    }
    
    if ( command -> GetIndexBuffer().expired() )
    {
        GLenum  mode  = GL_TRIANGLES ;
        GLint   first = 0 ;
        GLsizei count = static_cast < GLsizei >( command -> GetVertexCount() );
        
        glDrawArrays(mode, first, count);
        assert( glGetError() == GL_NO_ERROR && "'glDrawArrays()' failed." );
    }
    
    else
    {
        auto indexbuffer = command->GetIndexBuffer().lock();
        assert( indexbuffer && "'indexbuffer' expired while looking for it." );
        
        indexbuffer -> Bind();
        
        GLenum mode = GL_TRIANGLES ;
        GLsizei count = static_cast < GLsizei >( command -> GetIndexCount() );
        GLenum type = GlEnumFromIndexType( command -> GetIndexType() );
        GLvoid* offset = (GLvoid*) 0 ;
        
        glDrawElements(mode, count, type, offset);
        assert( glGetError() == GL_NO_ERROR && "'glDrawElements()' failed." );
        
        indexbuffer -> Unbind();
    }
    
    for ( auto index : enabled )
    {
        glDisableVertexAttribArray( index );
    }
}

////////////////////////////////////////////////////////////
void Gl3Context::BindViewport( const Viewport& viewport ) const
{
    glViewport( static_cast < GLint >( viewport.origin.x ) , static_cast < GLint >( viewport.origin.y ) ,
                static_cast < GLsizei >( viewport.size.width ) , static_cast < GLint >( viewport.size.height ) );
}
