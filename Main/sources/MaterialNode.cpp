//  ========================================================================  //
//
//  File    : ATL/MaterialNode.cpp
//  Project : atlresource
//  Author  : Luk2010
//  Date    : 30/11/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#include <ATL/MaterialNode.hpp>
#include <ATL/AggregatedMaterial.hpp>

namespace atl
{
    ////////////////////////////////////////////////////////////
    MaterialNode::MaterialNode( const Weak < atl::Material >& material )
    : DerivedNode < MaterialNode >( Node::Subtype::Material ) , m_material( material )
    {
        
    }
    
    ////////////////////////////////////////////////////////////
    MaterialNode::~MaterialNode()
    {
        
    }
    
    ////////////////////////////////////////////////////////////
    void MaterialNode::SetMaterial( const Weak < atl::Material >& material )
    {
        m_material = material ;
    }
    
    ////////////////////////////////////////////////////////////
    Weak < Material > MaterialNode::GetMaterial() const
    {
        return m_material ;
    }
    
    ////////////////////////////////////////////////////////////
    void MaterialNode::Aggregate( AggregatedMaterial& material , RenderCommand& command ) const
    {
        auto thismat = m_material.lock();
        
        material.SetAmbient( thismat->GetAmbient() );
        material.SetDiffuse( thismat->GetDiffuse() );
        material.SetSpecular( thismat->GetSpecular() );
        material.SetShininess( thismat->GetShininess() );
        material.SetTextureAmbient( thismat->GetTextureAmbient() );
        material.SetTextureDiffuse( thismat->GetTextureDiffuse() );
        material.SetTextureSpecular( thismat->GetTextureSpecular() );
        material.SetTextures( thismat->GetTextures() );
        
        DerivedNode < MaterialNode >::Aggregate( material , command );
    }
}
