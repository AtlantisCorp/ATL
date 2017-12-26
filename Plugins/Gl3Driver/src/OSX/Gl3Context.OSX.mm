//  ========================================================================  //
//
//  File    : Gl3Driver/OSX/Gl3Context.OSX.mm
//  Project : ATL/Gl3Driver
//  Author  : Luk2010
//  Date    : 15/10/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#include <Gl3Driver/Gl3Context.h>
#include <Gl3Driver/Gl3VertexBuffer.h>
#include <Gl3Driver/Gl3IndexBuffer.h>
#include <Gl3Driver/OSX/Gl3PixelFormat.h>

////////////////////////////////////////////////////////////
Gl3Context::Gl3Context( const Weak < Surface >& surface , const ContextSettings& settings )
{
    assert( !surface.expired() && "Invalid parent surface given." );
    auto atlsurface = surface.lock();
    id nssurface = HandleConvert < id >( atlsurface->GetSystemHandle() );
    assert( [nssurface isKindOfClass:[NSView class]] && "Invalid parent surface class given." );
    
    NSOpenGLPixelFormat* format = Gl3ConvertContextSettings( settings );
    assert( format && "Impossible to convert pixel format." );
    
    Gl3OpenGLView* view = [[Gl3OpenGLView alloc] initWithView:nssurface andFormat:format andRequester:this];
    assert( view && "Impossible to create Gl3OpenGLView." );
    
    m_view = view ;
}

////////////////////////////////////////////////////////////
Gl3Context::~Gl3Context()
{
    glDeleteVertexArrays( m_vaos.size() , &(m_vaos.at(0)) );
    
    if ( m_view )
        [m_view release];
}

////////////////////////////////////////////////////////////
void Gl3Context::SetActive( bool active )
{
    if ( m_view )
    {
        [m_view setContextActive:(BOOL)active];
    }
}

////////////////////////////////////////////////////////////
void Gl3Context::Flush() const
{
    if ( m_view )
    {
        [m_view flushContext];
    }
}

////////////////////////////////////////////////////////////
void Gl3Context::ClearColor( const Color4& color )
{
    if ( m_view )
    {
        Color4 rgba = color.RGBA();
        [m_view clearColorFloat4:rgba.data];
    }
}
