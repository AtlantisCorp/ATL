//  ========================================================================  //
//
//  File    : ATL/VaryingParameter.cpp
//  Project : atlresource
//  Author  : Luk2010
//  Date    : 28/10/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#include <ATL/VaryingParameter.hpp>

namespace atl
{
    ////////////////////////////////////////////////////////////
    VaryingParameter::VaryingParameter() : m_alias( Alias::Unknown ) , m_index( -1 )
    {
        
    }
    
    ////////////////////////////////////////////////////////////
    VaryingParameter::VaryingParameter( const ParameterValue& value , const String& name , int32_t index )
    : m_alias( Alias::Unknown ) , m_name( name ) , m_index( index ) , m_value( value )
    {
        
    }
    
    ////////////////////////////////////////////////////////////
    VaryingParameter::VaryingParameter( const ParameterValue& value , Alias alias )
    : m_alias( alias ) , m_index( -1 ) , m_value( value )
    {
        
    }
    
    ////////////////////////////////////////////////////////////
    VaryingParameter::~VaryingParameter()
    {
        
    }
    
    ////////////////////////////////////////////////////////////
    ParameterValue VaryingParameter::GetValue() const
    {
        Spinlocker lck( m_spinlock );
        return m_value ;
    }
    
    ////////////////////////////////////////////////////////////
    String VaryingParameter::GetName() const
    {
        Spinlocker lck( m_spinlock );
        return m_name ;
    }
    
    ////////////////////////////////////////////////////////////
    int32_t VaryingParameter::GetIndex() const
    {
        return m_index.load();
    }
    
    ////////////////////////////////////////////////////////////
    Alias VaryingParameter::GetAlias() const
    {
        return m_alias.load();
    }
    
    ////////////////////////////////////////////////////////////
    void VaryingParameter::SetValue( const ParameterValue& value )
    {
        Spinlocker lck( m_spinlock );
        m_value = value ;
    }
    
    ////////////////////////////////////////////////////////////
    void VaryingParameter::SetName( const String& name )
    {
        Spinlocker lck( m_spinlock );
        m_name = name ;
    }
    
    ////////////////////////////////////////////////////////////
    void VaryingParameter::SetIndex( int32_t index )
    {
        m_index.store( index );
    }
    
    ////////////////////////////////////////////////////////////
    void VaryingParameter::SetAlias( Alias alias )
    {
        m_alias.store( alias );
    }
}
