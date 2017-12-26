//  ========================================================================  //
//
//  File    : ATL/SceneGraph.hpp
//  Project : atlresource
//  Author  : Luk2010
//  Date    : 21/11/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#ifndef SceneGraph_hpp
#define SceneGraph_hpp

#include <ATL/StdIncludes.hpp>
#include <ATL/Resource.hpp>

namespace atl
{
    ////////////////////////////////////////////////////////////
    class PositionNode ;
    class Program ;
    class ProgramNode ;
    class Material ;
    class MaterialNode ;
    class Mesh ;
    class MeshNode ;
    class RenderNode ;
    
    ////////////////////////////////////////////////////////////
    /// \brief Interface provided to create and organize different
    /// nodes.
    ///
    /// Generally those nodes are organized by position nodes, which
    /// contains informations about their neighbourgs, their position
    /// parent, etc. Other nodes are children of those nodes.
    /// You can derive from this class and create another organization
    /// for your scene. This can help finding neighbourgs, implementing
    /// new way to aggregate lights, and other things.
    ///
    /// As a SceneGraph can be implemented by anyone, it should correspond
    /// to a virtual MIME type (and could even be loaded from an external
    /// file) and derive from Resource.
    ///
    ////////////////////////////////////////////////////////////
    class SceneGraph : public Resource
    {
        ////////////////////////////////////////////////////////////
        Shared < PositionNode > m_root ; ///< Root position node in this graph.
        mutable Mutex           m_mutex ; ///< Mutex to lock when performing some action.
        
    public:
        
        ////////////////////////////////////////////////////////////
        SceneGraph();
        
        ////////////////////////////////////////////////////////////
        virtual ~SceneGraph();
        
        ////////////////////////////////////////////////////////////
        /// \brief Creates a Position node, without any parent nor
        /// children, and return it.
        ///
        ////////////////////////////////////////////////////////////
        virtual Shared < PositionNode > CreatePositionNode( const glm::vec3& position ) const ;
        
        ////////////////////////////////////////////////////////////
        /// \brief Creates a Program node.
        ///
        ////////////////////////////////////////////////////////////
        virtual Shared < ProgramNode > CreateProgramNode( const Weak < Program >& program ) const ;
        
        ////////////////////////////////////////////////////////////
        /// \brief Creates a Material node.
        ///
        ////////////////////////////////////////////////////////////
        virtual Shared < MaterialNode > CreateMaterialNode( const Weak < Material >& material ) const ;
        
        ////////////////////////////////////////////////////////////
        /// \brief Creates a Mesh node.
        ///
        ////////////////////////////////////////////////////////////
        virtual Shared < MeshNode > CreateMeshNode( const Weak < Mesh >& mesh ) const ;
        
        ////////////////////////////////////////////////////////////
        /// \brief Creates a RenderNode.
        ///
        ////////////////////////////////////////////////////////////
        virtual Shared < RenderNode > CreateRenderNode( const Shared < PositionNode >& posnode ) const ;
        
        ////////////////////////////////////////////////////////////
        /// \brief Adds the given position node to the root node.
        ///
        ////////////////////////////////////////////////////////////
        virtual void AddPositionNode( const Shared < PositionNode >& posnode );
        
        ////////////////////////////////////////////////////////////
        virtual Weak < PositionNode > GetRootNode() const ;
    };
}

#endif /* SceneGraph_hpp */
