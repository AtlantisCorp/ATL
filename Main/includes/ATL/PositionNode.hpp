//  ========================================================================  //
//
//  File    : ATL/PositionNode.hpp
//  Project : atlresource
//  Author  : Luk2010
//  Date    : 21/11/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#ifndef PositionNode_hpp
#define PositionNode_hpp

#include <ATL/StdIncludes.hpp>
#include <ATL/DerivedNode.hpp>

namespace atl
{
    ////////////////////////////////////////////////////////////
    /// \brief Interface for nodes with type 'Position'.
    ///
    /// PositionNode should organize with other PositionNode depending
    /// on its position. It should be able to generate a Model Matrix
    /// on aggregation. A PositionNode is always relative to its parent
    /// position node. Thus, a PositionNode should be used to describe
    /// a position relative to an 'origin' point, or a 'parent' point.
    /// In a system where one wants to say 'place the object at position
    /// (X , Y , Z)' he should add 'from (X , Y , Z) point of view', which
    /// should be, by default, the origin position node.
    ///
    /// When aggregating this node, the model matrix is multiplicated
    /// by the current Model Matrix in the Material parameters. Then the
    /// aggregation is passed to the position's parent, which is not the
    /// node's parent. Position's parent is the Position node preceding
    /// this position in a virtual space. It generally is an englobing
    /// space part when doing space division.
    ///
    /// \note A Position node may or may not have children. This depend on
    /// your implementation and your vision of the space division.
    ///
    ////////////////////////////////////////////////////////////
    class PositionNode : public DerivedNode < PositionNode >
    {
        ////////////////////////////////////////////////////////////
        glm::vec3             m_position ; ///< Position of the node.
        glm::mat4             m_modelmat ; ///< Cached model matrix for this position.
        mutable Spinlock      m_spinlock ; ///< Spinlock to access position and model matrix.
        
    public:
        
        ////////////////////////////////////////////////////////////
        /// \brief Constructs a new PositionNode.
        ///
        /// \param position   Position to set to this node, relative to
        ///                   'relativeto' arg.
        /// \param relativeto Position's node that will be used as the
        ///                   parent (or inherited) position for this
        ///                   node.
        /// \param parent     Real parent of this node. It may not be
        ///                   a PositionNode. However, if given an expired
        ///                   Weak object, 'relativeto' is used.
        ///
        ////////////////////////////////////////////////////////////
        PositionNode( const glm::vec3& position );
        
        ////////////////////////////////////////////////////////////
        virtual ~PositionNode();
        
        ////////////////////////////////////////////////////////////
        virtual glm::vec3 GetPosition() const ;
        
        ////////////////////////////////////////////////////////////
        /// \brief Changes the current position of this node.
        ///
        ////////////////////////////////////////////////////////////
        virtual void SetPosition( const glm::vec3& position );
        
        ////////////////////////////////////////////////////////////
        /// \brief Aggregate relative model matrix and pass the Material
        /// to the position's parent, if not expired.
        ///
        /// \note Right *after* aggregating this node's position's parent,
        /// the position node should pass the aggregation process to its
        /// immediate parent. However, doing this is not permitted because
        /// passing to its parent may lead to other meshes or material aggregating
        /// the material, or even the same position parent may aggregate more than
        /// once the material. This means the Position node is *always* the last
        /// node to aggregate the material from its direct children. Thus a
        /// Position node should always be the last node in a rendering chain.
        ///
        /// \warning If Position node aggregates a material before it has reached
        /// the target mesh and/or material, it will not pass the aggregation process
        /// to them and the target will not be rendered.
        ///
        ////////////////////////////////////////////////////////////
        virtual void Aggregate( AggregatedMaterial& material , RenderCommand& ) const ;
    };
}

#endif /* PositionNode_hpp */
