//  ========================================================================  //
//
//  File    : Gl3Driver/Gl3VertexBuffer.cpp
//  Project : ATL/Gl3Driver
//  Author  : Luk2010
//  Date    : 25/10/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#include <Gl3Driver/Gl3VertexBuffer.h>

////////////////////////////////////////////////////////////
Gl3VertexBuffer::Gl3VertexBuffer( const void* data , const size_t sz )
{
    assert( glGetError() == GL_NO_ERROR && "OpenGL error occured before this function." );
    
    GLuint id = 0 ;
    glGenBuffers( 1 , &id );
    assert( id && "glGenBuffers() failed." );
    
    m_glid.store( id );
    
    glBindBuffer( GL_ARRAY_BUFFER , id );
    assert( glGetError() == GL_NO_ERROR && "glBindBuffer() failed." );
    
    glBufferData( GL_ARRAY_BUFFER , sz , data , GL_STREAM_DRAW );
    assert( glGetError() == GL_NO_ERROR && "glBufferData() failed." );
    
    glBindBuffer( GL_ARRAY_BUFFER , 0 );
    assert( glGetError() == GL_NO_ERROR && "glBindBuffer() failed." );
}

////////////////////////////////////////////////////////////
Gl3VertexBuffer::~Gl3VertexBuffer()
{
    GLuint id = m_glid.load();
    glDeleteBuffers( 1 , &id );
    assert( glGetError() == GL_NO_ERROR && "glDeleteBuffers() failed." );
}

////////////////////////////////////////////////////////////
void Gl3VertexBuffer::Bind()
{
    glBindBuffer( GL_ARRAY_BUFFER , m_glid.load() );
}

////////////////////////////////////////////////////////////
void Gl3VertexBuffer::Unbind()
{
    glBindBuffer( GL_ARRAY_BUFFER , 0 );
}
