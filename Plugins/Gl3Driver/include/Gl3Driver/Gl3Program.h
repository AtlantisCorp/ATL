//  ========================================================================  //
//
//  File    : Gl3Driver/Gl3Program.h
//  Project : ATL/Gl3Driver
//  Author  : Luk2010
//  Date    : 11/11/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#ifndef Gl3Program_h
#define Gl3Program_h

#include <Gl3Driver/Gl3Includes.h>
#include <ATL/Program.hpp>
using namespace atl ;

////////////////////////////////////////////////////////////
class Gl3Context ;

////////////////////////////////////////////////////////////
/// \brief OpenGL3 specialization of atl::Program.
///
/// On initialization (construction), the program attaches the
/// given shaders and links itself by using glLinkProgram.
/// Once the program is linked (and no error occured), parameters
/// are discovered one by one and added to the parent Program
/// class.
///
////////////////////////////////////////////////////////////
class Gl3Program : public atl::Program
{
    ////////////////////////////////////////////////////////////
    Atomic < GLuint >       m_glid ;      ///< OpenGL handle.
    mutable Spinlock        m_spinlock ;  ///< Access to texture units.
    Map < GLuint , GLuint > m_texunits ;  ///< Texture units by OpenGL uniform's indexes.
    Atomic < GLuint >       m_countunit ; ///< Number of texture units used by this program. Texture units are
                                          ///  activated from 'GL_TEXTURE0' to 'GL_TEXTURE0 + m_countunit - 1'.
    Weak < Gl3Context >     m_context ;   ///< Context that created this Program. When destroying the program,
                                          ///  glDeleteProgram is called only if this context is valid and bound
                                          ///  to the current thread calling this destructor, thus waiting for the
                                          ///  context to be ready and preventing concurrent accesses.
    
public:
    
    ////////////////////////////////////////////////////////////
    Gl3Program( const SharedVector < Shader >& shaders , const Weak < Gl3Context >& context );
    
    ////////////////////////////////////////////////////////////
    virtual ~Gl3Program();
    
    ////////////////////////////////////////////////////////////
    void Prepare( const RenderTarget& target ) const ;
    
protected:
    
    ////////////////////////////////////////////////////////////
    /// \brief Binds the given parameter by its index to the
    /// program.
    ///
    /// 'Prepare' must have been called before using this function
    /// by the rendertarget. When binding a texture, OpenGL actually
    /// binds texture units to a sampler and the texture is bound to
    /// the sampler unit in the following way:
    ///
    /// glActiveTexture( GL_TEXTURE0 + texture_unit );
    /// glBindTexture( texture_id );
    ///
    /// However, the texture unit must be bound to the parameter before
    /// everything. This way, for example, in a program that hold two textures
    /// (diffuse_tex and specular_tex) :
    ///
    /// glUniform1i( diffuse_tex , 0 );
    /// glUniform1i( specular_tex , 1 );
    ///
    /// The texture is then bound to the corresponding texture unit, but the
    /// program is already bound to its sampler's units. When binding a Texture
    /// object (parameter value is a Texture and parameter is the parameter
    /// where the texture should be bound), it will check if the parameter has
    /// a texture unit associated to it and will activate this texture unit
    /// to bind the texture to it. If the given parameter is not related to
    /// a texture unit, the binding is discarded and an error is launched to
    /// the ErrorCenter.
    ///
    ////////////////////////////////////////////////////////////
    void BindParameter( const ConstantParameter* parameter , const ParameterValue& value ) const ;
    
    ////////////////////////////////////////////////////////////
    /// \brief Constructs the attribute's list (Vertex layout) for the
    /// given current program.
    ///
    ////////////////////////////////////////////////////////////
    void GlMakeLayout( GLuint glid );
    
    ////////////////////////////////////////////////////////////
    /// \brief Constructs the parameter's list for the given current
    /// program.
    ///
    ////////////////////////////////////////////////////////////
    void GlMakeParameters( GLuint glid );
};

#endif /* Gl3Program_h */
