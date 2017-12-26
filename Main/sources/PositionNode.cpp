//  ========================================================================  //
//
//  File    : ATL/PositionNode.cpp
//  Project : atlresource
//  Author  : Luk2010
//  Date    : 29/11/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#include <ATL/PositionNode.hpp>
#include <ATL/Material.hpp>
#include <ATL/AggregatedMaterial.hpp>

namespace atl
{
    ////////////////////////////////////////////////////////////
    PositionNode::PositionNode( const glm::vec3& position )
    : DerivedNode < PositionNode >( Node::Subtype::Position ) , m_position( position )
    {
        
    }
    
    ////////////////////////////////////////////////////////////
    PositionNode::~PositionNode()
    {
        
    }
    
    ////////////////////////////////////////////////////////////
    glm::vec3 PositionNode::GetPosition() const
    {
        Spinlocker lck( m_spinlock );
        return m_position ;
    }
    
    ////////////////////////////////////////////////////////////
    void PositionNode::SetPosition( const glm::vec3& position )
    {
        Spinlocker lck( m_spinlock );
        m_position = position ;
    }
    
    ////////////////////////////////////////////////////////////
    void PositionNode::Aggregate( AggregatedMaterial& material , RenderCommand& command ) const
    {
        glm::mat4 model  = material.GetCustom( Alias::MatrixModel ).GetMat4();
        glm::mat3 model3 = material.GetCustom( Alias::Matrix3Model ).GetMat3();
        glm::mat4 mvp    = material.GetCustom( Alias::MatrixMVP ).GetMat4();
        glm::mat3 mvp3   = material.GetCustom( Alias::Matrix3MVP ).GetMat3();
        
        m_spinlock.lock();
        
        glm::mat4 tmp  = m_modelmat ;
        glm::mat3 tmp3 = glm::mat3( m_modelmat );
        
        m_spinlock.unlock();
        
        model  *= tmp ;
        mvp    *= tmp ;
        model3 *= tmp3 ;
        mvp3   *= tmp3 ;
        
        material.SetCustom( Alias::MatrixModel , ParameterValue( model ) );
        material.SetCustom( Alias::Matrix3Model , ParameterValue( model3 ) );
        material.SetCustom( Alias::MatrixMVP , ParameterValue( mvp ) );
        material.SetCustom( Alias::Matrix3MVP , ParameterValue( mvp3 ) );
        
        DerivedNode < PositionNode >::Aggregate( material , command );
    }
}
