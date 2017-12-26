//  ========================================================================  //
//
//  File    : ATL/MeshNode.hpp
//  Project : atlresource
//  Author  : Luk2010
//  Date    : 30/11/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#ifndef MeshNode_hpp
#define MeshNode_hpp

#include <ATL/Node.hpp>
#include <ATL/Mesh.hpp>

namespace atl
{
    ////////////////////////////////////////////////////////////
    class AggregatedNode ;
    
    ////////////////////////////////////////////////////////////
    /// \brief Holds a Weak Mesh.
    ///
    ///
    ///
    ////////////////////////////////////////////////////////////
    class MeshNode : public Node
    {
        ////////////////////////////////////////////////////////////
        Detail::WeakDirtable < Mesh >           m_mesh ;    ///< Handled Mesh object.
        mutable SharedVector < AggregatedNode > m_agnodes ; ///< AggregatedNodes created by the mesh node.
        mutable Mutex                           m_mutex ;   ///< Access AggregatedNodes.
        
    public:
        
        ////////////////////////////////////////////////////////////
        /// \brief Construct a node with a Mesh.
        ///
        ////////////////////////////////////////////////////////////
        MeshNode( const Weak < Mesh >& mesh , const Weak < Node >& parent = Weak < Node >() );
        
        ////////////////////////////////////////////////////////////
        virtual ~MeshNode();
        
        ////////////////////////////////////////////////////////////
        virtual void SetMesh( const Weak < Mesh >& mesh );
        
        ////////////////////////////////////////////////////////////
        virtual Weak < Mesh > GetMesh() const ;
        
        ////////////////////////////////////////////////////////////
        /// \brief Updates AggregatedNode for the given lsnodes map,
        /// only if mesh has changed. 
        ///
        ////////////////////////////////////////////////////////////
        virtual void Update( NodesBySubtype& lsnodes , AggregatedGroup& group ) const ;
    };
}

#endif /* MeshNode_hpp */
