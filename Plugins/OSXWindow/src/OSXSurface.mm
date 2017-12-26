//  ========================================================================  //
//
//  File    : OSXWindow/OSXSurface.mm
//  Project : ATL/OSXWindow
//  Author  : Luk2010
//  Date    : 11/10/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#include <ATL/Root.hpp>
#include <ATL/SurfaceEvent.hpp>
#include <OSXWindow/OSXSurface.h>
#include <OSXWindow/Scaling.h>

////////////////////////////////////////////////////////////
OSXSurface::OSXSurface( SurfaceHandle handle ) : Surface( handle ) , m_closed( true )
{
    id surface = HandleConvert < id >( handle );
    
    if ( [surface isKindOfClass:[NSWindow class]] )
    {
        m_window    = [surface retain];
        m_view      = nil ;
        m_blackview = [[OSXBlackView alloc] initWithWindow:m_window WithRequester:this];
        
        if ( m_blackview == nil )
        {
            Root::Get().GetLogger().warn( "OSXBlackView not allocated." );
            return ;
        }
        
        m_closed.store( false );
    }
    
    else if ( [surface isKindOfClass:[NSView class]] )
    {
        m_window    = [[surface window] retain];
        m_view      = [surface retain];
        m_blackview = [[OSXBlackView alloc] initWithView:m_view WithRequester:this];
        
        if ( m_window == nil )
        {
            Root::Get().GetLogger().warn( "NSView controlled but not in a NSWindow." );
        }
        
        if ( m_blackview == nil )
        {
            Root::Get().GetLogger().warn( "OSXBlackView not allocated." );
            return ;
        }
        
        m_closed.store( false );
    }
    
    else
    {
        Root::Get().GetLogger().warn( "Invalid handle given (not a NSWindow nor a NSView)." );
        m_window    = nil ;
        m_view      = nil ;
        m_blackview = nil ;
    }
}

////////////////////////////////////////////////////////////
OSXSurface::OSXSurface( const VideoMode& mode , const String& title , atl::Style style ) : Surface( mode , title , style )
{
    m_window    = nil ;
    m_view      = nil ;
    m_blackview = nil ;
    
    // If we are not on the main thread, just stop here because it is not allowed.
    // Note that this limits the atl::Performer class because it just can't be used
    // here as we cannot create the NSWindow outside of the main thread.
    if ( [NSThread currentThread] != [NSThread mainThread] )
    {
        Root::Get().GetLogger().warn( "Can't create NSWindow outside of main thread." );
        return ;
    }
    
    bool fullscreen = style & SurfaceStyle::Fullscreen ;
    
    if ( fullscreen )
    {
        SetupFullscreenWindow( mode );
    }
    
    else
    {
        SetupWindow( mode , style );
    }
    
    assert( m_window && "Invalid NSWindow creation." );
    assert( m_blackview && "Invalid OSXBlackView creation." );
    
    [m_window setTitle:AtlStringToNSString(title)];
    m_closed.store( false );
}

////////////////////////////////////////////////////////////
OSXSurface::~OSXSurface()
{
    if ( m_blackview ) [m_blackview release];
    if ( m_view ) [m_view release];
    if ( m_window ) [m_window release];
}

////////////////////////////////////////////////////////////
void OSXSurface::SetupFullscreenWindow( const VideoMode& mode )
{
    VideoMode desktop = Root::Get().GetSurfacer().lock()->GetDesktopVideoMode();
    ScaleInWidthHeight( desktop , nil );
    
    NSRect windowrect = NSMakeRect( 0 , 0 , desktop.width , desktop.height );
    m_window = [[NSWindow alloc] initWithContentRect:windowrect
                                           styleMask:NSWindowStyleMaskBorderless
                                             backing:NSBackingStoreBuffered
                                               defer:NO];
    
    if ( m_window == nil )
    {
        Root::Get().GetLogger().warn( "Invalid NSWindow creation." );
        m_window    = nil ;
        m_view      = nil ;
        m_blackview = nil ;
        return ;
    }
    
    [m_window setLevel:NSMainMenuWindowLevel+1];
    [m_window setOpaque:YES];
    [m_window setHidesOnDeactivate:YES];
    [m_window setAutodisplay:YES];
    [m_window setReleasedWhenClosed:NO];
    [m_window setAcceptsMouseMovedEvents:YES];
    [m_window setIgnoresMouseEvents:NO];
    
    m_blackview = [[OSXBlackView alloc] initWithWindow:m_window WithRequester:this];
    
    if ( m_blackview == nil )
    {
        Root::Get().GetLogger().warn( "Invalid OSXBlackView creation." );
        [m_window release];
        m_window    = nil ;
        m_view      = nil ;
        m_blackview = nil ;
        return ;
    }
}

