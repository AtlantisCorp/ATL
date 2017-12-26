//  ========================================================================  //
//
//  File    : ATL/AggregatedGroup.cpp
//  Project : atlresource
//  Author  : Luk2010
//  Date    : 11/12/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#include <ATL/AggregatedGroup.hpp>

namespace atl
{
    ////////////////////////////////////////////////////////////
    AggregatedGroup::AggregatedGroup()
    {
        
    }
    
    ////////////////////////////////////////////////////////////
    AggregatedGroup::~AggregatedGroup()
    {
        
    }
    
    ////////////////////////////////////////////////////////////
    void AggregatedGroup::AppendNode( const Shared < AggregatedNode >& node )
    {
        assert( node );
        
        {
            MutexLocker lck( m_mutex );
            m_nodes.push_back( node );
        }
        
        // Checks if the node already has this group as parent. An AggregatedNode
        // can be kept by only one AggregatedGroup at a time, so it should have only
        // one parent. However, when modifying the node's group, it should notify the
        // old group it will not be one of its child anymore.
        node->SetParentGroup( shared_from_this() );
    }
    
    ////////////////////////////////////////////////////////////
    Weak < AggregatedNode > AggregatedGroup::FindNode( const Shared < AggregatedNode >& node ) const
    {
        assert( node );
        MutexLocker lck( m_mutex );
        
        auto it = std::find_if( m_nodes.begin() , m_nodes.end() , [node]( const Weak < AggregatedNode >& wnode ) {
            return wnode.lock() == node ;
        });
        
        if ( it != m_nodes.end() )
        return *it ;
        
        else
        return Weak < AggregatedNode >();
    }
    
    ////////////////////////////////////////////////////////////
    void AggregatedGroup::NotifiateNodeDestroyed( const Shared < AggregatedNode >& node )
    {
        assert( node );
        MutexLocker lck( m_mutex );
        
        auto it = std::find_if( m_nodes.begin() , m_nodes.end() , [node]( const Weak < AggregatedNode >& wnode ) {
            return wnode.lock() == node ;
        });
        
        if ( it != m_nodes.end() )
        m_nodes.erase( it );
    }
    
    ////////////////////////////////////////////////////////////
    void AggregatedGroup::NotifiateNodeQuit( const Shared < AggregatedNode >& node )
    {
        assert( node );
        MutexLocker lck( m_mutex );
        
        auto it = std::find_if( m_nodes.begin() , m_nodes.end() , [node]( const Weak < AggregatedNode >& wnode ) {
            return wnode.lock() == node ;
        });
        
        if ( it != m_nodes.end() )
        m_nodes.erase( it );
    }
}
