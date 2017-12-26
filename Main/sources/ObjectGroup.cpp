//  ========================================================================  //
//
//  File    : ATL/ObjectGroup.cpp
//  Project : atlresource
//  Author  : Luk2010
//  Date    : 20/10/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#include <ATL/ObjectGroup.hpp>
#include <ATL/RenderTarget.hpp>

namespace atl
{
    ////////////////////////////////////////////////////////////
    IDGenerator < ObjectGroupId > ObjectGroup::s_generator ;
    
    ////////////////////////////////////////////////////////////
    ObjectGroup::ObjectGroup() : m_id( s_generator.New() )
    {
        
    }
    
    ////////////////////////////////////////////////////////////
    ObjectGroup::~ObjectGroup()
    {
        
    }
    
    ////////////////////////////////////////////////////////////
    ObjectGroupId ObjectGroup::GetId() const
    {
        return m_id.load();
    }
    
    ////////////////////////////////////////////////////////////
    Weak < ObjectGroup > ObjectGroup::GetParent() const
    {
        return m_parent ;
    }
    
    ////////////////////////////////////////////////////////////
    void ObjectGroup::SetParent( const Weak < ObjectGroup >& parent )
    {
        if ( !m_parent.expired() )
        {
            auto oldparent = m_parent.lock();
            
            if ( oldparent == parent.lock() )
                return ;
            
            oldparent->RemoveSubGroup( shared_from_this() );
        }
        
        m_parent = parent ;
        
        if ( !m_parent.expired() )
        {
            m_parent.lock()->AddSubGroup( shared_from_this() );
        }
    }
    
    ////////////////////////////////////////////////////////////
    WeakVector < ObjectGroup > ObjectGroup::GetSubGroups() const
    {
        MutexLocker lck( m_mutex );
        WeakVector < ObjectGroup > retvalue ;
        retvalue.insert( retvalue.begin() , m_subgroups.begin() , m_subgroups.end() );
        return retvalue ;
    }
    
    ////////////////////////////////////////////////////////////
    Weak < ObjectGroup > ObjectGroup::FindSubGroup( const ObjectGroupId& id ) const
    {
        MutexLocker lck( m_mutex );
        
        for ( auto& group : m_subgroups )
        {
            if ( group && group->GetId() == id )
                return group ;
        }
        
        return Weak < ObjectGroup >();
    }
    
    ////////////////////////////////////////////////////////////
    void ObjectGroup::RemoveSubGroup( const Weak < ObjectGroup >& group )
    {
        if ( group.expired() )
            return ;
        
        auto sgroup = group.lock();
        bool isdeleted = false ;
        
        {
            MutexLocker lck( m_mutex );
            auto it = std::find( m_subgroups.begin() , m_subgroups.end() , sgroup );
            
            if ( it != m_subgroups.end() )
            {
                m_subgroups.erase( it );
                isdeleted = true ;
            }
        }
        
        if ( isdeleted )
        {
            sgroup->SetParent( Weak < ObjectGroup >() );
        }
    }
    
    ////////////////////////////////////////////////////////////
    void ObjectGroup::AddSubGroup( const Shared < ObjectGroup >& group )
    {
        if ( !FindSubGroup( group->GetId() ).expired() )
            return ;
        
        {
            MutexLocker lck( m_mutex );
            m_subgroups.push_back( group );
        }
        
        group->SetParent( shared_from_this() );
    }
    
    ////////////////////////////////////////////////////////////
    Weak < ObjectGroup > ObjectGroup::CreateSubGroup()
    {
        auto group = std::make_shared < ObjectGroup >();
        group->SetParent( shared_from_this() );
        return group ;
    }
    
    ////////////////////////////////////////////////////////////
    void ObjectGroup::RemoveAllSubGroups()
    {
        m_mutex.lock();
        auto groups = m_subgroups ;
        m_subgroups.clear();
        m_mutex.unlock();
        
        for ( auto& group : groups )
        {
            group->SetParent( Weak < ObjectGroup >() );
        }
    }
    
    ////////////////////////////////////////////////////////////
    void ObjectGroup::AddObject( const Shared < Object >& object )
    {
        if ( !object )
            return ;
        
        if ( !FindObject( object->GetId() ).expired() )
            return ;
        
        MutexLocker lck( m_mutex );
        m_objects.push_back( object );
        object->SetGroup( shared_from_this() );
    }
    
    ////////////////////////////////////////////////////////////
    Weak < Object > ObjectGroup::FindObject( const ObjectId& id ) const
    {
        if ( id == 0 )
            return Weak < Object >();
        
        MutexLocker lck( m_mutex );
        
        for ( auto& object : m_objects )
        {
            if ( object->GetId() == id )
                return object ;
        }
        
        return Weak < Object >();
    }
    
    ////////////////////////////////////////////////////////////
    void ObjectGroup::RemoveObject( const Weak < Object >& object )
    {
        if ( object.expired() )
            return ;
        
        auto sobject = object.lock();
        MutexLocker lck( m_mutex );
        auto it = std::find( m_objects.begin() , m_objects.end() , sobject );
        
        if ( it != m_objects.end() )
        {
            m_objects.erase( it );
            sobject->SetGroup( Weak < ObjectGroup >() );
        }
    }
    
    ////////////////////////////////////////////////////////////
    void ObjectGroup::RemoveAllObjects()
    {
        MutexLocker lck( m_mutex );
        
        for ( auto& object : m_objects )
        {
            object->SetGroup( Weak < ObjectGroup >() );
        }
        
        m_objects.clear();
    }
    
    ////////////////////////////////////////////////////////////
    void ObjectGroup::Reset()
    {
        RemoveAllSubGroups();
        RemoveAllObjects();
        SetParent( Weak < ObjectGroup >() );
    }
    
    ////////////////////////////////////////////////////////////
    void ObjectGroup::Update( RenderTarget& target , bool lockupdate )
    {
        m_mutex.lock();
        auto groups = m_subgroups ;
        auto objects = m_objects ;
        m_mutex.unlock();
        
        for ( auto& object : objects )
        {
            if ( !object )
                continue ;
            
            if ( lockupdate )
            target.Begin();
            
            object->Update( target );
            
            if ( lockupdate )
            target.End();
        }
        
        for ( auto& group : groups )
        {
            if ( !group )
                continue ;
            
            group->Update( target , lockupdate );
        }
    }
}
