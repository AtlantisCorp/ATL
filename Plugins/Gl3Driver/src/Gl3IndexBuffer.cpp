//  ========================================================================  //
//
//  File    : Gl3Driver/Gl3IndexBuffer.cpp
//  Project : ATL/Gl3Driver
//  Author  : Luk2010
//  Date    : 25/10/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#include <Gl3Driver/Gl3IndexBuffer.h>

////////////////////////////////////////////////////////////
Gl3IndexBuffer::Gl3IndexBuffer( const void* data , const size_t sz )
{
    GLuint id = 0 ;
    glGenBuffers( 1 , &id );
    m_glid.store( id );
    assert( id && "glGenBuffers() failed." );
    
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER , id );
    
    glBufferData( GL_ELEMENT_ARRAY_BUFFER , sz , data , GL_STREAM_DRAW );
    assert( glGetError() == GL_NO_ERROR && "glBufferData() failed." );
    
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER , 0 );
}

////////////////////////////////////////////////////////////
Gl3IndexBuffer::~Gl3IndexBuffer()
{
    GLuint id = m_glid.load();
    glDeleteBuffers( 1 , &id );
}

////////////////////////////////////////////////////////////
void Gl3IndexBuffer::Bind()
{
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER , m_glid.load() );
}

////////////////////////////////////////////////////////////
void Gl3IndexBuffer::Unbind()
{
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER , 0 );
}
