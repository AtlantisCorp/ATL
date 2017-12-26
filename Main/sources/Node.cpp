//  ========================================================================  //
//
//  File    : ATL/Node.cpp
//  Project : atlresource
//  Author  : Luk2010
//  Date    : 21/11/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#include <ATL/Node.hpp>

namespace atl
{
    ////////////////////////////////////////////////////////////
    Node::Node( const Node::Subtype& type ) : m_type( type )
    {
        
    }
    
    ////////////////////////////////////////////////////////////
    Node::~Node()
    {
        
    }
    
    ////////////////////////////////////////////////////////////
    void Node::AddChild( const Shared < Node >& child )
    {
        Subtree < Node >::AddChild( child );
        Detail::Dirtable::SetDirty( true );
    }
    
    ////////////////////////////////////////////////////////////
    void Node::RemoveChild( const Shared < Node >& child )
    {
        Subtree < Node >::RemoveChild( child );
        Detail::Dirtable::SetDirty( true );
    }
    
    ////////////////////////////////////////////////////////////
    void Node::ResetChildren()
    {
        Subtree < Node >::ResetChildren();
        Detail::Dirtable::SetDirty( true );
    }
    
    ////////////////////////////////////////////////////////////
    uint32_t Node::GetSubtype() const
    {
        return m_type.load();
    }
    
    ////////////////////////////////////////////////////////////
    void Node::Aggregate( AggregatedMaterial& , RenderCommand& ) const
    {
        
    }
    
    ////////////////////////////////////////////////////////////
    void Node::Update( NodesBySubtype& lsnodes , AggregatedGroup& group ) const
    {
        lsnodes[GetSubtype()] = std::const_pointer_cast < Node >( Subtree < Node >::shared_from_this() );
        auto children = GetChildren();
        
        for ( auto const& child : children )
        {
            assert( child && "Null child was conserved in a node. (Illegal operation)" );
            child->Update( lsnodes , group );
        }
        
        if ( Detail::Dirtable::IsDirty() )
            Detail::Dirtable::SetDirty( false );
    }
}
