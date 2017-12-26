//  ========================================================================  //
//
//  File    : ATL/Darwin/Platform.cpp
//  Project : atlresource
//  Author  : Luk2010
//  Date    : 01/10/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //

#include <ATL/Darwin/Platform.hpp>
#include <ATL/Root.hpp>

// -------------------------------------------------------------------------------------------------------
// Internal definitions and includes.
// -------------------------------------------------------------------------------------------------------

// Needed for _NSGetProgname
#include <crt_externs.h>

// HACK: The 10.12 SDK adds new symbols and immediately deprecates the old ones
#if MAC_OS_X_VERSION_MAX_ALLOWED < 101200
#define NSWindowStyleMaskBorderless NSBorderlessWindowMask
#define NSWindowStyleMaskClosable NSClosableWindowMask
#define NSWindowStyleMaskMiniaturizable NSMiniaturizableWindowMask
#define NSWindowStyleMaskResizable NSResizableWindowMask
#define NSWindowStyleMaskTitled NSTitledWindowMask
#define NSEventModifierFlagCommand NSCommandKeyMask
#define NSEventModifierFlagControl NSControlKeyMask
#define NSEventModifierFlagOption NSAlternateKeyMask
#define NSEventModifierFlagShift NSShiftKeyMask
#define NSEventModifierFlagDeviceIndependentFlagsMask NSDeviceIndependentModifierFlagsMask
#define NSEventMaskAny NSAnyEventMask
#define NSEventTypeApplicationDefined NSApplicationDefined
#define NSEventTypeKeyUp NSKeyUp
#endif

// -------------------------------------------------------------------------------------------------------
// Local functions.
// -------------------------------------------------------------------------------------------------------

static void _AtlPostEmptyEvent( void )
{
    NSAutoreleasePool* pool = [[NSAutoreleasePool alloc] init];
    NSEvent* event = [NSEvent otherEventWithType:NSEventTypeApplicationDefined
                                        location:NSMakePoint(0, 0)
                                   modifierFlags:0
                                       timestamp:0
                                    windowNumber:0
                                         context:nil
                                         subtype:0
                                           data1:0
                                           data2:0];
    [NSApp postEvent:event atStart:YES];
    [pool drain];
}

// -------------------------------------------------------------------------------------------------------
// AtlApplicationDelegate class.
// -------------------------------------------------------------------------------------------------------

@interface AtlApplicationDelegate : NSObject
@end

@implementation AtlApplicationDelegate

- (NSApplicationTerminateReply) applicationShouldTerminate: (NSApplication*) sender
{
    // As this function might be called after Root has been destroyed, additional care
    // should be done to check the Root value and not reloading a Root object.
    
    if ( !atl::Root::GetPtr() )
        return NSTerminateNow ;
    
    auto WeakWins = atl::Root::Get().GetSurfaces();
    
    for ( auto it = WeakWins.begin() ; it != WeakWins.end() ; it++ )
    {
        if ( !it -> expired() )
        {
            it -> lock() -> Close();
        }
    }
    
    return NSTerminateCancel ;
}

- (void) applicationDidFinishLaunching: (NSNotification*) notification
{
    [NSApp stop:nil];
    _AtlPostEmptyEvent();
}

- (void) applicationDidHide: (NSNotification*) notification
{
    
}

@end

// -------------------------------------------------------------------------------------------------------
// AtlApplication class.
// -------------------------------------------------------------------------------------------------------

@interface AtlApplication : NSApplication
{
    NSArray* iNibObjects ;
}

@end

@implementation AtlApplication

// From http://cocoadev.com/index.pl?GameKeyboardHandlingAlmost
// This works around an AppKit bug, where key up events while holding
// down the command key don't get sent to the key window.
- (void)sendEvent:(NSEvent *)event
{
    if ([event type] == NSEventTypeKeyUp &&
        ([event modifierFlags] & NSEventModifierFlagCommand))
    {
        [[self keyWindow] sendEvent:event];
    }
    else
        [super sendEvent:event];
}


// No-op thread entry point
//
- (void) doNothing:(id)object
{
    
}

- (void)loadMainMenu
{
#if MAC_OS_X_VERSION_MAX_ALLOWED >= 100800
    [[NSBundle mainBundle] loadNibNamed:@"MainMenu"
                                  owner:NSApp
                        topLevelObjects:&iNibObjects];
#else
    [[NSBundle mainBundle] loadNibNamed:@"MainMenu" owner:NSApp];
#endif
}

@end

// -------------------------------------------------------------------------------------------------------
// Implementation of atl::Platform for Darwin OS X.
// -------------------------------------------------------------------------------------------------------

namespace atl
{
    Platform::Platform()
    {

    }

    Platform::~Platform()
    {
        if ( iAutoReleasePool )
        {
            [iAutoReleasePool release];
            iAutoReleasePool = nil ;
        }
    }
    
    String Platform::GetName() const
    {
        return "Platform: OSX" ;
    }
    
    String Platform::GetDefaultSurfacer() const
    {
        return "OSXWindow" ;
    }
    
    String Platform::GetDefaultDriver() const
    {
        return "Gl3Driver" ;
    }
    
    String Platform::GetDefaultAutoload() const
    {
        return "Plugins" ;
    }

    bool Platform::Init()
    {
        iAutoReleasePool = [[NSAutoreleasePool alloc] init];
        assert( iAutoReleasePool && "Invalid NSAutoreleasePool allocation." );
        
        if ( NSApp )
        return true ;
        
        [AtlApplication sharedApplication];
        
        // Makes Cocoa enter multithreaded mode.
        
        [NSThread detachNewThreadSelector:@selector(doNothing:)
                                 toTarget:NSApp
                               withObject:nil];
        
        // In case we are unbundled, makes a proper UI activation.
        
        [NSApp setActivationPolicy:NSApplicationActivationPolicyRegular];
        
        // Menu bar setup must go between sharedApplication above and
        // finishLaunching below, in order to properly emulate the behavior
        // of NSApplicationMain
        
        if ( [[NSBundle mainBundle] pathForResource:@"MainMenu" ofType:@"nib" ] )
        {
            [NSApp loadMainMenu];
        }
        
        else
        {
            Root::Get().GetLogger().log( "'MainMenu.nib' resource not found. One can use this file to create a" ,
                                         " custom menu for its application." );
        }
        
        iAppDelegate = [[AtlApplicationDelegate alloc] init];
        
        if ( iAppDelegate == nil )
        {
            Root::Get().GetLogger().log( "'iAppDelegate' could not be allocated." );
            return false ;
        }
        
        [NSApp setDelegate:iAppDelegate];
        [NSApp run];
        
        // Press and Hold prevents some keys from emitting repeated characters
        
        NSDictionary* defaults = [NSDictionary dictionaryWithObjectsAndKeys:[NSNumber numberWithBool:NO],
                                                                            @"ApplePressAndHoldEnabled",
                                                                            nil];
        [[NSUserDefaults standardUserDefaults] registerDefaults:defaults];
        
        return true ;
    }
}
