//  ========================================================================  //
//
//  File    : ATL/Program.cpp
//  Project : atlresource
//  Author  : Luk2010
//  Date    : 18/10/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#include <ATL/Program.hpp>
#include <ATL/ParameterValue.hpp>
#include <ATL/VaryingParameter.hpp>

namespace atl
{
    ////////////////////////////////////////////////////////////
    IDGenerator < ProgramId > Program::s_generator ;
    
    ////////////////////////////////////////////////////////////
    Program::Program() : m_id( s_generator.New() )
    {
        
    }
    
    ////////////////////////////////////////////////////////////
    Program::Program( const SharedVector < Shader >& shaders ) : m_id( s_generator.New() )
    {
        
    }
    
    ////////////////////////////////////////////////////////////
    Program::~Program()
    {
        
    }
    
    ////////////////////////////////////////////////////////////
    ProgramId Program::GetId() const
    {
        return m_id.load();
    }
    
    ////////////////////////////////////////////////////////////
    bool Program::AddAlias( Alias alias , const String& name )
    {
        if ( alias == Alias::Unknown )
            return false ;
        
        const ConstantParameter* parameter = GetParameterByName( name );
        if ( !parameter )
            return false ;
        
        MutexLocker lck( m_mutex );
        m_aliases[alias] = const_cast < ConstantParameter* >( parameter );
        return true ;
    }
    
    ////////////////////////////////////////////////////////////
    bool Program::AddAlias( Alias alias , int32_t index )
    {
        if ( alias == Alias::Unknown )
            return false ;
        
        const ConstantParameter* parameter = GetParameterByIndex( index );
        if ( !parameter )
            return false ;
        
        MutexLocker lck( m_mutex );
        m_aliases[alias] = const_cast < ConstantParameter* >( parameter );
        return true ;
    }
    
    ////////////////////////////////////////////////////////////
    void Program::RemoveAlias( Alias alias )
    {
        MutexLocker lck( m_mutex );
        auto it = m_aliases.find( alias );
        it != m_aliases.end() ? m_aliases.erase( it ) : it ;
    }
    
    ////////////////////////////////////////////////////////////
    String Program::GetAliasName( Alias alias ) const
    {
        MutexLocker lck( m_mutex );
        auto it = m_aliases.find( alias );
        
        if ( it != m_aliases.end() )
        {
            if ( it->second )
            {
                return it->second->GetName();
            }
        }
        
        return String();
    }
    
    ////////////////////////////////////////////////////////////
    int32_t Program::GetAliasIndex( Alias alias ) const
    {
        MutexLocker lck( m_mutex );
        auto it = m_aliases.find( alias );
        
        if ( it != m_aliases.end() )
        {
            if ( it->second )
            {
                return it->second->GetIndex();
            }
        }
        
        return -1 ;
    }
    
    ////////////////////////////////////////////////////////////
    void Program::ResetAliases()
    {
        MutexLocker lck( m_mutex );
        m_aliases.clear();
    }
    
    ////////////////////////////////////////////////////////////
    void Program::BindConstantParameter( const ConstantParameter& parameter ) const
    {
        const ConstantParameter* inparam = GetParameterByAlias( parameter.GetAlias() );
        
        if ( !inparam )
            inparam = GetParameterByName( parameter.GetName() );
        if ( !inparam )
            inparam = GetParameterByIndex( parameter.GetIndex() );
        
        if ( !inparam )
            return ;
        
        MutexLocker lck( m_mutex );
        BindParameter( inparam , parameter.GetValue() );
    }
    
    ////////////////////////////////////////////////////////////
    void Program::BindVaryingParameter( const Shared < VaryingParameter >& parameter ) const
    {
        if ( !parameter )
            return ;
        
        const ConstantParameter* inparam = GetParameterByAlias( parameter->GetAlias() );
        
        if ( !inparam )
            inparam = GetParameterByName( parameter->GetName() );
        if ( !inparam )
            inparam = GetParameterByIndex( parameter->GetIndex() );
        
        if ( !inparam )
            return ;
        
        MutexLocker lck( m_mutex );
        BindParameter( inparam , parameter->GetValue() );
    }
    
    ////////////////////////////////////////////////////////////
    void Program::BindName( const String& name , const ParameterValue& value ) const
    {
        const ConstantParameter* inparam = GetParameterByName( name );
        if ( !inparam )
            return ;
        
        MutexLocker lck( m_mutex );
        BindParameter( inparam , value );
    }
    
