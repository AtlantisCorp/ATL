//  ========================================================================  //
//
//  File    : ATL/Scene.hpp
//  Project : atlresource
//  Author  : Luk2010
//  Date    : 21/11/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#ifndef Scene_hpp
#define Scene_hpp

#include <ATL/StdIncludes.hpp>

namespace atl
{
    ////////////////////////////////////////////////////////////
    class SceneGraph ;
    class CameraGraph ;
    class Camera ;
    class Program ;
    class Material ;
    class Mesh ;
    class RenderNode ;
    
    ////////////////////////////////////////////////////////////
    /// \brief Organizes a scene graph and one or more camera graphs
    /// to coordinate aggregate stage with object's update stage.
    ///
    /// A Scene is composed of two main elements: a scene graph, which
    /// hold and organize position nodes, and one or more camera graph(s),
    /// that hold render nodes and aggregated nodes.
    /// SceneGraph is responsible for organizing and maintaining the
    /// positionable structures (i.e. when a node moves, what does it do?).
    /// CameraGraph is responsible for collecting and managing aggregated nodes
    /// from render nodes.
    ///
    /// A Scene must be updated as often as possible to maintain aggregated
    /// node's materials at the same point of the real node's materials.
    /// It is recommended to use 'StartAsync()' to start a new thread where
    /// the Scene continuously updates CameraGraph's aggregates.
    ///
    /// As CameraGraph is also a derived of Object, it will be updated by a
    /// given RenderTarget. You must link the CameraGraph with the desired
    /// RenderTarget for the CameraGraph to input its aggregates in the
    /// RenderTarget.
    ///
    /// \note Even if a default SceneGraph is attached to the Scene at construction,
    /// another SceneGraph can be attached to the Scene, releasing the previous one.
    /// This way you can load any SceneGraph and attach it to the Scene object.
    ///
    ////////////////////////////////////////////////////////////
    class Scene
    {
        ////////////////////////////////////////////////////////////
        Shared < SceneGraph >        m_scenegraph ; ///< SceneGraph attached to this scene.
        SharedVector < CameraGraph > m_camgraphs ;  ///< CameraGraph(s) attached to this scene.
        mutable Spinlock             m_spinlock ;   ///< Access to vector.
        
    public:
        
        ////////////////////////////////////////////////////////////
        /// \brief Constructs a new Scene.
        ///
        /// \param scenegraph A SceneGraph object to be used by this
        ///                   scene. If null (default), a default SceneGraph
        ///                   object is created.
        ///
        ////////////////////////////////////////////////////////////
        Scene( const Shared < SceneGraph >& scenegraph = nullptr );
        
        ////////////////////////////////////////////////////////////
        virtual ~Scene();
        
        ////////////////////////////////////////////////////////////
        /// \brief Release the previous scene graph and use the provided
        /// one to manage position nodes.
        ///
        ////////////////////////////////////////////////////////////
        virtual void SetSceneGraph( const Shared < SceneGraph >& scenegraph );
        
        ////////////////////////////////////////////////////////////
        virtual Weak < SceneGraph > GetSceneGraph() const ;
        
        ////////////////////////////////////////////////////////////
        /// \brief Creates a default CameraGraph and adds it.
        ///
        ////////////////////////////////////////////////////////////
        virtual Weak < CameraGraph > CreateAndAddCamera( const Shared < Camera >& camera );
        
        ////////////////////////////////////////////////////////////
        /// \brief Adds a CameraGraph to this scene.
        ///
        ////////////////////////////////////////////////////////////
        virtual void AddCamera( const Shared < CameraGraph >& camera );
        
        ////////////////////////////////////////////////////////////
        virtual void RemoveCamera( const Shared < Camera >& camera );
        
        ////////////////////////////////////////////////////////////
        virtual void RemoveCamera( const Shared < CameraGraph >& graph );
        
        ////////////////////////////////////////////////////////////
        virtual void ResetCameras();
        
        ////////////////////////////////////////////////////////////
        virtual Weak < CameraGraph > GetCameraGraph( const Shared < Camera >& camera ) const ;
        
        ////////////////////////////////////////////////////////////
        /// \brief Creates a RenderNode from given data, and, if drawable,
        /// adds it to the given CameraGraph.
        ///
        ////////////////////////////////////////////////////////////
        virtual Shared < RenderNode > CreateAndAddRenderNode( const glm::vec3& position ,
                                                              const Weak < Program >& program ,
                                                              const Weak < Material >& material ,
                                                              const Weak < Mesh >& mesh             = Weak < Mesh >() ,
                                                              const Weak < CameraGraph >& graph     = Weak < CameraGraph >() );
    };
}

#endif /* Scene_hpp */
