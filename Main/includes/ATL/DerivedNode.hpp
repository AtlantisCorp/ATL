//  ========================================================================  //
//
//  File    : ATL/DerivedNode.hpp
//  Project : atlresource
//  Author  : Luk2010
//  Date    : 23/12/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#ifndef DerivedNode_hpp
#define DerivedNode_hpp

#include <ATL/Node.hpp>

#include <ATL/AggregatedMaterial.hpp>
#include <ATL/RenderCommand.hpp>

namespace atl
{
    ////////////////////////////////////////////////////////////
    /// \brief Base class for derived nodes.
    ///
    /// Every nodes that use the aggregate/update subsystem must
    /// derive from this class, and not from the basic 'Node' class.
    ///
    /// A derived node holds a superficial subtree structure, which
    /// contains other derived node of the same type. This way, node's
    /// internal subtree structure is not involved into the general
    /// specific subtree structure needed for subtyped nodes.
    ///
    /// As an example, think about PositionNode: its logical parent
    /// is the englobing PositionNode, but its internal parent might
    /// be another node, like 'MaterialNode' or whatever. Two subtrees
    /// are superposed one onto another.
    ///
    /// A user always can access Node's internal representation by
    /// using 'Base()' method.
    ///
    ////////////////////////////////////////////////////////////
    template < typename Class >
    class DerivedNode : protected Node , public Subtree < Class >
    {
    protected:
        
        ////////////////////////////////////////////////////////////
        /// \brief Returns true if the given node should be added to
        /// this node's subtree.
        ///
        ////////////////////////////////////////////////////////////
        virtual bool ShouldAddChild( const Shared < Class >& child ) const
        {
            return true ;
        }
        
    public:
        
        ////////////////////////////////////////////////////////////
        DerivedNode( const Node::Subtype& subtype ) : Subtree < Class >() , Node( subtype )
        {
            
        }
        
        ////////////////////////////////////////////////////////////
        virtual ~DerivedNode()
        {
            
        }
        
        ////////////////////////////////////////////////////////////
        virtual void AddChild( const Shared < Class >& child )
        {
            Node::AddChild( std::static_pointer_cast < Node >( child ) );
            
            if ( ShouldAddChild( child ) )
            {
                Subtree < Class >::AddChild( child );
            }
        }
        
        ////////////////////////////////////////////////////////////
        virtual void RemoveChild( const Shared < Class >& child )
        {
            Node::RemoveChild( std::static_pointer_cast < Node >( child ) );
            
            if ( ShouldRemoveChild( child ) )
            {
                Subtree < Class >::RemoveChild( child );
            }
        }
        
        ////////////////////////////////////////////////////////////
        virtual void ResetChildren()
        {
            Node::ResetChildren();
            Subtree < Class >::ResetChildren();
        }
        
        ////////////////////////////////////////////////////////////
        virtual void Aggregate( AggregatedMaterial& material , RenderCommand& command ) const
        {
            // Naive version only launch aggregates on superficial subtree's parent.
            auto parent = Subtree < Class >::GetParent();
            
            if ( parent )
            {
                parent->Aggregate( material , command );
            }
        }
        
        ////////////////////////////////////////////////////////////
        virtual void Update( NodesBySubtype& lsnodes , AggregatedGroup& group ) const
        {
            Node::Update( lsnodes , group );
        }
        
        ////////////////////////////////////////////////////////////
        /// \brief Returns this node as the Node's base underlying
        /// this interface.
        ///
        ////////////////////////////////////////////////////////////
        Node& Base()
        {
            return *( static_cast < Node* >( this ) );
        }
        
        ////////////////////////////////////////////////////////////
        /// \brief Returns this node as Node's base.
        ///
        ////////////////////////////////////////////////////////////
        const Node& Base() const
        {
            return *( static_cast < const Node* >( this ) );
        }
    };
}

#endif /* DerivedNode_hpp */
