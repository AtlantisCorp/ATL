//  ========================================================================  //
//
//  File    : ATL/Subtree.hpp
//  Project : atlresource
//  Author  : Luk2010
//  Date    : 23/12/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#ifndef Subtree_hpp
#define Subtree_hpp

#include <ATL/StdIncludes.hpp>

namespace atl
{
    ////////////////////////////////////////////////////////////
    /// \brief Defines a basic tree design.
    ///
    /// You can define a new tree by deriving a new class from this
    /// one. Basically, a node tree is always a tree because it represents
    /// the root of its own subtree.
    ///
    /// Uses in Node's subsystem: Derived nodes should derive from
    /// this class. As Node also derives from this class, parents and
    /// children are dependant of the base used. If we want the internal
    /// node representation of parents and children, we should use
    /// functions prefixed with 'Node::'. If we want the actual parent/children
    /// subtree from the derived class, we use normal functions.
    ///
    /// It is useful because only Node cares about its internal tree
    /// representation. Derived classes like PositionNode have different
    /// parent and children (that are also PositionNode) and thus, can
    /// be retrieved using this class.
    ///
    /// \note Update phase cares about internal Node's tree, whereas
    /// Aggregation cares about Derived subtrees from nodes.
    ///
    /// \see Node, DerivedNode
    ///
    ////////////////////////////////////////////////////////////
    template < typename Class >
    class Subtree : public std::enable_shared_from_this < Subtree < Class > >
    {
        ////////////////////////////////////////////////////////////
        Weak < Subtree < Class > >         m_parent ;
        SharedVector < Subtree < Class > > m_children ;
        mutable Spinlock                   m_spinlock ;
        
        ////////////////////////////////////////////////////////////
        /// \brief Ensure given child is not in the tree anymore.
        ///
        ////////////////////////////////////////////////////////////
        virtual void NotifiateChildErasure( const Shared < Subtree < Class > >& child )
        {
            Spinlocker lck( m_spinlock );
            assert( child );
            
            auto it = std::find( m_children.begin() , m_children.end() , child );
            
            if ( it != m_children.end() )
                m_children.erase( it );
        }
        
        ////////////////////////////////////////////////////////////
        /// \brief Ensure given child changes its parent to given node,
        /// notifying its old parent from the parent's erasure.
        ///
        ////////////////////////////////////////////////////////////
        virtual void NotifiateParentChanged( const Shared < Subtree < Class > >& parent )
        {
            Spinlocker lck( m_spinlock );
            
            if ( !m_parent.expired() )
            {
                auto oldparent = m_parent.lock();
                assert( oldparent );
                
                oldparent->NotifiateChildErasure( shared_from_this() );
            }
            
            m_parent = parent ;
        }
        
    public:
        
        ////////////////////////////////////////////////////////////
        Subtree( const SharedVector < Class >& children = SharedVector < Class >() )
        : m_parent() , m_children( children )
        {
            
        }
        
        ////////////////////////////////////////////////////////////
        virtual ~Subtree()
        {
            Spinlocker lck( m_spinlock );
            
            // If our parent is not invalid, we must ensure we have unregistered from it.
            // We might be destroyed without notifying the parent.
            if ( !m_parent.expired() )
            {
                auto parent = m_parent.lock();
                assert( parent );
                
                auto thisptr = shared_from_this();
                assert( thisptr );
                
                parent->NotifiateChildErasure( thisptr );
            }
        }
        
        ////////////////////////////////////////////////////////////
        /// \brief Adds a child to this node.
        /// Child sees its parent change to this node.
        ///
        ////////////////////////////////////////////////////////////
        virtual void AddChild( const Shared < Class >& child )
        {
            Spinlocker lck( m_spinlock );
            assert( child );
            
            auto treeptr = std::static_pointer_cast < Subtree < Class > >( child );
            assert( treeptr );
            
            m_children.push_back( treeptr );
            child->NotifiateParentChanged( shared_from_this() );
        }
        
        ////////////////////////////////////////////////////////////
        /// \brief Removes a given node from this node's children.
        /// Resulting parent for the erased node is a null weak pointer.
        ///
        ////////////////////////////////////////////////////////////
        virtual void RemoveChild( const Shared < Class >& child )
        {
            if ( child )
                child->NotifiateParentChanged( nullptr );
        }
        
        ////////////////////////////////////////////////////////////
        /// \brief Returns true if 'm_parent' is null.
        ///
        ////////////////////////////////////////////////////////////
        virtual bool IsRoot() const
        {
            Spinlocker lck( m_spinlock );
            return m_parent.expired();
        }
        
        ////////////////////////////////////////////////////////////
        /// \brief Returns true if 'm_children' is empty.
        ///
        ////////////////////////////////////////////////////////////
        virtual bool IsLeaf() const
        {
            Spinlocker lck( m_spinlock );
            return m_children.empty();
        }
        
        ////////////////////////////////////////////////////////////
        /// \brief Returns this subtree's parent, if valid.
        ///
        ////////////////////////////////////////////////////////////
        virtual Shared < Class > GetParent() const
        {
            Spinlocker lck( m_spinlock );
            return std::static_pointer_cast < Class >( m_parent.lock() );
        }
        
        ////////////////////////////////////////////////////////////
        /// \brief Returns a copy of this subtree's children.
        ///
        ////////////////////////////////////////////////////////////
        virtual SharedVector < Class > GetChildren() const
        {
            Spinlocker lck( m_spinlock );
            SharedVector < Class > retvalue ;
            
            for ( auto child : m_children )
                retvalue.push_back( std::static_pointer_cast < Class >( child ) );
            
            return retvalue ;
        }
        
        ////////////////////////////////////////////////////////////
        /// \brief Empty children's list.
        ///
        ////////////////////////////////////////////////////////////
        virtual void ResetChildren()
        {
            Spinlocker lck( m_spinlock );
            m_children.clear();
        }
    };
}

#endif /* Subtree_hpp */
