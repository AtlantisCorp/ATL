//  ========================================================================  //
//
//  File    : ATL/ParameterValue.cpp
//  Project : atlresource
//  Author  : Luk2010
//  Date    : 30/10/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#include <ATL/ParameterValue.hpp>

namespace atl
{
    ////////////////////////////////////////////////////////////
    ParameterValue::ParameterValue()
    {
        
    }
    
    ////////////////////////////////////////////////////////////
    ParameterValue::ParameterValue( const ParameterValue& value ) : m_data() , m_type( value.m_type )
    {
        memcpy( &m_data , &value.m_data , sizeof( m_data ) );
    }
    
    ////////////////////////////////////////////////////////////
    ParameterValue::ParameterValue( float float1 ) : m_data() , m_type( ParameterType::Float1 )
    {
        m_data.float1 = float1 ;
    }
    
    ////////////////////////////////////////////////////////////
    ParameterValue::ParameterValue( const glm::vec2& float2 ) : m_data() , m_type( ParameterType::Float2 )
    {
        m_data.float2 = float2 ;
    }
    
    ////////////////////////////////////////////////////////////
    ParameterValue::ParameterValue( const glm::vec3& float3 ) : m_data() , m_type( ParameterType::Float3 )
    {
        m_data.float3 = float3 ;
    }
    
    ////////////////////////////////////////////////////////////
    ParameterValue::ParameterValue( const glm::vec4& float4 ) : m_data() , m_type( ParameterType::Float4 )
    {
        m_data.float4 = float4 ;
    }
    
    ////////////////////////////////////////////////////////////
    ParameterValue::ParameterValue( int int1 ) : m_data() , m_type( ParameterType::Int1 )
    {
        m_data.int1 = int1 ;
    }
    
    ////////////////////////////////////////////////////////////
    ParameterValue::ParameterValue( const glm::ivec2& int2 ) : m_data() , m_type( ParameterType::Int2 )
    {
        m_data.int2 = int2 ;
    }
    
    ////////////////////////////////////////////////////////////
    ParameterValue::ParameterValue( const glm::ivec3& int3 ) : m_data() , m_type( ParameterType::Int3 )
    {
        m_data.int3 = int3 ;
    }
    
    ////////////////////////////////////////////////////////////
    ParameterValue::ParameterValue( const glm::ivec4& int4 ) : m_data() , m_type( ParameterType::Int4 )
    {
        m_data.int4 = int4 ;
    }
    
    ////////////////////////////////////////////////////////////
    ParameterValue::ParameterValue( unsigned int uint1 ) : m_data() , m_type( ParameterType::Uint1 )
    {
        m_data.uint1 = uint1 ;
    }
    
    ////////////////////////////////////////////////////////////
    ParameterValue::ParameterValue( const glm::uvec2& uint2 ) : m_data() , m_type( ParameterType::Uint2 )
    {
        m_data.uint2 = uint2 ;
    }
    
    ////////////////////////////////////////////////////////////
    ParameterValue::ParameterValue( const glm::uvec3& uint3 ) : m_data() , m_type( ParameterType::Uint3 )
    {
        m_data.uint3 = uint3 ;
    }
    
    ////////////////////////////////////////////////////////////
    ParameterValue::ParameterValue( const glm::uvec4& uint4 ) : m_data() , m_type( ParameterType::Uint4 )
    {
        m_data.uint4 = uint4 ;
    }
    
    ////////////////////////////////////////////////////////////
    ParameterValue::ParameterValue( bool bool1 ) : m_data() , m_type( ParameterType::Bool1 )
    {
        m_data.bool1 = bool1 ;
    }
    
    ////////////////////////////////////////////////////////////
    ParameterValue::ParameterValue( const glm::bvec2& bool2 ) : m_data() , m_type( ParameterType::Bool2 )
    {
        m_data.bool2 = bool2 ;
    }
    
    ////////////////////////////////////////////////////////////
    ParameterValue::ParameterValue( const glm::bvec3& bool3 ) : m_data() , m_type( ParameterType::Bool3 )
    {
        m_data.bool3 = bool3 ;
    }
    
    ////////////////////////////////////////////////////////////
    ParameterValue::ParameterValue( const glm::bvec4& bool4 ) : m_data() , m_type( ParameterType::Bool4 )
    {
        m_data.bool4 = bool4 ;
    }
    
    ////////////////////////////////////////////////////////////
    ParameterValue::ParameterValue( const glm::mat2& mat2 ) : m_data() , m_type( ParameterType::Mat2 )
    {
        m_data.mat2 = mat2 ;
    }
    
    ////////////////////////////////////////////////////////////
    ParameterValue::ParameterValue( const glm::mat3& mat3 ) : m_data() , m_type( ParameterType::Mat3 )
    {
        m_data.mat3 = mat3 ;
    }
    
    ////////////////////////////////////////////////////////////
    ParameterValue::ParameterValue( const glm::mat4& mat4 ) : m_data() , m_type( ParameterType::Mat4 )
    {
        m_data.mat4 = mat4 ;
    }
    