    ////////////////////////////////////////////////////////////
    void Program::BindIndex( int32_t index , const ParameterValue& value ) const
    {
        const ConstantParameter* inparam = GetParameterByIndex( index );
        if ( !inparam )
            return ;
        
        MutexLocker lck( m_mutex );
        BindParameter( inparam , value );
    }
    
    ////////////////////////////////////////////////////////////
    void Program::BindAlias( Alias alias , const ParameterValue& value ) const
    {
        const ConstantParameter* inparam = GetParameterByAlias( alias );
        if ( !inparam )
            return ;
        
        MutexLocker lck( m_mutex );
        BindParameter( inparam , value );
    }
    
    ////////////////////////////////////////////////////////////
    ConstantParameter* Program::GetParameterByName( const String& name )
    {
        MutexLocker lck( m_mutex );
        
        for ( auto it = m_parameters.begin() ; it != m_parameters.end() ; it++ )
        {
            if ( (*it).GetName() == name )
            {
                return &(*it);
            }
        }
        
        return nullptr ;
    }
    
    ////////////////////////////////////////////////////////////
    ConstantParameter* Program::GetParameterByIndex( int32_t index )
    {
        MutexLocker lck( m_mutex );
        
        for ( auto it = m_parameters.begin() ; it != m_parameters.end() ; it++ )
        {
            if ( (*it).GetIndex() == index )
            {
                return &(*it);
            }
        }
        
        return nullptr ;
    }
    
    ////////////////////////////////////////////////////////////
    ConstantParameter* Program::GetParameterByAlias( Alias alias )
    {
        MutexLocker lck( m_mutex );
        auto it = m_aliases.find( alias );
        
        if ( it != m_aliases.end() && it->second )
        {
            return it->second ;
        }
        
        return nullptr ;
    }
    
    ////////////////////////////////////////////////////////////
    const ConstantParameter* Program::GetParameterByName( const String& name ) const
    {
        MutexLocker lck( m_mutex );
        
        for ( auto it = m_parameters.begin() ; it != m_parameters.end() ; it++ )
        {
            if ( (*it).GetName() == name )
            {
                return &(*it);
            }
        }
        
        return nullptr ;
    }
    
    ////////////////////////////////////////////////////////////
    const ConstantParameter* Program::GetParameterByIndex( int32_t index ) const
    {
        MutexLocker lck( m_mutex );
        
        for ( auto it = m_parameters.begin() ; it != m_parameters.end() ; it++ )
        {
            if ( (*it).GetIndex() == index )
            {
                return &(*it);
            }
        }
        
        return nullptr ;
    }
    
    ////////////////////////////////////////////////////////////
    const ConstantParameter* Program::GetParameterByAlias( Alias alias ) const
    {
        MutexLocker lck( m_mutex );
        auto it = m_aliases.find( alias );
        
        if ( it != m_aliases.end() && it->second )
        {
            return it->second ;
        }
        
        return nullptr ;
    }
    
    ////////////////////////////////////////////////////////////
    void Program::BindConstantParameters( const Vector < ConstantParameter >& params ) const
    {
        for ( auto const& param : params )
        {
            BindConstantParameter( param );
        }
    }
    
    ////////////////////////////////////////////////////////////
    void Program::BindVaryingParameters( const SharedVector < VaryingParameter >& params ) const
    {
        for ( auto const& param : params )
        {
            BindVaryingParameter( param );
        }
    }
    
    ////////////////////////////////////////////////////////////
    const ConstantParameter* Program::GetParameterByStage( Stage stage , const String& name ) const
    {
        MutexLocker lck( m_mutex );
        
        for ( auto const& param : m_parameters )
        {
            if ( param.GetStage() == stage &&
                 param.GetName()  == name )
            {
                return &param;
            }
        }
        
        return nullptr ;
    }
    
    ////////////////////////////////////////////////////////////
    const ConstantParameter* Program::GetParameterByStage( Stage stage , int32_t index ) const
    {
        MutexLocker lck( m_mutex );
        
        for ( auto const& param : m_parameters )
        {
            if ( param.GetStage() == stage &&
                 param.GetIndex() == index )
            {
                return &param;
            }
        }
        
        return nullptr ;
    }
    
    ////////////////////////////////////////////////////////////
    Weak < VertexLayout > Program::GetVertexLayout() const
    {
        return m_layout ;
    }
    
    ////////////////////////////////////////////////////////////
    void Program::SetVertexLayout( const Shared < VertexLayout >& layout )
    {
        m_layout = layout ;
    }
    
    ////////////////////////////////////////////////////////////
    void Program::SetParameters( const Vector < ConstantParameter >& params )
    {
        MutexLocker lck( m_mutex );
        m_parameters = params ;
        m_aliases.clear();
    }
}