////////////////////////////////////////////////////////////
void OSXSurface::SetupWindow( const VideoMode& mode , atl::Style style )
{
    NSRect windowrect = NSMakeRect( 0 , 0 , mode.width , mode.height );
    
    // Convert ATL SurfaceStyle to NSWindowStyle.
    unsigned int windowstyle = NSWindowStyleMaskBorderless ;
    if ( style & SurfaceStyle::Titlebar )
        windowstyle |= NSWindowStyleMaskTitled | NSWindowStyleMaskMiniaturizable ;
    if ( style & SurfaceStyle::Resizable )
        windowstyle |= NSWindowStyleMaskResizable ;
    if ( style & SurfaceStyle::Closable )
        windowstyle |= NSWindowStyleMaskClosable ;
    
    m_window = [[NSWindow alloc] initWithContentRect:windowrect
                                           styleMask:windowstyle
                                             backing:NSBackingStoreBuffered
                                               defer:NO];
    
    if ( m_window == nil )
    {
        Root::Get().GetLogger().warn( "Invalid NSWindow creation." );
        m_window    = nil ;
        m_view      = nil ;
        m_blackview = nil ;
        return ;
    }
    
    m_blackview = [[OSXBlackView alloc] initWithWindow:m_window WithRequester:this];
    
    if ( m_blackview == nil )
    {
        Root::Get().GetLogger().warn( "Invalid OSXBlackView creation." );
        [m_window release];
        m_window    = nil ;
        m_view      = nil ;
        m_blackview = nil ;
        return ;
    }
    
    [m_window setAcceptsMouseMovedEvents:YES];
    [m_window setIgnoresMouseEvents:NO];
    [m_window setAutodisplay:YES];
    [m_window setReleasedWhenClosed:NO];
}

////////////////////////////////////////////////////////////
String OSXSurface::GetTitle() const
{
    if ( m_window != nil )
        return AtlStringFromNSString( [m_window title] );
    return "" ;
}

////////////////////////////////////////////////////////////
void OSXSurface::SetTitle(const String &title)
{
    if ( m_window != nil )
    {
        NSString* nstitle = AtlStringToNSString( title );
        [m_window setTitle:nstitle];
        [nstitle release];
    }
}

////////////////////////////////////////////////////////////
atl::Size OSXSurface::GetSize() const
{
    if ( m_blackview != nil )
    {
        atl::Size retvalue ;
        NSRect nsframe  = [m_blackview convertRectToBacking:[m_blackview frame]];
        retvalue.width  = nsframe.size.width ;
        retvalue.height = nsframe.size.height ;
        ScaleOutWidthHeight( retvalue , nil );
        return retvalue ;
    }
    
    return atl::Size( 0 , 0 );
}

////////////////////////////////////////////////////////////
void OSXSurface::SetSize( const atl::Size& sizenotscaled )
{
    atl::Size size = sizenotscaled ;
    ScaleInWidthHeight( size , nil );
    
    if ( m_view == nil && m_window != nil )
    {
        NSRect framerect = [m_window frame];
        framerect.size.width  = size.width ;
        framerect.size.height = size.height ;
        [m_window setFrame:framerect display:YES];
    }
    
    else if ( m_view != nil )
    {
        [m_view setFrameSize:NSMakeSize(size.width, size.height)];
    }
    
    else if ( m_blackview != nil )
    {
        [m_blackview setFrameSize:NSMakeSize(size.width, size.height)];
    }
}

////////////////////////////////////////////////////////////
void OSXSurface::Move( const atl::Position& positionnotscaled )
{
    atl::Position position = positionnotscaled ;
    ScaleInXY( position , nil );
    
    if ( m_window != nil && m_view == nil )
    {
        NSRect framerect = [m_window frame];
        framerect.origin.x = position.x ;
        framerect.origin.y = position.y ;
        [m_window setFrame:framerect display:YES];
    }
    
    else if ( m_view != nil )
    {
        [m_view setFrameOrigin:NSMakePoint(position.x, position.y)];
    }
    
    else if ( m_blackview != nil )
    {
        [m_blackview setFrameOrigin:NSMakePoint(position.x, position.y)];
    }
}