    ////////////////////////////////////////////////////////////
    ParameterValue::ParameterValue( const Weak < Texture >& texture ) : m_data() , m_type( ParameterType::Texture )
    {
        m_data.tex = texture ;
    }
    
    ////////////////////////////////////////////////////////////
    ParameterValue::~ParameterValue()
    {
        
    }
    
    ////////////////////////////////////////////////////////////
    ParameterValue& ParameterValue::operator = ( const ParameterValue& rhs )
    {
        Spinlocker lck( m_spinlock );
        memcpy( &m_data , &rhs.m_data , sizeof( m_data ) );
        m_type = rhs.m_type ;
        return *this ;
    }
    
    ////////////////////////////////////////////////////////////
    ParameterType ParameterValue::GetType() const
    {
        Spinlocker lck( m_spinlock );
        return m_type ;
    }
    
    ////////////////////////////////////////////////////////////
    float ParameterValue::GetFloat1() const
    {
        Spinlocker lck( m_spinlock );
        return m_data.float1 ;
    }
    
    ////////////////////////////////////////////////////////////
    glm::vec2 ParameterValue::GetFloat2() const
    {
        Spinlocker lck( m_spinlock );
        return m_data.float2 ;
    }
    
    ////////////////////////////////////////////////////////////
    glm::vec3 ParameterValue::GetFloat3() const
    {
        Spinlocker lck( m_spinlock );
        return m_data.float3 ;
    }
    
    ////////////////////////////////////////////////////////////
    glm::vec4 ParameterValue::GetFloat4() const
    {
        Spinlocker lck( m_spinlock );
        return m_data.float4 ;
    }
    
    ////////////////////////////////////////////////////////////
    int ParameterValue::GetInt1() const
    {
        Spinlocker lck( m_spinlock );
        return m_data.int1 ;
    }
    
    ////////////////////////////////////////////////////////////
    glm::ivec2 ParameterValue::GetInt2() const
    {
        Spinlocker lck( m_spinlock );
        return m_data.int2 ;
    }
    
    ////////////////////////////////////////////////////////////
    glm::ivec3 ParameterValue::GetInt3() const
    {
        Spinlocker lck( m_spinlock );
        return m_data.int3 ;
    }
    
    ////////////////////////////////////////////////////////////
    glm::ivec4 ParameterValue::GetInt4() const
    {
        Spinlocker lck( m_spinlock );
        return m_data.int4 ;
    }
    
    ////////////////////////////////////////////////////////////
    unsigned int ParameterValue::GetUint1() const
    {
        Spinlocker lck( m_spinlock );
        return m_data.uint1 ;
    }
    
    ////////////////////////////////////////////////////////////
    glm::uvec2 ParameterValue::GetUint2() const
    {
        Spinlocker lck( m_spinlock );
        return m_data.uint2 ;
    }
    
    ////////////////////////////////////////////////////////////
    glm::uvec3 ParameterValue::GetUint3() const
    {
        Spinlocker lck( m_spinlock );
        return m_data.uint3 ;
    }
    
    ////////////////////////////////////////////////////////////
    glm::uvec4 ParameterValue::GetUint4() const
    {
        Spinlocker lck( m_spinlock );
        return m_data.uint4 ;
    }
    
    ////////////////////////////////////////////////////////////
    bool ParameterValue::GetBool1() const
    {
        Spinlocker lck( m_spinlock );
        return m_data.bool1 ;
    }
    
    ////////////////////////////////////////////////////////////
    glm::bvec2 ParameterValue::GetBool2() const
    {
        Spinlocker lck( m_spinlock );
        return m_data.bool2 ;
    }
    
    ////////////////////////////////////////////////////////////
    glm::bvec3 ParameterValue::GetBool3() const
    {
        Spinlocker lck( m_spinlock );
        return m_data.bool3 ;
    }
    
    ////////////////////////////////////////////////////////////
    glm::bvec4 ParameterValue::GetBool4() const
    {
        Spinlocker lck( m_spinlock );
        return m_data.bool4 ;
    }
    
    ////////////////////////////////////////////////////////////
    glm::mat2 ParameterValue::GetMat2() const
    {
        Spinlocker lck( m_spinlock );
        return m_data.mat2 ;
    }
    
    ////////////////////////////////////////////////////////////
    glm::mat3 ParameterValue::GetMat3() const
    {
        Spinlocker lck( m_spinlock );
        return m_data.mat3 ;
    }
    
    ////////////////////////////////////////////////////////////
    glm::mat4 ParameterValue::GetMat4() const
    {
        Spinlocker lck( m_spinlock );
        return m_data.mat4 ;
    }
    
    ////////////////////////////////////////////////////////////
    Weak < Texture > ParameterValue::GetTexture() const
    {
        Spinlocker lck( m_spinlock );
        return m_data.tex ;
    }
}
