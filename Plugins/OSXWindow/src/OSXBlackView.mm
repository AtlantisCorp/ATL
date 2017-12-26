//  ========================================================================  //
//
//  File    : OSXWindow/OSXBlackView.mm
//  Project : ATL/OSXWindow
//  Author  : Luk2010
//  Date    : 12/10/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#include <ATL/Mouse.hpp>
#include <ATL/Modifier.hpp>
#include <ATL/Key.hpp>

#include <OSXWindow/OSXBlackView.h>
#include <OSXWindow/OSXSurface.h>
#include <OSXWindow/Scaling.h>
#include <OSXWindow/Unicode.h>

@implementation OSXBlackView

////////////////////////////////////////////////////////////
- (id) initWithWindow:(NSWindow*)window WithRequester:(OSXSurface*)surface
{
    if ( self = [super initWithFrame:[window frame]] )
    {
        m_window    = window ;
        m_view      = nil ;
        m_requester = surface ;
        m_trackarea = nil ;
        m_deadkey   = 0 ;
        m_cursorpos = NSMakePoint( 0 , 0 );
        m_cursorin  = NO ;
        
        [m_window setContentView:self];
        [m_window makeFirstResponder:self];
        [self initTrackingArea];
    }
    
    return self ;
}

////////////////////////////////////////////////////////////
- (id) initWithView:(NSView *)view WithRequester:(OSXSurface *)surface
{
    if ( self = [super initWithFrame:[view bounds]] )
    {
        m_window    = nil ;
        m_view      = view ;
        m_requester = surface ;
        m_trackarea = nil ;
        m_deadkey   = 0 ;
        m_cursorpos = NSMakePoint( 0 , 0 );
        m_cursorin  = NO ;
        
        [m_view addSubview:self];
        [m_view setAutoresizesSubviews:YES];
        [self setAutoresizingMask:NSViewWidthSizable|NSViewHeightSizable];
        [self initTrackingArea];
    }
    
    return self ;
}

////////////////////////////////////////////////////////////
- (void) windowWillClose:(NSNotification*)notification
{
    assert( m_requester && "Event received but OSXSurface is invalid." );
    m_requester->NotifiateWindowWillClose();
}

////////////////////////////////////////////////////////////
- (void) windowDidMove:(NSNotification*)notification
{
    assert( m_requester && "Null requester invoked." );
    
    if ( m_window != nil && !m_requester->Closed() )
    {
        NSRect nsframe = [m_window frame];
        atl::Position position ;
        position.x = nsframe.origin.x ;
        position.y = nsframe.origin.y ;
        ScaleOutXY( position , nil );
        
        m_requester->NotifiateWindowDidMove( position );
    }
}

////////////////////////////////////////////////////////////
- (void) initTrackingArea
{
    assert( m_trackarea == nil && "NSTrackingArea already initialized but 'OSXBlackView::initTrackingArea' was (re)called." );
    m_trackarea = [[NSTrackingArea alloc] initWithRect:[self frame]
                                               options:(NSTrackingMouseEnteredAndExited | NSTrackingMouseMoved | NSTrackingActiveInKeyWindow)
                                                 owner:self
                                              userInfo:nil];
    assert( m_trackarea != nil && "NSTrackingArea is 'nil' (Allocation error)." );
    [self addTrackingArea:m_trackarea];
}

////////////////////////////////////////////////////////////
- (void) updateTrackingAreas
{
    if ( m_trackarea != nil )
    {
        [self removeTrackingArea:m_trackarea];
        [m_trackarea release];
        m_trackarea = nil ;
    }
    
    [self initTrackingArea];
}

////////////////////////////////////////////////////////////
- (void) drawRect:(NSRect)dirtyRect
{
    [[NSColor blackColor] setFill];
    NSRectFill( dirtyRect );
}

////////////////////////////////////////////////////////////
- (BOOL) acceptsFirstResponder
{
    return YES ;
}

////////////////////////////////////////////////////////////
- (void) mouseDown:(NSEvent *)event
{
    NSPoint mouseposition = [self convertPoint:[event locationInWindow] fromView:nil];
    ScaleOutXY(mouseposition, nil);
    
    atl::MouseButton button = atl::MouseButton::Left ;
    atl::MouseAction action = atl::MouseAction::Pressed ;
    
    assert( m_requester && "Requester is 'nil'." );
    m_requester->NotifiateViewMouseUp( button , action , atl::Position( mouseposition.x , mouseposition.y ) );
}

