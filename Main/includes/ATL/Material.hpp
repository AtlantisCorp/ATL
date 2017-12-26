//  ========================================================================  //
//
//  File    : ATL/Material.hpp
//  Project : atlresource
//  Author  : Luk2010
//  Date    : 17/10/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#ifndef Material_hpp
#define Material_hpp

#include <ATL/StdIncludes.hpp>
#include <ATL/Resource.hpp>
#include <ATL/ParameterValue.hpp>
#include <ATL/Alias.hpp>

namespace atl
{
    ////////////////////////////////////////////////////////////
    class Program ;
    
    ////////////////////////////////////////////////////////////
    /// \brief Defines a material object.
    ///
    ////////////////////////////////////////////////////////////
    class Material : public Resource
    {
        ////////////////////////////////////////////////////////////
        glm::vec4                 m_ambient ;     ///< Ambient color. (MaterialAmbient)
        glm::vec4                 m_diffuse ;     ///< Diffuse color. (MaterialDiffuse)
        glm::vec4                 m_specular ;    ///< Specular color. (MaterialSpecular)
        float                     m_shininess ;   ///< Shininess value. (MaterialShininess)
        Weak < Texture >          m_texambient ;  ///< Ambient texture. (MaterialTextureAmbient)
        Weak < Texture >          m_texdiffuse ;  ///< Diffuse texture. (MaterialTextureDiffuse)
        Weak < Texture >          m_texspecular ; ///< Specular texture. (MaterialTextureSpecular)
        WeakVector < Texture >    m_textures ;    ///< Other textures. (MaterialTexture1 to 4)
        Vector < ParameterValue > m_customs ;     ///< Other parameters. (MaterialComponent1 to 5)
        String                    m_name ;        ///< Name given to this materia.
        mutable Mutex             m_mutex ;       ///< Access to those data.
        
    public:
        
        ////////////////////////////////////////////////////////////
        Material();
        
        ////////////////////////////////////////////////////////////
        virtual ~Material();
        
        ////////////////////////////////////////////////////////////
        /// \brief Prepares the material for use with the given program.
        ///
        /// Binds every possible data to the program using every Material's
        /// Aliases as described for each data. Program must handle Material's
        /// Aliases for the binding to be done correctly.
        ///
        ////////////////////////////////////////////////////////////
        void Prepare( const Program& program );
        
        ////////////////////////////////////////////////////////////
        virtual const glm::vec4 GetAmbient() const ;
        
        ////////////////////////////////////////////////////////////
        virtual void SetAmbient( const glm::vec4& ambient );
        
        ////////////////////////////////////////////////////////////
        virtual const glm::vec4 GetDiffuse() const ;
        
        ////////////////////////////////////////////////////////////
        virtual void SetDiffuse( const glm::vec4& diffuse );
        
        ////////////////////////////////////////////////////////////
        virtual const glm::vec4 GetSpecular() const ;
        
        ////////////////////////////////////////////////////////////
        virtual void SetSpecular( const glm::vec4& specular );
        
        ////////////////////////////////////////////////////////////
        virtual float GetShininess() const ;
        
        ////////////////////////////////////////////////////////////
        virtual void SetShininess( float shininess );
        
        ////////////////////////////////////////////////////////////
        virtual const Weak < Texture > GetTextureAmbient() const ;
        
        ////////////////////////////////////////////////////////////
        virtual void SetTextureAmbient( const Weak < Texture >& texture );
        
        ////////////////////////////////////////////////////////////
        virtual const Weak < Texture > GetTextureDiffuse() const ;
        
        ////////////////////////////////////////////////////////////
        virtual void SetTextureDiffuse( const Weak < Texture >& texture );
        
        ////////////////////////////////////////////////////////////
        virtual const Weak < Texture > GetTextureSpecular() const ;
        
        ////////////////////////////////////////////////////////////
        virtual void SetTextureSpecular( const Weak < Texture >& texture );
        
        ////////////////////////////////////////////////////////////
        virtual const Weak < Texture > GetTexture( Alias alias ) const ;
        
        ////////////////////////////////////////////////////////////
        virtual void SetTexture( Alias alias , const Weak < Texture >& texture );
        
        ////////////////////////////////////////////////////////////
        virtual const ParameterValue GetCustom( Alias alias ) const ;
        
        ////////////////////////////////////////////////////////////
        virtual void SetCustom( Alias alias , const ParameterValue& value );
        
        ////////////////////////////////////////////////////////////
        virtual const String GetName() const ;
        
        ////////////////////////////////////////////////////////////
        virtual void SetName( const String& name );
        
        ////////////////////////////////////////////////////////////
        virtual void SetTextures( const WeakVector < Texture >& textures );
        
        ////////////////////////////////////////////////////////////
        virtual WeakVector < Texture > GetTextures() const ;
    };
}

#endif /* Material_hpp */
