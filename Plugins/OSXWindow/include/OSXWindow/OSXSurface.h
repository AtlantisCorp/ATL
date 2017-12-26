//  ========================================================================  //
//
//  File    : OSXWindow/OSXSurface.h
//  Project : ATL/OSXWindow
//  Author  : Luk2010
//  Date    : 10/10/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#ifndef OSXSurface_h
#define OSXSurface_h

#include <ATL/Surface.hpp>
#include <ATL/Mouse.hpp>
#include <ATL/Modifier.hpp>
using namespace atl ;

#if defined(__OBJC__)

#include <Cocoa/Cocoa.h>
#include <OSXWindow/OSXBlackView.h>

typedef NSWindow*        OSXWindowRef ;
typedef NSView*          OSXViewRef ;
typedef OSXBlackView*    OSXBlackViewRef ;

#else

typedef void* OSXWindowRef ;
typedef void* OSXViewRef ;
typedef void* OSXBlackViewRef ;

#endif // __OBJC__

////////////////////////////////////////////////////////////
/// \brief An macOS Surface manages a NSWindow object and its
/// events.
///
/// It does not manage the OpenGLView that might be added by a
/// Context. It is to the Context to manage this view. The Context
/// can set the view by using 'GetSystemHandle()' to retrieve the
/// Surface handle.
///
/// A Surface can be created from a NSWindow or a NSView object.
/// By default, it creates a NSWindow when created from separate
/// args. In all case, the Context have to add a subview to the
/// NSView or NSWindow handle to be displayed.
///
/// In detail, the OSXSurface always create a OSXBlackView and this
/// is this subview which handles events. This way, the OSXBlackView
/// can be inserted as the content view of a given NSWindow, or a a subview
/// if it is given a NSView.
///
/// Events are treated concerning the NSView or NSWindow controlled,
/// this meaning the glview child will be controlled by this Surface.
///
////////////////////////////////////////////////////////////
class OSXSurface : public Surface
{
    OSXWindowRef    m_window ;    ///< NSWindow associated to the surface. This parameter can be 'nil' if the NSView given
                                  ///  to initialize the Surface is not attached to a NSWindow. (This behaviour is heavily not
                                  ///  recommended)
    OSXViewRef      m_view ;      ///< NSView controlled by this surface if initialized with a view. If not initialized
                                  ///  (or with a NSWindow), this parameter remains 'nil'.
    OSXBlackViewRef m_blackview ; ///< ATL view to handle NSView events. A Context can always add a subview to this black view
                                  ///  to add a native NSOpenGLView or any view that suits its behaviour.
    Atomic < bool > m_closed ;    ///< False when the OSXSurface is created (on success, otherwise true). When the surface is closed
                                  ///  (using 'Close()' or when 'OSXBlackView' detect 'windowWillClose'), this boolean is set to
                                  ///  false. However, the Window will close only when the surface is destroyed. This can be done immediatly
                                  ///  by using 'Surfacer::RemoveSurface()'.
    
public:
    
    ////////////////////////////////////////////////////////////
    /// \brief Creates a new Surface by controlling the handle.
    ///
    /// \param handle It can be a NSView or a NSWindow. When it
    /// is a NSWindow, a OSXBlackView is created as the main view
    /// for this window. When it is a NSView, it will be used as
    /// for main view.
    ///
    ////////////////////////////////////////////////////////////
    OSXSurface( SurfaceHandle handle );
    
    ////////////////////////////////////////////////////////////
    OSXSurface( const VideoMode& mode , const String& title , atl::Style style );
    
    ////////////////////////////////////////////////////////////
    virtual ~OSXSurface();
    
    ////////////////////////////////////////////////////////////
    /// \brief Get the surface's title.
    ///
    ////////////////////////////////////////////////////////////
    virtual String GetTitle() const ;
    
    ////////////////////////////////////////////////////////////
    /// \brief Changes the surface title, if applicable.
    ///
    ////////////////////////////////////////////////////////////
    virtual void SetTitle( const String& title );
    
    ////////////////////////////////////////////////////////////
    /// \brief Get the surface's size, in pixels.
    ///
    ////////////////////////////////////////////////////////////
    virtual atl::Size GetSize() const ;
    
    ////////////////////////////////////////////////////////////
    /// \brief Changes the surface's size, in pixels.
    ///
    /// \param size New size to apply. Notes that if the blackview
    /// is the content view of its window, this function tries to
    /// resize the actual window parent. If the blackview is actually
    /// constructed inside another view (m_view not nil), it is the
    /// view which is actually resized, and not the NSWindow.
    ///
    ////////////////////////////////////////////////////////////
    virtual void SetSize( const atl::Size& size );
    