////////////////////////////////////////////////////////////
- (void) mouseUp:(NSEvent *)event
{
    NSPoint mouseposition = [self convertPoint:[event locationInWindow] fromView:nil];
    ScaleOutXY(mouseposition, nil);
    
    atl::MouseButton button = atl::MouseButton::Left ;
    atl::MouseAction action = atl::MouseAction::Released ;
    
    assert( m_requester && "Requester is 'nil'." );
    m_requester->NotifiateViewMouseUp( button , action , atl::Position( mouseposition.x , mouseposition.y ) );
}

////////////////////////////////////////////////////////////
- (void) mouseMoved:(NSEvent *)event
{
    if ( !m_cursorin )
        return ;
    
    if ( m_cursorpos.x == 0 && m_cursorpos.y == 0 )
    {
        m_cursorpos = [self convertPoint:[event locationInWindow] fromView:nil];
    }
    
    else
    {
        NSPoint pt = [self convertPoint:[event locationInWindow] fromView:nil];
        CGFloat dx = pt.x - m_cursorpos.x ;
        CGFloat dy = pt.y - m_cursorpos.y ;
        
        if ( !(dx == 0.0f && dy == 0.0f) )
        {
            assert( m_requester && "Requester is 'nil'." );
            m_requester->NotifiateViewMouseMoved( dx , dy );
            m_cursorpos = pt ;
        }
    }
}

////////////////////////////////////////////////////////////
- (void) rightMouseDown:(NSEvent*)event
{
    NSPoint mouseposition = [self convertPoint:[event locationInWindow] fromView:nil];
    ScaleOutXY(mouseposition, nil);
    
    atl::MouseButton button = atl::MouseButton::Right ;
    atl::MouseAction action = atl::MouseAction::Pressed ;
    
    assert( m_requester && "Requester is 'nil'." );
    m_requester->NotifiateViewMouseUp( button , action , atl::Position( mouseposition.x , mouseposition.y ) );
}

////////////////////////////////////////////////////////////
- (void) rightMouseUp:(NSEvent*)event
{
    NSPoint mouseposition = [self convertPoint:[event locationInWindow] fromView:nil];
    ScaleOutXY(mouseposition, nil);
    
    atl::MouseButton button = atl::MouseButton::Right ;
    atl::MouseAction action = atl::MouseAction::Released ;
    
    assert( m_requester && "Requester is 'nil'." );
    m_requester->NotifiateViewMouseUp( button , action , atl::Position( mouseposition.x , mouseposition.y ) );
}

////////////////////////////////////////////////////////////
- (void) mouseEntered:(NSEvent *)event
{
    m_cursorin = YES ;
    NSPoint mouseposition = [self convertPoint:[event locationInWindow] fromView:nil];
    ScaleOutXY(mouseposition, nil);
    
    assert( m_requester && "Requester is 'nil'." );
    m_requester->NotifiateViewMouseEntered( atl::Position( mouseposition.x , mouseposition.y ) );
}

////////////////////////////////////////////////////////////
- (void) mouseExited:(NSEvent *)event
{
    m_cursorin = NO ;
    NSPoint mouseposition = [self convertPoint:[event locationInWindow] fromView:nil];
    ScaleOutXY(mouseposition, nil);
    
    assert( m_requester && "Requester is 'nil'." );
    m_requester->NotifiateViewMouseExited( atl::Position( mouseposition.x , mouseposition.y ) );
}

////////////////////////////////////////////////////////////
- (void) viewWillMoveToWindow:(NSWindow *)newWindow
{
    if ( newWindow == m_window )
    {
        [[NSNotificationCenter defaultCenter] addObserver:self
                                                 selector:@selector(windowWillClose:)
                                                     name:NSWindowWillCloseNotification
                                                   object:m_window];
        
        [[NSNotificationCenter defaultCenter] addObserver:self
                                                 selector:@selector(windowDidMove:)
                                                     name:NSWindowDidMoveNotification
                                                   object:m_window];
    }
    
    else
    {
        [[NSNotificationCenter defaultCenter] removeObserver:self];
    }
}

////////////////////////////////////////////////////////////
- (void) viewDidEndLiveResize
{
    [super viewDidEndLiveResize];
    
    atl::Size newsize ;
    NSRect newrect = [self frame];
    newsize.width  = newrect.size.width ;
    newsize.height = newrect.size.height ;
    ScaleOutWidthHeight( newsize , nil );
    
    assert( m_requester && "Invalid requester invoked." );
    m_requester->NotifiateViewDidResize( newsize );
}

