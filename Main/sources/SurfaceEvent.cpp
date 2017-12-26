//  ========================================================================  //
//
//  File    : ATL/SurfaceEvent.cpp
//  Project : atlresource
//  Author  : Luk2010
//  Date    : 13/10/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#include <ATL/SurfaceEvent.hpp>

namespace atl
{
    ////////////////////////////////////////////////////////////
    SurfaceEvent::SurfaceEvent( const Weak < Surface >& surface ) : m_surface( surface )
    {
        
    }
    
    ////////////////////////////////////////////////////////////
    SurfaceEvent::~SurfaceEvent()
    {
        
    }
    
    ////////////////////////////////////////////////////////////
    Weak < Surface > SurfaceEvent::GetSurface() const
    {
        return m_surface ;
    }
    
    ////////////////////////////////////////////////////////////
    SurfaceResizeEvent::SurfaceResizeEvent( const atl::Size& newsize , const Weak < Surface >& surface )
    : SurfaceEvent( surface ) , m_newsize( newsize )
    {
        
    }
    
    ////////////////////////////////////////////////////////////
    atl::Size SurfaceResizeEvent::GetSize() const
    {
        return m_newsize ;
    }
    
    ////////////////////////////////////////////////////////////
    SurfaceMoveEvent::SurfaceMoveEvent( const atl::Position& position , const Weak < Surface >& surface )
    : SurfaceEvent( surface ) , m_position( position )
    {
        
    }
    
    ////////////////////////////////////////////////////////////
    atl::Position SurfaceMoveEvent::GetPosition() const
    {
        return m_position ;
    }
    
    ////////////////////////////////////////////////////////////
    SurfaceMouseEnteredEvent::SurfaceMouseEnteredEvent( const atl::Position& position , const Weak < Surface >& surface )
    : SurfaceEvent( surface ) , m_position( position )
    {
        
    }
    
    ////////////////////////////////////////////////////////////
    atl::Position SurfaceMouseEnteredEvent::GetPosition() const
    {
        return m_position ;
    }
    
    ////////////////////////////////////////////////////////////
    SurfaceMouseButtonEvent::SurfaceMouseButtonEvent( MouseButton button , MouseAction action , const atl::Position& position , const Weak < Surface >& surface )
    : SurfaceEvent( surface ) , m_button( button ) , m_action( action ) , m_position( position )
    {
        
    }
    
    ////////////////////////////////////////////////////////////
    MouseButton SurfaceMouseButtonEvent::GetButton() const
    {
        return m_button ;
    }
    
    ////////////////////////////////////////////////////////////
    MouseAction SurfaceMouseButtonEvent::GetAction() const
    {
        return m_action ;
    }
    
    ////////////////////////////////////////////////////////////
    atl::Position SurfaceMouseButtonEvent::GetPosition() const
    {
        return m_position ;
    }
    
    ////////////////////////////////////////////////////////////
    SurfaceMouseMovedEvent::SurfaceMouseMovedEvent( float dx , float dy , const Weak < Surface >& surface )
    : SurfaceEvent( surface ) , m_dx( dx ) , m_dy( dy )
    {
        
    }
    
    ////////////////////////////////////////////////////////////
    float SurfaceMouseMovedEvent::GetDeltaX() const
    {
        return m_dx ;
    }
    
    ////////////////////////////////////////////////////////////
    float SurfaceMouseMovedEvent::GetDeltaY() const
    {
        return m_dy ;
    }
    
    ////////////////////////////////////////////////////////////
    SurfaceKeyDownEvent::SurfaceKeyDownEvent( const String& key , const String& text , Modifiers mods , const Weak < Surface >& surface )
    : SurfaceEvent( surface ) , m_text( text ) , m_key( key ) , m_mods( mods )
    {
        
    }
    
    ////////////////////////////////////////////////////////////
    String SurfaceKeyDownEvent::GetText() const
    {
        return m_text ;
    }
    
    ////////////////////////////////////////////////////////////
    String SurfaceKeyDownEvent::GetKey() const
    {
        return m_key ;
    }
    
    ////////////////////////////////////////////////////////////
    Modifiers SurfaceKeyDownEvent::GetModifiers() const
    {
        return m_mods ;
    }
}
