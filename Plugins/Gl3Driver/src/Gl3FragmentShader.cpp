//  ========================================================================  //
//
//  File    : Gl3Driver/Gl3FragmentShader.cpp
//  Project : ATL/Gl3Driver
//  Author  : Luk2010
//  Date    : 08/11/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#include <Gl3Driver/Gl3FragmentShader.h>

////////////////////////////////////////////////////////////
MimeType Gl3FragmentShader::s_mime = MimeType( "Gl3Driver/shader.fragment" , { "glsl" , "frag" , "fragment" } );

////////////////////////////////////////////////////////////
Gl3FragmentShader::Gl3FragmentShader( const String& file , va_list& args )
: Gl3Shader( file , s_mime , Stage::Fragment , GL_FRAGMENT_SHADER , args )
{
    
}

////////////////////////////////////////////////////////////
Gl3FragmentShader::Gl3FragmentShader( std::istream& is , va_list& args )
: Gl3Shader( is , s_mime , Stage::Fragment , GL_FRAGMENT_SHADER , args )
{
    
}
