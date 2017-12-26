//  ========================================================================  //
//
//  File    : ATL/ConstantParameter.hpp
//  Project : atlresource
//  Author  : Luk2010
//  Date    : 28/10/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#ifndef ConstantParameter_hpp
#define ConstantParameter_hpp

#include <ATL/StdIncludes.hpp>
#include <ATL/ParameterValue.hpp>
#include <ATL/Alias.hpp>
#include <ATL/Stage.hpp>

namespace atl
{
    ////////////////////////////////////////////////////////////
    /// \brief A Constant parameter.
    ///
    /// This policy for a parameter means the parameter is stored
    /// by value, and no locking is done to access its data.
    ///
    ////////////////////////////////////////////////////////////
    class ConstantParameter
    {
        ////////////////////////////////////////////////////////////
        ParameterValue m_value ; ///< Value for this parameter. May hold nothing if this parameter
                                 ///  is used by the program class to store informations about the parameter.
        String         m_name ;  ///< Actual name of the parameter, may be empty.
        int32_t        m_index ; ///< Actual index of the parameter, may be -1 on invalid.
        Alias          m_alias ; ///< Actual alias for this parameter. When it is a user parameter, it is used
                                 ///  to find what is the current parameter in the program. When in a program, this
                                 ///  alias is always Alias::Unknown.
        Stage          m_stage ; ///< Stage designated for this parameter. Notes that this field is information/optional
                                 ///  for OpenGL drivers but needed for DirectX drivers as management of constant buffers
                                 ///  are per-vertex-stage on D3D. Default value is 'Stage::Vertex'.
        
    public:
        
        ////////////////////////////////////////////////////////////
        ConstantParameter();
        
        ////////////////////////////////////////////////////////////
        ConstantParameter( const ParameterValue& value , const String& name , int32_t index = -1 );
        
        ////////////////////////////////////////////////////////////
        ConstantParameter( const ParameterValue& value , Alias alias );
        
        ////////////////////////////////////////////////////////////
        ConstantParameter( const ConstantParameter& parameter );
        
        ////////////////////////////////////////////////////////////
        ~ConstantParameter();
        
        ////////////////////////////////////////////////////////////
        const ParameterValue& GetValue() const ;
        
        ////////////////////////////////////////////////////////////
        const String& GetName() const ;
        
        ////////////////////////////////////////////////////////////
        int32_t GetIndex() const ;
        
        ////////////////////////////////////////////////////////////
        Alias GetAlias() const ;
        
        ////////////////////////////////////////////////////////////
        Stage GetStage() const ;
        
        ////////////////////////////////////////////////////////////
        void SetValue( const ParameterValue& value );
        
        ////////////////////////////////////////////////////////////
        void SetName( const String& name );
        
        ////////////////////////////////////////////////////////////
        void SetIndex( int32_t index );
        
        ////////////////////////////////////////////////////////////
        void SetAlias( Alias alias );
        
        ////////////////////////////////////////////////////////////
        void SetStage( Stage stage );
    };
}

#endif /* ConstantParameter_hpp */
