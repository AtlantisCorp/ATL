//  ========================================================================  //
//
//  File    : Gl3Driver/Gl3VertexBuffer.h
//  Project : ATL/Gl3Driver
//  Author  : Luk2010
//  Date    : 25/10/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#ifndef Gl3VertexBuffer_h
#define Gl3VertexBuffer_h

#include <ATL/Buffer.hpp>
using namespace atl ;

#include <Gl3Driver/Gl3Includes.h>

////////////////////////////////////////////////////////////
/// \brief Defines an OpenGL3 vertex buffer.
///
////////////////////////////////////////////////////////////
class Gl3VertexBuffer : public Buffer
{
    ////////////////////////////////////////////////////////////
    Atomic < GLuint > m_glid ; ///< OpenGL buffer id.
    
public:
    
    ////////////////////////////////////////////////////////////
    Gl3VertexBuffer( const void* data , const size_t sz );
    
    ////////////////////////////////////////////////////////////
    virtual ~Gl3VertexBuffer();
    
    ////////////////////////////////////////////////////////////
    virtual void Bind();
    
    ////////////////////////////////////////////////////////////
    virtual void Unbind();
};

#endif /* Gl3VertexBuffer_h */