    ////////////////////////////////////////////////////////////
    /// \brief Moves the surface, if applicable, in pixels.
    ///
    /// \param pos New position, in pixels.
    ///
    /// \note 'applicable' here means that if the blackview is in
    /// a NSWindow, the window will be moved. If the blackview is
    /// in a NSView, this view will be moved and not the NSWindow.
    ///
    ////////////////////////////////////////////////////////////
    virtual void Move( const Position& pos );
    
    ////////////////////////////////////////////////////////////
    /// \brief Get the surface position's relative to screen, in
    /// pixels.
    ///
    ////////////////////////////////////////////////////////////
    virtual Position GetPosition() const ;
    
    ////////////////////////////////////////////////////////////
    /// \brief Process events and send them to registered listeners.
    ///
    ////////////////////////////////////////////////////////////
    virtual void ProcessEvents( void ) const ;

    ////////////////////////////////////////////////////////////
    /// \brief Return 'true' if the Surface is closed.
    ///
    ////////////////////////////////////////////////////////////
    virtual bool Closed( void ) const ;
    
    ////////////////////////////////////////////////////////////
    /// \brief Close the Surface.
    ///
    ////////////////////////////////////////////////////////////
    virtual void Close( void );
    
    ////////////////////////////////////////////////////////////
    /// \brief Show the Surface.
    ///
    /// Must be called after creating the Surface using the Surfacer,
    /// because default behaviour does not show the surface right
    /// after creation.
    ///
    ////////////////////////////////////////////////////////////
    virtual void Show( void ) const ;
    
    ////////////////////////////////////////////////////////////
    /// \brief Hide the Surface.
    ///
    ////////////////////////////////////////////////////////////
    virtual void Hide( void ) const ;
    
    ////////////////////////////////////////////////////////////
    /// \brief Returns the black view.
    ///
    ////////////////////////////////////////////////////////////
    virtual SurfaceHandle GetSystemHandle() const ;
    
    ////////////////////////////////////////////////////////////
    /// \brief Used by OSXBlackView to notifiate the NSWindow will
    /// close.
    ///
    ////////////////////////////////////////////////////////////
    virtual void NotifiateWindowWillClose( void );
    
    ////////////////////////////////////////////////////////////
    /// \brief Used by OSXBlackView to notifiate the NSView did
    /// resize.
    ///
    ////////////////////////////////////////////////////////////
    virtual void NotifiateViewDidResize( const atl::Size& newsize );
    
    ////////////////////////////////////////////////////////////
    /// \brief Used by OSXBlackView to notifiate the NSWindow did
    /// move.
    ///
    ////////////////////////////////////////////////////////////
    virtual void NotifiateWindowDidMove( const atl::Position& position );
    
    ////////////////////////////////////////////////////////////
    /// \brief Used by OSXBlackView to notifiate NSCursor did enter
    /// the NSTrackingArea operated by the NSView.
    ///
    ////////////////////////////////////////////////////////////
    virtual void NotifiateViewMouseEntered( const atl::Position& position );
    
    ////////////////////////////////////////////////////////////
    /// \brief Used by OSXBlackView to notifiate NSCursor did enter
    /// the NSTrackingArea operated by the NSView.
    ///
    ////////////////////////////////////////////////////////////
    virtual void NotifiateViewMouseExited( const atl::Position& position );
    
    ////////////////////////////////////////////////////////////
    /// \brief Used by OSXBlackView to notifiate the mouse left button
    /// is up.
    ///
    ////////////////////////////////////////////////////////////
    virtual void NotifiateViewMouseUp( atl::MouseButton button , atl::MouseAction action , const atl::Position& position );
    
    ////////////////////////////////////////////////////////////
    /// \brief Used by OSXBlackView to notifiate a key-down event
    /// has been treated.
    ///
    ////////////////////////////////////////////////////////////
    virtual void NotifiateViewKeyDown( const String& key , const String& text , atl::Modifiers mods );
    
    ////////////////////////////////////////////////////////////
    /// \brief Used by OSXBlackView to notifiate a key-up event.
    ///
    ////////////////////////////////////////////////////////////
    virtual void NotifiateViewKeyUp( const String& key , const String& text , atl::Modifiers mods );
    
    ////////////////////////////////////////////////////////////
    /// \brief Used by OSXBlackView to notifiate mouse moved.
    ///
    ////////////////////////////////////////////////////////////
    virtual void NotifiateViewMouseMoved( float dx , float dy );
    
private:
    
    ////////////////////////////////////////////////////////////
    /// \brief Setup a fullscreen window with given mode.
    ///
    ////////////////////////////////////////////////////////////
    void SetupFullscreenWindow( const VideoMode& mode );
    
    ////////////////////////////////////////////////////////////
    /// \brief Setup a normal Window with given mode.
    ///
    ////////////////////////////////////////////////////////////
    void SetupWindow( const VideoMode& mode , atl::Style style );
};

#endif /* OSXSurface_h */
