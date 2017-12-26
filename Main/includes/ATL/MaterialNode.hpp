//  ========================================================================  //
//
//  File    : ATL/MaterialNode.hpp
//  Project : atlresource
//  Author  : Luk2010
//  Date    : 30/11/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#ifndef MaterialNode_hpp
#define MaterialNode_hpp

#include <ATL/DerivedNode.hpp>
#include <ATL/Material.hpp>

namespace atl
{
    ////////////////////////////////////////////////////////////
    class AggregatedMaterial ;
    
    ////////////////////////////////////////////////////////////
    /// \brief Specialized Node to handle Materials.
    ///
    /// Place in the node chain: MaterialNode should be placed
    /// between a PositionNode or a ProgramNode and a MeshNode or
    /// another MaterialNode.
    ///
    /// Update routine: MaterialNode creates AggregatedNode for children
    /// that respond positively to 'IsDirty'. This does not mean the handled
    /// child mesh is dirty, but only the 'node' itself containing the mesh
    /// (when the mesh is changed). It use 'EmitRenderCommand' on the MeshNode
    /// to create a new RenderCommand with dependent VertexCommands.
    ///
    /// \note 'EmitRenderCommand' should agglomerate Mesh's VertexCommand and
    /// the submesh's VertexCommands only if those are not linked to a different
    /// MaterialNode (direct child).
    ///
    /// Aggregation routine: MaterialNode set parameters in an AggregatedMaterial
    /// object. AggregatedMaterial remember which parameter has already been set
    /// and only allow one setting by aggregation.
    ///
    ////////////////////////////////////////////////////////////
    class MaterialNode : public DerivedNode < MaterialNode >
    {
        ////////////////////////////////////////////////////////////
        Weak < Material > m_material ; ///< Managed Material.
        
    public:
        
        ////////////////////////////////////////////////////////////
        MaterialNode( const Weak < Material >& material );
        
        ////////////////////////////////////////////////////////////
        virtual ~MaterialNode();
        
        ////////////////////////////////////////////////////////////
        virtual void SetMaterial( const Weak < Material >& material );
        
        ////////////////////////////////////////////////////////////
        virtual Weak < Material > GetMaterial() const ;
        
        ////////////////////////////////////////////////////////////
        /// \brief Aggregates owned material with given material.
        ///
        /// \note Custom parameters are ignored while aggregating the
        /// material. A Derived class might use custom parameters differently
        /// from this class and aggregate other parameters to the material.
        ///
        ////////////////////////////////////////////////////////////
        virtual void Aggregate( AggregatedMaterial& , RenderCommand& ) const ;
    };
}

#endif /* MaterialNode_hpp */
