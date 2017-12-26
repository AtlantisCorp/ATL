//  ========================================================================  //
//
//  File    : ATL/Scene.cpp
//  Project : atlresource
//  Author  : Luk2010
//  Date    : 21/11/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#include <ATL/Scene.hpp>
#include <ATL/Metaclass.hpp>
#include <ATL/SceneGraph.hpp>

#include <ATL/PositionNode.hpp>

namespace atl
{
    ////////////////////////////////////////////////////////////
    Scene::Scene( const Shared < SceneGraph >& scenegraph ) : m_scenegraph( scenegraph )
    {
        if ( !m_scenegraph )
        {
            m_scenegraph = std::static_pointer_cast < SceneGraph >( Metaclass < SceneGraph >().Create() );
            assert( m_scenegraph && "'m_scenegraph': Metaclass creation failure." );
        }
    }
    
    ////////////////////////////////////////////////////////////
    Scene::~Scene()
    {
        
    }
    
    ////////////////////////////////////////////////////////////
    void Scene::SetSceneGraph( const Shared < SceneGraph >& scenegraph )
    {
        std::atomic_store( &m_scenegraph , scenegraph );
    }
    
    ////////////////////////////////////////////////////////////
    Weak < SceneGraph > Scene::GetSceneGraph() const
    {
        return std::atomic_load( &m_scenegraph );
    }
    
    ////////////////////////////////////////////////////////////
    Weak < CameraGraph > Scene::CreateAndAddCamera( const Shared < Camera >& camera )
    {
        assert( camera && "'camera' is null." );
        
        auto graph = std::static_pointer_cast < CameraGraph >( Metaclass < CameraGraph >().Create() );
        assert( graph && "'graph': Metaclass creation failure." );
        
        Spinlocker lck( m_spinlock );
        m_camgraphs.push_back( graph );
        
        return graph ;
    }
    
    ////////////////////////////////////////////////////////////
    void Scene::AddCamera( const Shared < CameraGraph >& camera )
    {
        assert( camera && "'camera' is null." );
        Spinlocker lck( m_spinlock );
        
        auto it = std::find( m_camgraphs.begin() , m_camgraphs.end() , camera );
        if ( it == m_camgraphs.end() )
            m_camgraphs.push_back( camera );
    }
    
    ////////////////////////////////////////////////////////////
    void Scene::RemoveCamera( const Shared < Camera >& camera )
    {
        assert( camera && "'camera' is null." );
        Spinlocker lck( m_spinlock );
        
        auto it = std::find_if( m_camgraphs.begin() , m_camgraphs.end() , [camera]( const Shared < CameraGraph >& graph ){
            assert( graph && "'graph' is null." );
            return graph->GetCamera().lock() == camera ;
        });
        
        if ( it != m_camgraphs.end() )
            m_camgraphs.erase( it );
    }
    
    ////////////////////////////////////////////////////////////
    void Scene::RemoveCamera( const Shared < CameraGraph >& graph )
    {
        assert( graph && "'graph' is null." );
        Spinlocker lck( m_spinlock );
        
        auto it = std::find( m_camgraphs.begin() , m_camgraphs.end() , graph );
        if ( it != m_camgraphs.end() )
            m_camgraphs.erase( it );
    }
    
    ////////////////////////////////////////////////////////////
    void Scene::ResetCameras()
    {
        Spinlocker lck( m_spinlock );
        m_camgraphs.clear();
    }
    
    ////////////////////////////////////////////////////////////
    Weak < CameraGraph > Scene::GetCameraGraph( const Shared < Camera >& camera ) const
    {
        assert( camera && "'camera' is null." );
        Spinlocker lck( m_spinlock );
        
        auto it = std::find_if( m_camgraphs.begin() , m_camgraphs.end() , [camera]( const Shared < CameraGraph >& graph ){
            assert( graph && "'graph' is null." );
            return graph->GetCamera().lock() == camera ;
        });
    }
    
    ////////////////////////////////////////////////////////////
    Shared < RenderNode > Scene::CreateAndAddRenderNode( const glm::vec3& position ,
                                                         const Weak < Program >& program ,
                                                         const Weak < Material >& material ,
                                                         const Weak < Mesh >& mesh ,
                                                         const Weak < CameraGraph >& graph )
    {
        assert( m_scenegraph && "'m_scenegraph' is null." );
        
        decltype( m_scenegraph ) scenegraph ;
        std::atomic_store( &scenegraph , m_scenegraph );
        
        auto posnode = scenegraph -> CreatePositionNode( position );
        assert( posnode && "'posnode' is null." );
        
        auto prognode = scenegraph -> CreateProgramNode( program );
        assert( prognode && "'prognode' is null." );
        posnode -> AddChild( prognode );
        
        auto matnode = scenegraph -> CreateMaterialNode( material );
        assert( matnode );
        prognode -> AddChild( matnode );
        
        auto meshnode = scenegraph -> CreateMeshNode( mesh );
        assert( meshnode );
        matnode -> AddChild( meshnode );
        
        auto rendernode = scenegraph -> CreateRenderNode( posnode );
        assert( rendernode );
        
        auto sgraph = graph.lock();
        if ( sgraph && meshnode->Drawable() )
        sgraph->AddRenderNode( rendernode );
        
        scenegraph -> AddPositionNode( posnode );
        return rendernode ;
    }
}
