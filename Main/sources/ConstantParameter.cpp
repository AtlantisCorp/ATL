//  ========================================================================  //
//
//  File    : ATL/ConstantParameter.cpp
//  Project : atlresource
//  Author  : Luk2010
//  Date    : 31/10/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#include <ATL/ConstantParameter.hpp>

namespace atl
{
    ////////////////////////////////////////////////////////////
    ConstantParameter::ConstantParameter() : m_index( -1 ) , m_alias( Alias::Unknown )
    {
        
    }
    
    ////////////////////////////////////////////////////////////
    ConstantParameter::ConstantParameter( const ParameterValue& value , const String& name , int32_t idx )
    : m_value( value ) , m_name( name ) , m_index( idx ) , m_alias( Alias::Unknown )
    {
        
    }
    
    ////////////////////////////////////////////////////////////
    ConstantParameter::ConstantParameter( const ParameterValue& value , Alias alias )
    : m_value( value ) , m_index( -1 ) , m_alias( alias )
    {
        
    }
    
    ////////////////////////////////////////////////////////////
    ConstantParameter::ConstantParameter( const ConstantParameter& parameter )
    : m_value( parameter.m_value ) , m_name( parameter.m_name ) , m_index( parameter.m_index ) , m_alias( parameter.m_alias )
    {
        
    }
    
    ////////////////////////////////////////////////////////////
    ConstantParameter::~ConstantParameter()
    {
        
    }
    
    ////////////////////////////////////////////////////////////
    const ParameterValue& ConstantParameter::GetValue() const
    {
        return m_value ;
    }
    
    ////////////////////////////////////////////////////////////
    const String& ConstantParameter::GetName() const
    {
        return m_name ;
    }
    
    ////////////////////////////////////////////////////////////
    int32_t ConstantParameter::GetIndex() const
    {
        return m_index ;
    }
    
    ////////////////////////////////////////////////////////////
    Alias ConstantParameter::GetAlias() const
    {
        return m_alias ;
    }
    
    ////////////////////////////////////////////////////////////
    Stage ConstantParameter::GetStage() const
    {
        return m_stage ;
    }
    
    ////////////////////////////////////////////////////////////
    void ConstantParameter::SetValue( const ParameterValue& value )
    {
        m_value = value ;
    }
    
    ////////////////////////////////////////////////////////////
    void ConstantParameter::SetName( const String& name )
    {
        m_name = name ;
    }
    
    ////////////////////////////////////////////////////////////
    void ConstantParameter::SetIndex( int32_t index )
    {
        m_index = index ;
    }
    
    ////////////////////////////////////////////////////////////
    void ConstantParameter::SetAlias( Alias alias )
    {
        m_alias = alias ;
    }
    
    ////////////////////////////////////////////////////////////
    void ConstantParameter::SetStage( Stage stage )
    {
        m_stage = stage ;
    }
}
