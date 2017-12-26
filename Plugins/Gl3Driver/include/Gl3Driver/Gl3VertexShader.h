//  ========================================================================  //
//
//  File    : Gl3Driver/Gl3VertexShader.h
//  Project : ATL/Gl3Driver
//  Author  : Luk2010
//  Date    : 08/11/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#ifndef Gl3VertexShader_h
#define Gl3VertexShader_h

#include <Gl3Driver/Gl3Shader.h>

////////////////////////////////////////////////////////////
/// \brief Specialization of Gl3Shader for Stage::Vertex, i.e.
/// GL_VERTEX_SHADER.
///
////////////////////////////////////////////////////////////
class Gl3VertexShader : public Gl3Shader
{
public:
    
    ////////////////////////////////////////////////////////////
    /// \brief MIME type representing this class.
    static MimeType s_mime ;
    
    ////////////////////////////////////////////////////////////
    Gl3VertexShader( const String& file , va_list& args );
    
    ////////////////////////////////////////////////////////////
    Gl3VertexShader( std::istream& is , va_list& args );
};

#endif /* Gl3VertexShader_h */
