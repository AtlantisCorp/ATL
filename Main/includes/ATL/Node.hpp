//  ========================================================================  //
//
//  File    : ATL/Node.hpp
//  Project : atlresource
//  Author  : Luk2010
//  Date    : 21/11/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#ifndef Node_hpp
#define Node_hpp

#include <ATL/StdIncludes.hpp>
#include <ATL/Dirtable.hpp>
#include <ATL/Subtree.hpp>

namespace atl
{
    ////////////////////////////////////////////////////////////
    class AggregatedMaterial ;
    class RenderCommand ;
    class AggregatedGroup ;
    class Node ;
    
    ////////////////////////////////////////////////////////////
    typedef Map < uint32_t , Weak < Node > > NodesBySubtype ;
    
    ////////////////////////////////////////////////////////////
    /// \brief Interface usable by SceneGraph and CameraGraph to
    /// organize their entities.
    ///
    /// A Node is part of an internal SceneGraph tree. However, the
    /// internal representation of the tree is not used everytime.
    ///
    /// A Node is also part of a special subtree, created only by Node
    /// subtypes. For example, a subtype 'Material' will behave to the
    /// subtree 'Materials' in the current Scene.
    ///
    /// Node's action on the rendering system occurs in two phases:
    ///
    /// - SCENE-UPDATE: Calls 'Update'. If the node is renderable, it
    /// should create in the given AggregateGroup a new AggregatedNode
    /// (if dirty/needed). If the node is not renderable, but is not
    /// transparent, it must register itself to the current binding
    /// map given by the function. At each call, binding map is different
    /// and goes for every renderable nodes to make them register their
    /// aggregated nodes differently.
    ///
    /// - AGGREGATION: Calls 'Aggregate'. If the node has an action in the
    /// rendering pipeline, it must modify the given current rendercommand
    /// by updating the command's material (or directly modify the given
    /// AggregatedMaterial).
    ///
    /// Subtree holdings and inheritance: A Node's subtype defines a
    /// specific subtree. For example, subtype 'Material' defines
    /// a subtree for every material's nodes registered in the Scene.
    /// Aggregation's phase should be passed to the next subtree's parent
    /// of each node. For example, a MaterialNode will pass the Aggregation
    /// subsystem to its MaterialNode's next parent, and the Aggregated
    /// Material will inherits its parents properties that weren't set
    /// by the MaterialNode.
    ///
    ////////////////////////////////////////////////////////////
    class Node : public Subtree < Node > , public Detail::Dirtable
    {
    public:
        
        ////////////////////////////////////////////////////////////
        /// \brief Defines basic node subtypes.
        ///
        /// Values defined here are arbitrary, and a custom subtype can
        /// be every values above the last subtype.
        ///
        ////////////////////////////////////////////////////////////
        enum Subtype
        {
            Null       = 0 , ///< Default subtype when creating a Node without any preferences.
            Position   = 1 , ///< Subtype for nodes deriving 'PositionNode'.
            Program    = 2 , ///< Subtype for nodes deriving 'ProgramNode'.
            Material   = 3 , ///< Subtype for nodes deriving 'MaterialNode'.
            Mesh       = 4 , ///< Subtype for nodes deriving 'MeshNode'.
            Aggregated = 5 , ///< Subtype for nodes deriving 'AggregatedNode'. A subtype is provided for
                             ///  those specific nodes, because they may have a particular subtree behaviour.
            
            /// Every custom subtypes should have at least this value more 'x'.
            Custom
        };
        
    private:
        
        ////////////////////////////////////////////////////////////
        Atomic < uint32_t >   m_type ;     ///< Type associated to this node.
        mutable Mutex         m_mutex ;    ///< Mutex to access those data.
        
    public:
        
        ////////////////////////////////////////////////////////////
        Node( const Subtype& type = Subtype::Null );
        
        ////////////////////////////////////////////////////////////
        virtual ~Node();
        
        ////////////////////////////////////////////////////////////
        virtual uint32_t GetSubtype() const ;
        
        ////////////////////////////////////////////////////////////
        virtual void AddChild( const Shared < Node >& child );
        
        ////////////////////////////////////////////////////////////
        virtual void RemoveChild( const Shared < Node >& child );
        
        ////////////////////////////////////////////////////////////
        virtual void ResetChildren();
        
        ////////////////////////////////////////////////////////////
        /// \brief Aggregate informations in this node to the given
        /// material and pass it to the parent node.
        ///
        /// \note As the default class does not do anything, this is
        /// a pass-through function that just call 'Aggregate()' from
        /// the parent's node if this one is valid.
        ///
        ////////////////////////////////////////////////////////////
        virtual void Aggregate( AggregatedMaterial& , RenderCommand& ) const ;
        
        ////////////////////////////////////////////////////////////
        /// \brief Updates the given AggregateGroup.
        ///
        /// Called by 'CameraGraph::Update()', default behaviour only
        /// pass the given group to children update function.
        ///
        /// A renderable node should create one or more AggregateNode
        /// in this group if none is found. Created AggregateNode always
        /// have their creator as parent to initiate the Aggregation
        /// routine. For example, a MeshNode can create an AggregateNode
        /// in the given group with its rendercommand, and then pass the
        /// group to its submeshes's nodes.
        ///
        /// \param lsnodes 'Last-Seen' nodes, by type. By default, the node
        ///                register itself into this map to be reported into
        ///                the next AggregatedNode.
        /// \param group   AggregateGroup to modify. Create a new AggregatedNode
        ///                only when needed, i.e. when 'lsnodes' differs from the
        ///                current one held by your AggregatedNode. In the optic that
        ///                a MeshNode (for example) can update from more than one MaterialNode
        ///                (for example), the mesh node might check 'group' if
        ///                the 'lsnodes' set is already available (including itself)
        ///                for an already registered node. If not, it must create
        ///                a new aggregated node and destroy the old one.
        ///
        ////////////////////////////////////////////////////////////
        virtual void Update( NodesBySubtype& lsnodes , AggregatedGroup& group ) const ;
    };
}

#endif /* Node_hpp */
