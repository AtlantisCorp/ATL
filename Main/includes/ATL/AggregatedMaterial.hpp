//  ========================================================================  //
//
//  File    : ATL/AggregatedMaterial.hpp
//  Project : atlresource
//  Author  : Luk2010
//  Date    : 06/12/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#ifndef AggregatedMaterial_hpp
#define AggregatedMaterial_hpp

#include <ATL/Material.hpp>

namespace atl
{
    ////////////////////////////////////////////////////////////
    /// \brief Defines a Material that keeps track of what has been
    /// set and what needs to be set.
    ///
    /// An AggregatedMaterial is locked at the beginning of the Aggregation
    /// phase. During this phase, the AggregatedMaterial reset every states
    /// and materials can overwrites only states that are not set already.
    /// At the end of aggregation phase, AggregatedMaterial is unlocked and
    /// no writing is possible.
    ///
    ////////////////////////////////////////////////////////////
    class AggregatedMaterial : public Material
    {
        ////////////////////////////////////////////////////////////
        mutable Map < Alias , bool > m_states ;
        mutable Mutex                m_mutex ;
        
    public:
        
        ////////////////////////////////////////////////////////////
        AggregatedMaterial();
        
        ////////////////////////////////////////////////////////////
        virtual ~AggregatedMaterial();
        
        ////////////////////////////////////////////////////////////
        virtual void SetAmbient( const glm::vec4& ambient );
        
        ////////////////////////////////////////////////////////////
        virtual void SetDiffuse( const glm::vec4& diffuse );
        
        ////////////////////////////////////////////////////////////
        virtual void SetSpecular( const glm::vec4& specular );
        
        ////////////////////////////////////////////////////////////
        virtual void SetShininess( float shininess );
        
        ////////////////////////////////////////////////////////////
        virtual void SetTextureAmbient( const Weak < Texture >& texture );
        
        ////////////////////////////////////////////////////////////
        virtual void SetTextureDiffuse( const Weak < Texture >& texture );
        
        ////////////////////////////////////////////////////////////
        virtual void SetTextureSpecular( const Weak < Texture >& texture );
        
        ////////////////////////////////////////////////////////////
        virtual void SetTexture( Alias alias , const Weak < Texture >& texture );
        
        ////////////////////////////////////////////////////////////
        virtual void SetCustom( Alias alias , const ParameterValue& value );
        
        ////////////////////////////////////////////////////////////
        virtual void SetTextures( const WeakVector < Texture >& textures );
        
        ////////////////////////////////////////////////////////////
        /// \brief Reset all states.
        ///
        /// \note It must be called *before* beginning of an AGGREGATION
        /// phase. Generally it is done by AggregatedNode before initiating
        /// a new AGGREGATION phase.
        ///
        ////////////////////////////////////////////////////////////
        virtual void ResetAllStates() const ;
    };
}

#endif /* AggregatedMaterial_hpp */
