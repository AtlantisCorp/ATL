//  ========================================================================  //
//
//  File    : ATL/VertexComponent.cpp
//  Project : atlresource
//  Author  : Luk2010
//  Date    : 11/11/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#include <ATL/VertexComponent.hpp>
#include <ATL/Buffer.hpp>
#include <ATL/CBuffer.hpp>

namespace atl
{
    ////////////////////////////////////////////////////////////
    size_t VertexComponent::GetElementCountFor( uint32_t type )
    {
        switch( type )
        {
            case R32Float: return 1 ;
            case R32Uint:  return 1 ;
            case R32Sint:  return 1 ;
                
            case R32G32Float: return 2 ;
            case R32G32Uint:  return 2 ;
            case R32G32Sint:  return 2 ;
                
            case R32G32B32Float: return 3 ;
            case R32G32B32Uint:  return 3 ;
            case R32G32B32Sint:  return 3 ;
                
            case R32G32B32A32Float: return 4 ;
            case R32G32B32A32Uint:  return 4 ;
            case R32G32B32A32Sint:  return 4 ;
                
            default: return 0 ;
        }
    }
    
    ////////////////////////////////////////////////////////////
    VertexComponent::VertexComponent( Attribute attrib , uint32_t type ,
                                      uintptr_t stride , uintptr_t offset ,
                                      const Shared < Buffer >& buffer )
    : m_attrib( attrib ) , m_type( type )
    , m_elcount( GetElementCountFor(type) ) , m_stride( stride ) , m_offset( offset )
    , m_buffer( buffer )
    {
        
    }
    
    ////////////////////////////////////////////////////////////
    VertexComponent::VertexComponent( Attribute attrib , uint32_t type ,
                                      uintptr_t stride , uintptr_t offset ,
                                      const Weak < CBuffer >& cbuffer )
    : m_attrib( attrib ) , m_type( type )
    , m_elcount( GetElementCountFor(type) ) , m_stride( stride ) , m_offset( offset )
    , m_cbuffer( cbuffer )
    {
        
    }
    
    ////////////////////////////////////////////////////////////
    VertexComponent::VertexComponent( const VertexComponent& rhs )
    : m_attrib( rhs.m_attrib.load() ) , m_type( rhs.m_type.load() )
    , m_elcount( rhs.m_elcount.load() ) , m_stride( rhs.m_stride.load() ) , m_offset( rhs.m_offset.load() )
    , m_buffer( rhs.m_buffer ) , m_cbuffer( rhs.m_cbuffer )
    {
        
    }
    
    ////////////////////////////////////////////////////////////
    VertexComponent& VertexComponent::operator = ( const VertexComponent& rhs )
    {
        m_attrib.store( rhs.GetAttribute() );
        m_type.store( rhs.GetType() );
        m_elcount.store( rhs.GetElementCount() );
        m_stride.store( rhs.GetStride() );
        m_offset.store( rhs.GetOffset() );
        std::atomic_store( &m_buffer , rhs.m_buffer );
        m_cbuffer = rhs.GetCBuffer();
        return *this ;
    }
    
    ////////////////////////////////////////////////////////////
    VertexComponent::~VertexComponent()
    {
        
    }
    
    ////////////////////////////////////////////////////////////
    Attribute VertexComponent::GetAttribute() const
    {
        return m_attrib.load();
    }
    
    ////////////////////////////////////////////////////////////
    uint32_t VertexComponent::GetType() const
    {
        return m_type.load();
    }
    
    ////////////////////////////////////////////////////////////
    size_t VertexComponent::GetElementCount() const
    {
        return m_elcount.load();
    }
    
    ////////////////////////////////////////////////////////////
    uintptr_t VertexComponent::GetStride() const
    {
        return m_stride.load();
    }
    
    ////////////////////////////////////////////////////////////
    uintptr_t VertexComponent::GetOffset() const
    {
        return m_offset.load();
    }
    
    ////////////////////////////////////////////////////////////
    const Weak < Buffer > VertexComponent::GetBuffer() const
    {
        return std::atomic_load( &m_buffer );
    }
    
    ////////////////////////////////////////////////////////////
    void VertexComponent::SetBuffer( const Shared < Buffer >& buffer )
    {
        std::atomic_store( &m_buffer , buffer );
    }
    
    ////////////////////////////////////////////////////////////
    const Weak < CBuffer > VertexComponent::GetCBuffer() const
    {
        return m_cbuffer ;
    }
}
