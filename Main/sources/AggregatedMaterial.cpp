//  ========================================================================  //
//
//  File    : ATL/AggregatedMaterial.cpp
//  Project : atlresource
//  Author  : Luk2010
//  Date    : 06/12/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#include <ATL/AggregatedMaterial.hpp>

namespace atl
{
    ////////////////////////////////////////////////////////////
    AggregatedMaterial::AggregatedMaterial()
    {
        
    }
    
    ////////////////////////////////////////////////////////////
    AggregatedMaterial::~AggregatedMaterial()
    {
        
    }
    
    ////////////////////////////////////////////////////////////
    void AggregatedMaterial::SetAmbient( const glm::vec4& ambient )
    {
        MutexLocker lck( m_mutex );
        auto state = m_states.find( Alias::MaterialAmbient );
        
        if ( state == m_states.end() || !(state->second) )
        {
            Material::SetAmbient( ambient );
            m_states[ Alias::MaterialAmbient ] = true ;
        }
    }
    
    ////////////////////////////////////////////////////////////
    void AggregatedMaterial::SetDiffuse( const glm::vec4& diffuse )
    {
        MutexLocker lck( m_mutex );
        auto state = m_states.find( Alias::MaterialDiffuse );
        
        if ( state == m_states.end() || !(state->second) )
        {
            Material::SetDiffuse( diffuse );
            m_states[ Alias::MaterialDiffuse ] = true ;
        }
    }
    
    ////////////////////////////////////////////////////////////
    void AggregatedMaterial::SetSpecular( const glm::vec4& specular )
    {
        MutexLocker lck( m_mutex );
        auto state = m_states.find( Alias::MaterialSpecular );
        
        if ( state == m_states.end() || !(state->second) )
        {
            Material::SetSpecular( specular );
            m_states[ Alias::MaterialSpecular ] = true ;
        }
    }
    
    ////////////////////////////////////////////////////////////
    void AggregatedMaterial::SetShininess( float shininess )
    {
        MutexLocker lck( m_mutex );
        auto state = m_states.find( Alias::MaterialShininess );
        
        if ( state == m_states.end() || !(state->second) )
        {
            Material::SetShininess( shininess );
            m_states[ Alias::MaterialShininess ] = true ;
        }
    }
    
    ////////////////////////////////////////////////////////////
    void AggregatedMaterial::SetTextureAmbient( const Weak < Texture >& ambient )
    {
        MutexLocker lck( m_mutex );
        auto state = m_states.find( Alias::MaterialTextureAmbient );
        
        if ( state == m_states.end() || !(state->second) )
        {
            Material::SetTextureAmbient( ambient );
            m_states[ Alias::MaterialTextureAmbient ] = true ;
        }
    }
    
    ////////////////////////////////////////////////////////////
    void AggregatedMaterial::SetTextureDiffuse( const Weak < Texture >& diffuse )
    {
        MutexLocker lck( m_mutex );
        auto state = m_states.find( Alias::MaterialTextureDiffuse );
        
        if ( state == m_states.end() || !(state->second) )
        {
            Material::SetTextureDiffuse( diffuse );
            m_states[ Alias::MaterialTextureDiffuse ] = true ;
        }
    }
    
    ////////////////////////////////////////////////////////////
    void AggregatedMaterial::SetTextureSpecular( const Weak < Texture >& specular )
    {
        MutexLocker lck( m_mutex );
        auto state = m_states.find( Alias::MaterialTextureSpecular );
        
        if ( state == m_states.end() || !(state->second) )
        {
            Material::SetTextureSpecular( specular );
            m_states[ Alias::MaterialTextureSpecular ] = true ;
        }
    }
    
    ////////////////////////////////////////////////////////////
    void AggregatedMaterial::SetTexture( Alias alias , const Weak < Texture >& texture )
    {
        MutexLocker lck( m_mutex );
        auto state = m_states.find( alias );
        
        if ( state == m_states.end() || !(state->second) )
        {
            Material::SetTexture( alias , texture );
            m_states[ alias ] = true ;
        }
    }
    
    ////////////////////////////////////////////////////////////
    void AggregatedMaterial::SetCustom( Alias alias , const ParameterValue& texture )
    {
        MutexLocker lck( m_mutex );
        auto state = m_states.find( alias );
        
        if ( state == m_states.end() || !(state->second) )
        {
            Material::SetCustom( alias , texture );
            m_states[ alias ] = true ;
        }
    }
    
    ////////////////////////////////////////////////////////////
    void AggregatedMaterial::SetTextures( const WeakVector < Texture >& textures )
    {
        for ( unsigned int i = 0 ; i < textures.size() ; ++i )
        {
            switch( i )
            {
                case 0:
                    SetTexture( Alias::MaterialTexture1 , textures[i] );
                    break ;
                    
                case 1:
                    SetTexture( Alias::MaterialTexture2 , textures[i] );
                    break ;
                    
                case 2:
                    SetTexture( Alias::MaterialTexture3 , textures[i] );
                    break ;
                    
                case 3:
                    SetTexture( Alias::MaterialTexture4 , textures[i] );
                    break ;
                    
                default:
                    break ;
            }
        }
    }
    
    ////////////////////////////////////////////////////////////
    void AggregatedMaterial::ResetAllStates() const
    {
        MutexLocker lck( m_mutex );
        
        // To prevent reinstanciation of states nodes, we do not clear the
        // state map but only set flags to 'false'. This way map does not reallocate
        // everytime we reset it.
        
        for ( auto& it : m_states )
        it.second = false ;
    }
}