////////////////////////////////////////////////////////////
atl::Position OSXSurface::GetPosition() const
{
    if ( m_blackview != nil )
    {
        atl::Position retvalue ;
        NSRect nsframe = [m_window convertRectToScreen:[m_blackview convertRectToBacking:[m_blackview frame]]];
        retvalue.x     = nsframe.origin.x ;
        retvalue.y     = nsframe.origin.y ;
        ScaleOutXY( retvalue , nil );
        return retvalue ;
    }
    
    return atl::Position( 0 , 0 );
}

////////////////////////////////////////////////////////////
void OSXSurface::ProcessEvents() const
{
    @autoreleasepool
    {
        if ( NSApp != nil )
        {
            NSEvent* event = nil ;
            while ( (event = [NSApp nextEventMatchingMask:NSEventMaskAny
                                                untilDate:[NSDate distantPast]
                                                   inMode:NSDefaultRunLoopMode
                                                  dequeue:YES]) )
            {
                [NSApp sendEvent:event];
            }
        }
    }
}

////////////////////////////////////////////////////////////
bool OSXSurface::Closed() const
{
    return m_closed.load();
}

////////////////////////////////////////////////////////////
void OSXSurface::Close( void )
{
    if ( m_window != nil )
        [m_window close];
    
    m_closed.store( true );
}

////////////////////////////////////////////////////////////
void OSXSurface::Show( void ) const
{
    if ( m_window != nil )
    {
        [m_window makeKeyAndOrderFront:nil];
    }
}

////////////////////////////////////////////////////////////
void OSXSurface::Hide( void ) const
{
    if ( m_window != nil )
    {
        [m_window orderOut:nil];
    }
}

////////////////////////////////////////////////////////////
SurfaceHandle OSXSurface::GetSystemHandle() const
{
    if ( m_blackview != nil )
    {
        return HandleConvert( (id) m_blackview );
    }
    
    return 0 ;
}

////////////////////////////////////////////////////////////
void OSXSurface::NotifiateWindowWillClose( void )
{
    Emitter::SendAsyncEvent< SurfaceWillCloseEvent >( shared_from_this() );
    m_closed.store( true );
}

////////////////////////////////////////////////////////////
void OSXSurface::NotifiateViewDidResize( const atl::Size& newsize )
{
    Emitter::SendAsyncEvent < SurfaceResizeEvent >( newsize , shared_from_this() );
}

////////////////////////////////////////////////////////////
void OSXSurface::NotifiateWindowDidMove( const atl::Position& position )
{
    Emitter::SendAsyncEvent < SurfaceMoveEvent >( position , shared_from_this() );
}

////////////////////////////////////////////////////////////
void OSXSurface::NotifiateViewMouseEntered( const atl::Position& position )
{
    Emitter::SendAsyncEvent < SurfaceMouseEnteredEvent >( position , shared_from_this() );
}

////////////////////////////////////////////////////////////
void OSXSurface::NotifiateViewMouseExited( const atl::Position& position )
{
    Emitter::SendAsyncEvent < SurfaceMouseExitedEvent >( position , shared_from_this() );
}

////////////////////////////////////////////////////////////
void OSXSurface::NotifiateViewMouseUp( atl::MouseButton button , atl::MouseAction action , const atl::Position& position )
{
    Emitter::SendAsyncEvent < SurfaceMouseButtonEvent >( button , action , position , shared_from_this() );
}

////////////////////////////////////////////////////////////
void OSXSurface::NotifiateViewKeyDown( const String& key , const String& text , atl::Modifiers mods )
{
    Emitter::SendAsyncEvent < SurfaceKeyDownEvent >( key , text , mods , shared_from_this() );
}

////////////////////////////////////////////////////////////
void OSXSurface::NotifiateViewKeyUp( const String& key , const String& text , atl::Modifiers mods )
{
    Emitter::SendAsyncEvent < SurfaceKeyUpEvent >( key , text , mods , shared_from_this() );
}

////////////////////////////////////////////////////////////
void OSXSurface::NotifiateViewMouseMoved( float dx , float dy )
{
    Emitter::SendAsyncEvent < SurfaceMouseMovedEvent >( dx , dy , shared_from_this() );
}



