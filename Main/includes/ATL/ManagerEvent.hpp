//  ========================================================================  //
//
//  File    : ATL/ManagerEvent.hpp
//  Project : atlresource
//  Author  : Luk2010
//  Date    : 14/11/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#ifndef ManagerEvent_hpp
#define ManagerEvent_hpp

#include <ATL/Listener.hpp>
#include <ATL/Resource.hpp>

namespace atl
{
    ////////////////////////////////////////////////////////////
    class ManagerCreateEvent : public Event
    {
        ////////////////////////////////////////////////////////////
        Atomic < ResourceId > m_id ;       ///< Resource's created ID.
        String                m_file ;     ///< Resource's created file, if created from a file.
        mutable Spinlock      m_spinlock ; ///< Access to file.
        
    public:
        
        ////////////////////////////////////////////////////////////
        ManagerCreateEvent( const ResourceId& id , const String& m_file = String() );
        
        ////////////////////////////////////////////////////////////
        ResourceId GetId() const ;
        
        ////////////////////////////////////////////////////////////
        const String GetFile() const ;
    };
    
    ////////////////////////////////////////////////////////////
    class ManagerReleaseEvent : public Event
    {
        ////////////////////////////////////////////////////////////
        Atomic < ResourceId > m_id ; ///< Resource's created ID.
        
    public:
        
        ////////////////////////////////////////////////////////////
        ManagerReleaseEvent( const ResourceId& id );
        
        ////////////////////////////////////////////////////////////
        ResourceId GetId() const ;
    };
}

#endif /* ManagerEvent_hpp */
