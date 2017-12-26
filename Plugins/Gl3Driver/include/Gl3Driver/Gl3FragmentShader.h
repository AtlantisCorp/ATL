//  ========================================================================  //
//
//  File    : Gl3Driver/Gl3FragmentShader.h
//  Project : ATL/Gl3Driver
//  Author  : Luk2010
//  Date    : 08/11/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#ifndef Gl3FragmentShader_h
#define Gl3FragmentShader_h

#include <Gl3Driver/Gl3Shader.h>

////////////////////////////////////////////////////////////
/// \brief Specialization of Gl3Shader for Stage::Fragment, i.e.
/// GL_FRAGMENT_SHADER.
///
////////////////////////////////////////////////////////////
class Gl3FragmentShader : public Gl3Shader
{
public:
    
    ////////////////////////////////////////////////////////////
    /// \brief MIME type representing this class.
    static MimeType s_mime ;
    
    ////////////////////////////////////////////////////////////
    Gl3FragmentShader( const String& file , va_list& args );
    
    ////////////////////////////////////////////////////////////
    Gl3FragmentShader( std::istream& is , va_list& args );
};

#endif /* Gl3FragmentShader_h */
