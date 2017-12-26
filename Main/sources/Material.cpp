//  ========================================================================  //
//
//  File    : ATL/Material.cpp
//  Project : atlresource
//  Author  : Luk2010
//  Date    : 20/10/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#include <ATL/Material.hpp>
#include <ATL/Program.hpp>

namespace atl
{
    ////////////////////////////////////////////////////////////
    Material::Material() : Resource()
    {
        m_textures.insert( m_textures.end() , 4 , Weak < Texture >() );
        m_customs.insert( m_customs.end() , 5 , ParameterValue() );
    }
    
    ////////////////////////////////////////////////////////////
    Material::~Material()
    {
        
    }
    
    ////////////////////////////////////////////////////////////
    void Material::Prepare( const Program& program )
    {
        MutexLocker lck( m_mutex );
        program.BindAlias( Alias::MaterialAmbient , ParameterValue( m_ambient ) );
        program.BindAlias( Alias::MaterialDiffuse , ParameterValue( m_diffuse ) );
        program.BindAlias( Alias::MaterialSpecular , ParameterValue( m_specular ) );
        program.BindAlias( Alias::MaterialShininess , ParameterValue( m_shininess ) );
        program.BindAlias( Alias::MaterialTextureAmbient , ParameterValue( m_texambient ) );
        program.BindAlias( Alias::MaterialTextureDiffuse , ParameterValue( m_texdiffuse ) );
        program.BindAlias( Alias::MaterialTextureSpecular , ParameterValue( m_texspecular ) );
        program.BindAlias( Alias::MaterialTexture1 , ParameterValue( m_textures.at( 0 ) ) );
        program.BindAlias( Alias::MaterialTexture2 , ParameterValue( m_textures.at( 1 ) ) );
        program.BindAlias( Alias::MaterialTexture3 , ParameterValue( m_textures.at( 2 ) ) );
        program.BindAlias( Alias::MaterialTexture4 , ParameterValue( m_textures.at( 3 ) ) );
        program.BindAlias( Alias::MaterialComponent1 , m_customs.at( 0 ) );
        program.BindAlias( Alias::MaterialComponent2 , m_customs.at( 1 ) );
        program.BindAlias( Alias::MaterialComponent3 , m_customs.at( 2 ) );
        program.BindAlias( Alias::MaterialComponent4 , m_customs.at( 3 ) );
        program.BindAlias( Alias::MaterialComponent5 , m_customs.at( 4 ) );
    }
    
    ////////////////////////////////////////////////////////////
    const glm::vec4 Material::GetAmbient() const
    {
        MutexLocker lck( m_mutex );
        return m_ambient ;
    }
    
    ////////////////////////////////////////////////////////////
    void Material::SetAmbient( const glm::vec4& ambient )
    {
        MutexLocker lck( m_mutex );
        m_ambient = ambient ;
    }
    
    ////////////////////////////////////////////////////////////
    const glm::vec4 Material::GetDiffuse() const
    {
        MutexLocker lck( m_mutex );
        return m_diffuse ;
    }
    
    ////////////////////////////////////////////////////////////
    void Material::SetDiffuse( const glm::vec4& diffuse )
    {
        MutexLocker lck( m_mutex );
        m_diffuse = diffuse ;
    }
    
    ////////////////////////////////////////////////////////////
    const glm::vec4 Material::GetSpecular() const
    {
        MutexLocker lck( m_mutex );
        return m_specular ;
    }
    
    ////////////////////////////////////////////////////////////
    void Material::SetSpecular( const glm::vec4& specular )
    {
        MutexLocker lck( m_mutex );
        m_specular = specular ;
    }
    
    ////////////////////////////////////////////////////////////
    float Material::GetShininess() const
    {
        MutexLocker lck( m_mutex );
        return m_shininess ;
    }
    
    ////////////////////////////////////////////////////////////
    void Material::SetShininess( float shininess )
    {
        MutexLocker lck( m_mutex );
        m_shininess = shininess ;
    }
    
    ////////////////////////////////////////////////////////////
    const Weak < Texture > Material::GetTextureAmbient() const
    {
        MutexLocker lck( m_mutex );
        return m_texambient ;
    }
    
