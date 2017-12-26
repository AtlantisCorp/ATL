//  ========================================================================  //
//
//  File    : ATL/MeshNode.cpp
//  Project : atlresource
//  Author  : Luk2010
//  Date    : 06/12/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#include <ATL/MeshNode.hpp>
#include <ATL/RenderCommand.hpp>

#include <ATL/AggregatedMaterial.hpp>
#include <ATL/AggregatedNode.hpp>
#include <ATL/AggregatedGroup.hpp>

namespace atl
{
	////////////////////////////////////////////////////////////
	Shared < AggregatedNode > MeshNode::CreateAggregatedNode( const NodesBySubtype& lsnodes , const AggregatedGroup& group ) const
	{
		auto mesh = m_mesh.Get().lock();
		assert( mesh );
		
		auto vcommand = mesh->GetVertexCommand();
		assert( vcommand );
		
		auto agmaterial = std::make_shared < AggregatedMaterial >();
		assert( agmaterial );
		
		auto command = std::make_shared < RenderCommand >( vcommand , agmaterial );
		assert( command );
		
		auto agnode = std::make_shared < AggregatedNode >( lsnodes , command , agmaterial );
		assert( anode );
		
		return agnode ;
	}
	
	////////////////////////////////////////////////////////////
	MeshNode::MeshNode( const Weak < Mesh >& mesh ) : m_mesh( mesh )
	{
		
	}
	
	////////////////////////////////////////////////////////////
	MeshNode::~MeshNode()
	{
		
	}
	
    ////////////////////////////////////////////////////////////
    void MeshNode::Update( NodesBySubtype& lsnodes , AggregatedGroup& group ) const
    {
        if ( m_mesh.IsDirty() )
        {
            // When handled mesh is dirty, it means user have changed the mesh handled by this
            // node. 'group' holds the old AggregatedNode, but it must be replaced with a correct
            // aggregated node. How to retrieve the old aggregated node ? We can do easily this thing:
            // if group holds only weaked pointer to those aggregated nodes, mesh node can hold a shared
            // pointer and every nodes in the group are invalidated when clearing the aggregated node's list.
            // Thus, here we clear the node's list and repeat the normal node's creation.
            MutexLocker lck( m_mutex );
            m_agnodes.clear();
            m_mesh.Clean();
        }
        
        // Tries to find an AggregatedNode registered in the group for the given lsnodes map. If not found,
        // we must create a new aggregated node.
        
        MutexLocker lck( m_mutex );
        lsnodes[GetSubtype()] = std::const_pointer_cast < Node >( shared_from_this() );
        
        auto agit = std::find_if( m_agnodes.begin() , m_agnodes.end() , [lsnodes,group](const Shared<AggregatedNode>& agnode) {
            assert( agnode );
            return agnode->IsLsnodesEqual( lsnodes , group );
        });
        
        if ( agit == m_agnodes.end() )
        {
            auto agnode = CreateAggregatedNode( lsnodes , group );
            assert( agnode );
            
            m_agnodes.push_back( agnode );
            group.AppendNode( agnode );
        }
        
        else
        {
            auto agnode = group.FindNode( *agit );
            if ( agnode.expired() )
            {
                group.AppendNode( agnode );
            }
        }
        
        return Node::Update( lsnodes , group );
    }
}
