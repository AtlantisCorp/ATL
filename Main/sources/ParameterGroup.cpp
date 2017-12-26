//  ========================================================================  //
//
//  File    : ATL/ParameterGroup.cpp
//  Project : atlresource
//  Author  : Luk2010
//  Date    : 28/10/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#include <ATL/ParameterGroup.hpp>

namespace atl
{
    ////////////////////////////////////////////////////////////
    ParameterGroup::ParameterGroup()
    {
        
    }
    
    ////////////////////////////////////////////////////////////
    ParameterGroup::~ParameterGroup()
    {
        
    }
    
    ////////////////////////////////////////////////////////////
    void ParameterGroup::AddConstParameter( const ConstantParameter& param )
    {
        MutexLocker lck( m_mutex );
        m_constparams.push_back( param );
    }
    
    ////////////////////////////////////////////////////////////
    void ParameterGroup::AddConstParameters( const Vector < ConstantParameter >& params )
    {
        MutexLocker lck( m_mutex );
        m_constparams.insert( m_constparams.end() , params.begin() , params.end() );
    }
    
    ////////////////////////////////////////////////////////////
    void ParameterGroup::ResetConstParameters()
    {
        MutexLocker lck( m_mutex );
        m_constparams.clear();
    }
    
    ////////////////////////////////////////////////////////////
    void ParameterGroup::AddVarParameter( const Shared < VaryingParameter >& param )
    {
        MutexLocker lck( m_mutex );
        m_varparams.push_back( param );
    }
    
    ////////////////////////////////////////////////////////////
    void ParameterGroup::AddVarParameters( const SharedVector < VaryingParameter >& params )
    {
        MutexLocker lck( m_mutex );
        m_varparams.insert( m_varparams.end() , params.begin() , params.end() );
    }
    
    ////////////////////////////////////////////////////////////
    void ParameterGroup::ResetVarParameters()
    {
        MutexLocker lck( m_mutex );
        m_varparams.clear();
    }
    
    ////////////////////////////////////////////////////////////
    Vector < ConstantParameter > ParameterGroup::GetConstParameters() const
    {
        MutexLocker lck( m_mutex );
        return m_constparams ;
    }
    
    ////////////////////////////////////////////////////////////
    SharedVector < VaryingParameter > ParameterGroup::GetVarParameters() const
    {
        MutexLocker lck( m_mutex );
        return m_varparams ;
    }
}
