//  ========================================================================  //
//
//  File    : Gl3Driver/Gl3VertexShader.cpp
//  Project : ATL/Gl3Driver
//  Author  : Luk2010
//  Date    : 08/11/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#include <Gl3Driver/Gl3VertexShader.h>

////////////////////////////////////////////////////////////
MimeType Gl3VertexShader::s_mime = MimeType( "Gl3Driver/shader.vertex" , { "glsl" , "vert" , "vertex" } );

////////////////////////////////////////////////////////////
Gl3VertexShader::Gl3VertexShader( const String& file , va_list& args )
: Gl3Shader( file , s_mime , Stage::Vertex , GL_VERTEX_SHADER , args )
{
    
}

////////////////////////////////////////////////////////////
Gl3VertexShader::Gl3VertexShader( std::istream& is , va_list& args )
: Gl3Shader( is , s_mime , Stage::Vertex , GL_VERTEX_SHADER , args )
{
    
}
