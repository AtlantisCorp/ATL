//  ========================================================================  //
//
//  File    : Gl3Driver/Gl3Shader.h
//  Project : ATL/Gl3Driver
//  Author  : Luk2010
//  Date    : 06/11/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#ifndef Gl3Shader_h
#define Gl3Shader_h

#include <Gl3Driver/Gl3Includes.h>
#include <ATL/Shader.hpp>
using namespace atl ;

////////////////////////////////////////////////////////////
/// \brief Defines a generic shader interface to create OpenGL
/// shaders.
///
////////////////////////////////////////////////////////////
class Gl3Shader : public Shader
{
    ////////////////////////////////////////////////////////////
    Atomic < GLuint > m_glid ;
    
public:
    
    ////////////////////////////////////////////////////////////
    /// \brief Creates a Gl3Shader from a file.
    ///
    /// \param file    File to load the shader's source from.
    /// \param mime    MIME type the shader resource was loaded from.
    /// \param stage   Given by the derived class, the Stage it refers
    ///                to.
    /// \param glstage Given by the derived class, the corresponding
    ///                OpenGL stage it refers to. This stage will be
    ///                used to create the shader.
    /// \param args    For now, not used. May be used later to pass
    ///                custom compilation arguments to the shader.
    ///
    /// \note Gl3Shader's constructor does not follow the Metaclass
    /// constructor's pattern. However, derived class must follow
    /// this pattern to enable Metaclass to create those derived
    /// objects. The derived class must also give the Gl3Shader the
    /// ATL's stage and the OpenGL corresponding stage to this class
    /// to create the shader object.
    ///
    /// \note On failure, a Gl3Exception object is threw with the
    /// corresponding Gl3Error code.
    ///
    ////////////////////////////////////////////////////////////
    Gl3Shader( const String& file , const MimeType& mime , Stage stage , GLenum glstage , va_list& args );
    
    ////////////////////////////////////////////////////////////
    /// \brief Creates a shader from the input stream given.
    ///
    /// \param is    Input stream to use instead of a file for the
    ///              shader source.
    /// \param mime    MIME type the shader resource was loaded from.
    /// \param stage   Given by the derived class, the Stage it refers
    ///                to.
    /// \param glstage Given by the derived class, the corresponding
    ///                OpenGL stage it refers to. This stage will be
    ///                used to create the shader.
    /// \param args    For now, not used. May be used later to pass
    ///                custom compilation arguments to the shader.
    ///
    /// \note Gl3Shader's constructor does not follow the Metaclass
    /// constructor's pattern. However, derived class must follow
    /// this pattern to enable Metaclass to create those derived
    /// objects. The derived class must also give the Gl3Shader the
    /// ATL's stage and the OpenGL corresponding stage to this class
    /// to create the shader object.
    ///
    /// \note On failure, a Gl3Exception object is threw with the
    /// corresponding Gl3Error code.
    ////////////////////////////////////////////////////////////
    Gl3Shader( std::istream& is , const MimeType& mime , Stage stage , GLenum glstage , va_list& args );
    
    ////////////////////////////////////////////////////////////
    virtual ~Gl3Shader();
    
    ////////////////////////////////////////////////////////////
    GLuint GetGlId() const ;
    
private:
    
    ////////////////////////////////////////////////////////////
    /// \brief Internally load the shader from the given source.
    ///
    /// \param source  Source of the future shader to be compiled.
    /// \param glstage Given by the derived class, the corresponding
    ///                OpenGL stage it refers to. This stage will be
    ///                used to create the shader.
    /// \param args    For now, not used. May be used later to pass
    ///                custom compilation arguments to the shader.
    ///
    /// \note On failure, a Gl3Exception object is threw with the
    /// corresponding Gl3Error code.
    ///
    ////////////////////////////////////////////////////////////
    void iGl3Shader( const String& source , GLenum glstage , va_list& args );
};

#endif /* Gl3Shader_h */
