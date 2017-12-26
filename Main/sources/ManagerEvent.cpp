//  ========================================================================  //
//
//  File    : ATL/ManagerEvent.cpp
//  Project : atlresource
//  Author  : Luk2010
//  Date    : 14/11/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#include <ATL/ManagerEvent.hpp>

namespace atl
{
    ////////////////////////////////////////////////////////////
    ManagerCreateEvent::ManagerCreateEvent( const ResourceId& id , const String& file )
    : m_id( id ) , m_file( file )
    {
        
    }
    
    ////////////////////////////////////////////////////////////
    ResourceId ManagerCreateEvent::GetId() const
    {
        return m_id.load();
    }
    
    ////////////////////////////////////////////////////////////
    const String ManagerCreateEvent::GetFile() const
    {
        Spinlocker lck( m_spinlock );
        return m_file ;
    }
    
    ////////////////////////////////////////////////////////////
    ManagerReleaseEvent::ManagerReleaseEvent( const ResourceId& id )
    : m_id( id )
    {
        
    }
    
    ////////////////////////////////////////////////////////////
    ResourceId ManagerReleaseEvent::GetId() const
    {
        return m_id.load();
    }
}
