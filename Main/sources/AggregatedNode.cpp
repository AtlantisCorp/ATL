//  ========================================================================  //
//
//  File    : ATL/AggregatedNode.cpp
//  Project : atlresource
//  Author  : Luk2010
//  Date    : 11/12/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#include <ATL/AggregatedNode.hpp>
#include <ATL/AggregatedGroup.hpp>
#include <ATL/RenderCommand.hpp>
#include <ATL/AggregatedMaterial.hpp>

namespace atl
{
    ////////////////////////////////////////////////////////////
    AggregatedNode::AggregatedNode( const NodesBySubtype& lsnodes , const Shared < RenderCommand >& command , const Weak < AggregatedMaterial >& material )
    : atl::Node( Node::Subtype::Aggregated )
    , m_material( material.lock() )
    , m_command( command )
    , m_lsnodes( lsnodes )
    {
        
    }
    
    ////////////////////////////////////////////////////////////
    AggregatedNode::~AggregatedNode()
    {
        Spinlocker lck( m_spinlock );
        
        // We must notifiate our parent group if we have one. AggregatedGroup
        // never destroys the aggregated node but it keeps track of Weak pointers
        // and thus, they should be destroyed.
        if ( !m_group.expired() )
        {
            auto group = m_group.lock();
            assert( group );
            
            auto thisptr = std::static_pointer_cast < AggregatedNode >( shared_from_this() );
            assert( thisptr );
            
            group->NotifiateNodeDestroyed( thisptr );
        }
    }
    
    ////////////////////////////////////////////////////////////
    void AggregatedNode::SetRenderCommand( const Shared < RenderCommand >& command )
    {
        Spinlocker lck( m_spinlock );
        m_command = command ;
    }
    
    ////////////////////////////////////////////////////////////
    Shared < RenderCommand > AggregatedNode::GetRenderCommand() const
    {
        Spinlocker lck( m_spinlock );
        return m_command ;
    }
    
    ////////////////////////////////////////////////////////////
    void AggregatedNode::SetMaterial( const Shared < AggregatedMaterial >& material )
    {
        Spinlocker lck( m_spinlock );
        m_material = material ;
    }
    
    ////////////////////////////////////////////////////////////
    Shared < AggregatedMaterial > AggregatedNode::GetMaterial() const
    {
        Spinlocker lck( m_spinlock );
        return m_material ;
    }
    
    ////////////////////////////////////////////////////////////
    void AggregatedNode::Aggregation() const
    {
        Spinlocker lck( m_spinlock );
        
        assert( m_material );
        assert( m_command );

        AggregatedMaterial& material = const_cast < AggregatedMaterial& >( *(m_material.get()) );
        RenderCommand& command       = const_cast < RenderCommand& >( *(m_command.get()) );
        
        for ( auto it = m_lsnodes.begin() ; it != m_lsnodes.end() ; it++ )
        {
            auto node = it->second ;
            
            if ( !node.expired() )
            {
                auto nodeptr = node.lock();
                assert( nodeptr );
                
                nodeptr->Aggregate( material , command );
            }
        }
    }
    
    ////////////////////////////////////////////////////////////
    bool AggregatedNode::IsLsnodesEqual( const NodesBySubtype& lsnodes , const AggregatedGroup& group ) const
    {
        Spinlocker lck( m_spinlock );
        
        if ( m_group.expired() )
        {
            return m_lsnodes == lsnodes ;
        }
        
        else
        {
            auto groupptr = m_group.lock();
            assert( groupptr );
            
            return groupptr.get() == &group
                && m_lsnodes == lsnodes ;
        }
    }
    
    ////////////////////////////////////////////////////////////
    void AggregatedNode::SetParentGroup( const Shared < AggregatedGroup >& group )
    {
        Spinlocker lck( m_spinlock );
        
        if ( !m_group.expired() )
        {
            auto oldgroup = m_group.lock();
            assert( oldgroup );
            
            auto thisptr = std::static_pointer_cast < AggregatedNode >( shared_from_this() );
            assert( thisptr );
            
            oldgroup->NotifiateNodeQuit( thisptr );
        }
        
        m_group = group ;
    }
}