////////////////////////////////////////////////////////////
- (void) keyDown:(NSEvent *)event
{
    NSString* str  = translateInputForKeyDown(event, &m_deadkey);
    NSString* str2 = [event charactersIgnoringModifiers];
    
    // Principle of atl::KeyEvent
    // A KeyEvent is emitted when a UnicodeCharacter is treated by the surface.
    // As this character might be more than one char long, a String is always used
    // as the key involved.
    // Always: the keyevent represents the unicode character computed without modifiers,
    // excepted the shift (and caps-lock) modifier. When a user press a key, it is expected to
    // give the typed character without the modifiers in a game experience, but also a computed
    // unicode character in a text editing experience. So we have a 'text' field represeting the
    // locale key interpretation with modifiers, and the 'key' field that represents the keyboard
    // key interpretation of the system without modifiers. If a game wants the user to press 'S',
    // he will have to press 'Shift+'s''. This can be useful for walking/running differencies. Other
    // unicodes commonly-used characters (as 'tab' or other) are described in atl::Key ;
    // Example: if ( key == Key::Tab ) // do something.
    // OSX: When a key is a 'deadkey' (no text can be outputted), it will be stored and on the next
    // keyDown event it will be used to translate accordingly the key event.
    // When a special key is pressed (like Key::Up or Key::Down or event Key::Escape), we directly translate
    // this key to a key pressed event with modifiers. This special key is not translatable to text and therefore,
    // the resulting 'text' will be an empty String. 
    
    // String text = str ? AtlStringFromNSString( str ) : "" ;
    // String key  = AtlStringFromNSString( str2 );
    
    String key  = AtlDetectKeyFromNSString( str2 );
    String text = "" ;
    
    if ( !atl::Key::IsSpecialKey( key ) && !atl::Key::IsControlKey( key ) && str != nil )
    {
        text = AtlStringFromNSString( str );
    }
    
    Modifiers mods = Modifier::None ;
    if ( [event modifierFlags] & NSEventModifierFlagCapsLock )
        mods |= Modifier::Capslock ;
    else if ( [event modifierFlags] & NSEventModifierFlagHelp )
        mods |= Modifier::Help ;
    else if ( [event modifierFlags] & NSEventModifierFlagShift )
        mods |= Modifier::Shift ;
    else if ( [event modifierFlags] & NSEventModifierFlagOption )
        mods |= Modifier::Option ;
    else if ( [event modifierFlags] & NSEventModifierFlagCommand )
        mods |= Modifier::Command ;
    else if ( [event modifierFlags] & NSEventModifierFlagControl )
        mods |= Modifier::Control ;
    else if ( [event modifierFlags] & NSEventModifierFlagFunction )
        mods |= Modifier::Function ;
    else if ( [event modifierFlags] & NSEventModifierFlagNumericPad )
        mods |= Modifier::NumPad ;
    else if ( [event modifierFlags] & NSEventModifierFlagDeviceIndependentFlagsMask )
        mods |= Modifier::DeviceIndependent ;
    
    assert( m_requester && "Requester is 'nil'." );
    m_requester->NotifiateViewKeyDown( key , text , mods );
}

////////////////////////////////////////////////////////////
- (void) keyUp:(NSEvent*)event
{
    NSString* str  = translateInputForKeyDown(event, &m_deadkey);
    NSString* str2 = [event charactersIgnoringModifiers];
    
    String key  = AtlDetectKeyFromNSString( str2 );
    String text = "" ;
    
    if ( !atl::Key::IsSpecialKey( key ) && !atl::Key::IsControlKey( key ) && str != nil )
    {
        text = AtlStringFromNSString( str );
    }
    
    Modifiers mods = Modifier::None ;
    if ( [event modifierFlags] & NSEventModifierFlagCapsLock )
        mods |= Modifier::Capslock ;
    else if ( [event modifierFlags] & NSEventModifierFlagHelp )
        mods |= Modifier::Help ;
    else if ( [event modifierFlags] & NSEventModifierFlagShift )
        mods |= Modifier::Shift ;
    else if ( [event modifierFlags] & NSEventModifierFlagOption )
        mods |= Modifier::Option ;
    else if ( [event modifierFlags] & NSEventModifierFlagCommand )
        mods |= Modifier::Command ;
    else if ( [event modifierFlags] & NSEventModifierFlagControl )
        mods |= Modifier::Control ;
    else if ( [event modifierFlags] & NSEventModifierFlagFunction )
        mods |= Modifier::Function ;
    else if ( [event modifierFlags] & NSEventModifierFlagNumericPad )
        mods |= Modifier::NumPad ;
    else if ( [event modifierFlags] & NSEventModifierFlagDeviceIndependentFlagsMask )
        mods |= Modifier::DeviceIndependent ;
    
    assert( m_requester && "Requester is 'nil'." );
    m_requester->NotifiateViewKeyUp( key , text , mods );
}

////////////////////////////////////////////////////////////
- (void) dealloc
{
    if ( m_trackarea )
        [m_trackarea release];
    
    [super dealloc];
}

@end
