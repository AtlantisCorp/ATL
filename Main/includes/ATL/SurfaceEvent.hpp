//  ========================================================================  //
//
//  File    : ATL/SurfaceEvent.hpp
//  Project : atlresource
//  Author  : Luk2010
//  Date    : 13/10/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#ifndef SurfaceEvent_hpp
#define SurfaceEvent_hpp

#include <ATL/Surface.hpp>
#include <ATL/Mouse.hpp>
#include <ATL/Modifier.hpp>

namespace atl
{
    ////////////////////////////////////////////////////////////
    /// \brief A Generic Event emitted by a Surface object.
    ///
    ////////////////////////////////////////////////////////////
    class SurfaceEvent : public Event
    {
        Weak < Surface > m_surface ;
        
    public:
        
        ////////////////////////////////////////////////////////////
        SurfaceEvent( const Weak < Surface >& surface );
        
        ////////////////////////////////////////////////////////////
        virtual ~SurfaceEvent();
        
        ////////////////////////////////////////////////////////////
        Weak < Surface > GetSurface() const ;
    };
    
    ////////////////////////////////////////////////////////////
    /// \brief Emitted when the Surface will close.
    ///
    ////////////////////////////////////////////////////////////
    class SurfaceWillCloseEvent : public SurfaceEvent
    {
    public:
        using SurfaceEvent::SurfaceEvent ;
    };
    
    ////////////////////////////////////////////////////////////
    /// \brief Emitted when the Surface did resize.
    ///
    ////////////////////////////////////////////////////////////
    class SurfaceResizeEvent : public SurfaceEvent
    {
        atl::Size m_newsize ;
        
    public:
        
        ////////////////////////////////////////////////////////////
        SurfaceResizeEvent( const atl::Size& newsize , const Weak < Surface >& surface );
        
        ////////////////////////////////////////////////////////////
        atl::Size GetSize() const ;
    };
    
    ////////////////////////////////////////////////////////////
    /// \brief Emitted when the Surface did move.
    ///
    ////////////////////////////////////////////////////////////
    class SurfaceMoveEvent : public SurfaceEvent
    {
        atl::Position m_position ;
        
    public:
        
        ////////////////////////////////////////////////////////////
        SurfaceMoveEvent( const atl::Position& position , const Weak < Surface >& surface );
        
        ////////////////////////////////////////////////////////////
        atl::Position GetPosition() const ;
    };
    
    ////////////////////////////////////////////////////////////
    /// \brief Emitted when a Mouse enter the surface.
    ///
    ////////////////////////////////////////////////////////////
    class SurfaceMouseEnteredEvent : public SurfaceEvent
    {
        atl::Position m_position ;
        
    public:
        
        ////////////////////////////////////////////////////////////
        SurfaceMouseEnteredEvent( const atl::Position& position , const Weak < Surface >& surface );
        
        ////////////////////////////////////////////////////////////
        atl::Position GetPosition() const ;
    };
    
    ////////////////////////////////////////////////////////////
    /// \brief Emitted when a Mouse exits the surface.
    ///
    ////////////////////////////////////////////////////////////
    class SurfaceMouseExitedEvent : public SurfaceMouseEnteredEvent
    {
    public:
        using SurfaceMouseEnteredEvent::SurfaceMouseEnteredEvent ;
    };
    
    ////////////////////////////////////////////////////////////
    /// \brief Emitted when a MouseButton is pressed or released.
    ///
    ////////////////////////////////////////////////////////////
    class SurfaceMouseButtonEvent : public SurfaceEvent
    {
        MouseButton   m_button ;   ///< Button used (Left, Right, Wheel).
        MouseAction   m_action ;   ///< Action done (Pressed, Released).
        atl::Position m_position ; ///< Event's position when emitted.
        
    public:
        
        ////////////////////////////////////////////////////////////
        SurfaceMouseButtonEvent( MouseButton button , MouseAction action , const atl::Position& position , const Weak < Surface >& surface );
        
        ////////////////////////////////////////////////////////////
        MouseButton GetButton() const ;
        
        ////////////////////////////////////////////////////////////
        MouseAction GetAction() const ;
        
        ////////////////////////////////////////////////////////////
        atl::Position GetPosition() const ;
    };
    
    ////////////////////////////////////////////////////////////
    /// \brief Emitted when a mouse is moved.
    ///
    ////////////////////////////////////////////////////////////
    class SurfaceMouseMovedEvent : public SurfaceEvent
    {
        float m_dx ; ///< Delta X with last known position.
        float m_dy ; ///< Delta Y with last known position.
        
    public:
        
        ////////////////////////////////////////////////////////////
        SurfaceMouseMovedEvent( float dx , float dy , const Weak < Surface >& surface );
        
        ////////////////////////////////////////////////////////////
        float GetDeltaX() const ;
        
        ////////////////////////////////////////////////////////////
        float GetDeltaY() const ;
    };
    
    ////////////////////////////////////////////////////////////
    /// \brief Emitted when a key is pressed in a Surface.
    ///
    ////////////////////////////////////////////////////////////
    class SurfaceKeyDownEvent : public SurfaceEvent
    {
        String    m_text ; ///< The UTF8 character computed with all modifiers.
        String    m_key ;  ///< UTF8 character computed with only the Modifier::Shift mod or none.
        Modifiers m_mods ; ///< Modifiers currently pressed when the key was pressed.
        
    public:
        
        ////////////////////////////////////////////////////////////
        SurfaceKeyDownEvent( const String& key , const String& text , Modifiers mods , const Weak < Surface >& surface );
        
        ////////////////////////////////////////////////////////////
        String GetText() const ;
        
        ////////////////////////////////////////////////////////////
        String GetKey() const ;
        
        ////////////////////////////////////////////////////////////
        Modifiers GetModifiers() const ;
    };
    
    ////////////////////////////////////////////////////////////
    /// \brief Emitted when a key is released in a Surface.
    ///
    ////////////////////////////////////////////////////////////
    class SurfaceKeyUpEvent : public SurfaceKeyDownEvent
    {
    public:
        using SurfaceKeyDownEvent::SurfaceKeyDownEvent ;
    };
    
    ////////////////////////////////////////////////////////////
    /// \brief Emitted by a parent 'RenderWindow' when 'Display'
    /// is called for the first time.
    ///
    /// \note This Event is reported as a Surface event because the
    /// Surface is displayed for the first time to the screen and its
    /// events have been processed for the first time.
    ///
    ////////////////////////////////////////////////////////////
    class SurfaceFirstDisplayedEvent : public SurfaceEvent
    {
    public:
        using SurfaceEvent::SurfaceEvent ;
    };
}

#endif /* SurfaceEvent_hpp */
