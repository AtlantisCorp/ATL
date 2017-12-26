//  ========================================================================  //
//
//  File    : ATL/VertexCommand.cpp
//  Project : atlresource
//  Author  : Luk2010
//  Date    : 21/10/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#include <ATL/VertexCommand.hpp>
#include <ATL/VertexCommandVisitor.hpp>

namespace atl
{
    ////////////////////////////////////////////////////////////
    IDGenerator < VertexCommandId > VertexCommand::s_generator ;
    
    ////////////////////////////////////////////////////////////
    VertexCommand::VertexCommand()
    : m_id( s_generator.New() )
    , m_count( 0 ) , m_icount( 0 )
    , m_itype( IndexType::Unknown )
    , m_ctxtdata( 0 )
    {
        
    }
    
    ////////////////////////////////////////////////////////////
    VertexCommand::VertexCommand( uint32_t count , const VertexComponent& buffer ,
                                  uint32_t icount , const Shared < Buffer >& ibuffer ,
                                  IndexType itype )
    : m_id( s_generator.New() )
    , m_count( count )
    , m_icount( icount ) , m_ibuffer( ibuffer )
    {
        m_comps.push_back( buffer );
    }
    
    ////////////////////////////////////////////////////////////
    VertexCommand::VertexCommand( uint32_t count , const Vector < VertexComponent >& buffers ,
                                  uint32_t icount , const Shared < Buffer >& ibuffer ,
                                  IndexType itype )
    : m_id( s_generator.New() )
    , m_comps( buffers ) , m_count( count )
    , m_icount( icount ) , m_ibuffer( ibuffer )
    {
        
    }
    
    ////////////////////////////////////////////////////////////
    VertexCommand::~VertexCommand()
    {
        
    }
    
    ////////////////////////////////////////////////////////////
    VertexCommandId VertexCommand::GetId() const
    {
        return m_id.load();
    }
    
    ////////////////////////////////////////////////////////////
    uint32_t VertexCommand::GetVertexCount() const
    {
        return m_count.load();
    }
    
    ////////////////////////////////////////////////////////////
    void VertexCommand::SetVertexCount( uint32_t count )
    {
        m_count.store( count );
    }
    
    ////////////////////////////////////////////////////////////
    Vector < VertexComponent > VertexCommand::GetVertexComponents() const
    {
        Spinlocker lck( m_spinlock );
        return m_comps ;
    }
    
    ////////////////////////////////////////////////////////////
    void VertexCommand::SetVertexComponents( const Vector < VertexComponent >& buffers )
    {
        Spinlocker lck( m_spinlock );
        m_comps = buffers ;
    }
    
    ////////////////////////////////////////////////////////////
    void VertexCommand::AddVertexComponent( const VertexComponent& component )
    {
        Spinlocker lck( m_spinlock );
        m_comps.push_back( component );
    }
    
    ////////////////////////////////////////////////////////////
    uint32_t VertexCommand::GetIndexCount() const
    {
        return m_icount.load();
    }
    
    ////////////////////////////////////////////////////////////
    void VertexCommand::SetIndexCount( uint32_t count )
    {
        m_icount.store( count );
    }
    
    ////////////////////////////////////////////////////////////
    Weak < Buffer > VertexCommand::GetIndexBuffer() const
    {
        return m_ibuffer;
    }
    
    ////////////////////////////////////////////////////////////
    void VertexCommand::SetIndexBuffer( const Shared < Buffer >& buffer )
    {
        m_ibuffer = buffer ;
    }
    
    ////////////////////////////////////////////////////////////
    IndexType VertexCommand::GetIndexType() const
    {
        return m_itype.load();
    }
    
    ////////////////////////////////////////////////////////////
    void VertexCommand::SetIndexType( IndexType type )
    {
        m_itype.store( type );
    }
    
    ////////////////////////////////////////////////////////////
    void VertexCommand::AcceptVisitor( VertexCommandVisitor& visitor ) const
    {
        visitor.Visit( *this );
    }
}