    ////////////////////////////////////////////////////////////
    void Material::SetTextureAmbient( const Weak < Texture >& texambient )
    {
        MutexLocker lck( m_mutex );
        m_texambient = texambient ;
    }
    
    ////////////////////////////////////////////////////////////
    const Weak < Texture > Material::GetTextureDiffuse() const
    {
        MutexLocker lck( m_mutex );
        return m_texdiffuse ;
    }
    
    ////////////////////////////////////////////////////////////
    void Material::SetTextureDiffuse( const Weak < Texture >& texdiffuse )
    {
        MutexLocker lck( m_mutex );
        m_texdiffuse = texdiffuse ;
    }
    
    ////////////////////////////////////////////////////////////
    const Weak < Texture > Material::GetTextureSpecular() const
    {
        MutexLocker lck( m_mutex );
        return m_texspecular ;
    }
    
    ////////////////////////////////////////////////////////////
    void Material::SetTextureSpecular( const Weak < Texture >& texspecular )
    {
        MutexLocker lck( m_mutex );
        m_texspecular = texspecular ;
    }
    
    ////////////////////////////////////////////////////////////
    const Weak < Texture > Material::GetTexture( Alias alias ) const
    {
        MutexLocker lck( m_mutex );
        
        switch (alias)
        {
            case Alias::MaterialTexture1: return m_textures.at( 0 );
            case Alias::MaterialTexture2: return m_textures.at( 1 );
            case Alias::MaterialTexture3: return m_textures.at( 2 );
            case Alias::MaterialTexture4: return m_textures.at( 3 );
            default: return Weak < Texture >();
        }
    }
    
    ////////////////////////////////////////////////////////////
    void Material::SetTexture( Alias alias , const Weak < Texture >& texture )
    {
        MutexLocker lck( m_mutex );
        
        switch (alias)
        {
            case Alias::MaterialTexture1:
                m_textures[0] = texture ;
                break ;
                
            case Alias::MaterialTexture2:
                m_textures[1] = texture ;
                break ;
                
            case Alias::MaterialTexture3:
                m_textures[2] = texture ;
                break ;
                
            case Alias::MaterialTexture4:
                m_textures[3] = texture ;
                break ;
                
            default:
                break ;
        }
    }
    
    ////////////////////////////////////////////////////////////
    const ParameterValue Material::GetCustom( Alias alias ) const
    {
        MutexLocker lck( m_mutex );
        
        switch (alias)
        {
            case Alias::MaterialComponent1: return m_customs.at( 0 );
            case Alias::MaterialComponent2: return m_customs.at( 1 );
            case Alias::MaterialComponent3: return m_customs.at( 2 );
            case Alias::MaterialComponent4: return m_customs.at( 3 );
            case Alias::MaterialComponent5: return m_customs.at( 4 );
            default: return ParameterValue();
        }
    }
    
    ////////////////////////////////////////////////////////////
    void Material::SetCustom( Alias alias , const ParameterValue& value )
    {
        MutexLocker lck( m_mutex );
        
        switch (alias)
        {
            case Alias::MaterialComponent1:
                m_customs[0] = value ;
                break ;
                
            case Alias::MaterialComponent2:
                m_customs[1] = value ;
                break ;
                
            case Alias::MaterialComponent3:
                m_customs[2] = value ;
                break ;
                
            case Alias::MaterialComponent4:
                m_customs[3] = value ;
                break ;
                
            case Alias::MaterialComponent5:
                m_customs[4] = value ;
                break ;
                
            default:
                break ;
        }
    }
    
    ////////////////////////////////////////////////////////////
    const String Material::GetName() const
    {
        MutexLocker lck( m_mutex );
        return m_name ;
    }
    
    ////////////////////////////////////////////////////////////
    void Material::SetName( const String& name )
    {
        MutexLocker lck( m_mutex );
        m_name = name ;
    }
    
    ////////////////////////////////////////////////////////////
    void Material::SetTextures( const WeakVector < Texture >& textures )
    {
        MutexLocker lck( m_mutex );
        m_textures = textures ;
    }
    
    ////////////////////////////////////////////////////////////
    WeakVector < Texture > Material::GetTextures() const
    {
        MutexLocker lck( m_mutex );
        return m_textures ;
    }
}
