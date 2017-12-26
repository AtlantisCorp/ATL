//  ========================================================================  //
//
//  File    : ATL/Mesh.cpp
//  Project : atlresource
//  Author  : Luk2010
//  Date    : 26/10/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#include <ATL/Mesh.hpp>
#include <ATL/RenderWindow.hpp>

namespace atl
{    
    ////////////////////////////////////////////////////////////
    Mesh::Mesh() : m_dirty( false )
    {
        
    }
    
    ////////////////////////////////////////////////////////////
    Mesh::~Mesh()
    {
        
    }
    
    ////////////////////////////////////////////////////////////
    void Mesh::AddVertexCBuffer( const Shared < CBuffer >& buffer , const VertexComponent& component )
    {
        assert( buffer && "'buffer' is null." );
        assert( component.GetCBuffer().lock() == buffer && "'component' must be related to 'buffer'." );
        
        MutexLocker lck( m_mutex );
        
        auto it = std::find( m_vbufs.begin() , m_vbufs.end() , buffer );
        if ( it == m_vbufs.end() )
            m_vbufs.push_back( buffer );
        
        m_comps.push_back( component );
        m_dirty.store( true );
    }
    
    ////////////////////////////////////////////////////////////
    void Mesh::AddVertexCBuffer( const Shared < CBuffer >& buffer )
    {
        assert( buffer && "'buffer' is null." );
        MutexLocker lck( m_mutex );
        
        auto it = std::find( m_vbufs.begin() , m_vbufs.end() , buffer );
        if ( it == m_vbufs.end() )
        {
            m_vbufs.push_back( buffer );
            m_dirty.store( true );
        }
    }
    
    ////////////////////////////////////////////////////////////
    void Mesh::AddVertexComponent( const VertexComponent& component )
    {
        MutexLocker lck( m_mutex );
        m_comps.push_back( component );
        m_dirty.store( true );
    }
    
    ////////////////////////////////////////////////////////////
    void Mesh::SetVertexCount( uint32_t count )
    {
        m_vcount.store( count );
        m_dirty.store( true );
    }
    
    ////////////////////////////////////////////////////////////
    void Mesh::SetIndexCBuffer( const Shared < CBuffer >& buffer , uint32_t count , IndexType type )
    {
        assert( buffer && "'buffer' is null." );
        assert( count && "'count' is 0." );
        assert( type != IndexType::Unknown && "'type' is unknown." );
        
        MutexLocker lck( m_mutex );
        m_ibuf = buffer ;
        m_icount.store( count );
        m_itype = type ;
        m_dirty.store( true );
    }
    
    ////////////////////////////////////////////////////////////
    void Mesh::SetMaterial( const Weak < Material >& material )
    {
        MutexLocker lck( m_mutex );
        m_material = material ;
    }
    
    ////////////////////////////////////////////////////////////
    void Mesh::GenVertexCommands( const Weak < RenderWindow >& renderwindow )
    {
        assert( !renderwindow.expired() && "'renderwindow' expired." );
        
        if ( !m_dirty.load() )
            return ;
        
        auto rwindow = renderwindow.lock();
        MutexLocker lck( m_mutex );
        
        if ( !m_vbufs.empty() && !m_comps.empty() )
        {
            auto command = rwindow->CreateVertexCommand( m_comps , m_vbufs , m_vcount.load() , m_ibuf , m_icount.load() , m_itype );
            assert( command && "'RenderWindow::CreateVertexCommand()' failed." );
            m_command = command ;
            m_dirty.store( false );
        }

        for ( auto& submesh : m_submeshes )
        {
            submesh->GenVertexCommands( renderwindow );
        }
    }
    
    ////////////////////////////////////////////////////////////
    void Mesh::AddSubmesh( const Shared < Mesh >& submesh )
    {
        assert( submesh && "'submesh' is null." );
        MutexLocker lck( m_mutex );
        m_submeshes.push_back( submesh );
    }
    
    ////////////////////////////////////////////////////////////
    SharedVector < VertexCommand > Mesh::GetVertexCommands() const
    {
        MutexLocker lck( m_mutex );
        SharedVector < VertexCommand > retvalue ;
        
        if ( m_command )
            retvalue.push_back( m_command );
        
        for ( auto& submesh : m_submeshes )
        {
            auto subret = submesh->GetVertexCommands();
            retvalue.insert( retvalue.end() , subret.begin() , subret.end() );
        }
        
        return retvalue ;
    }
    
    ////////////////////////////////////////////////////////////
    Shared < VertexCommand > Mesh::GetVertexCommand() const
    {
        MutexLocker lck( m_mutex );
        return m_command ;
    }
}
