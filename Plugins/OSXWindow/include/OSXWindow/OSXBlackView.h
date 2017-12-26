//  ========================================================================  //
//
//  File    : OSXWindow/OSXBlackView.h
//  Project : ATL/OSXWindow
//  Author  : Luk2010
//  Date    : 11/10/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#ifndef OSXBlackView_h
#define OSXBlackView_h

#include <Cocoa/Cocoa.h>

class OSXSurface ;

////////////////////////////////////////////////////////////
/// \brief Interfaces to an ATL controlled NSView.
///
/// This object handles every events and make the requester
/// atl::Surface sends those events.
///
/// Initializing from a NSWindow: the view will take the window's
/// frame, being its content view and its first responder. All events
/// will be treated here. Notes that a OSXWindowDelegate will be created
/// to take care of close/expose/... events.
///
/// Initializing from a NSView: the view will take the view'frame
/// and be added as a subview. However, the NSView must follow its events
/// to its children for the OSXBlackView to handle events.
///
////////////////////////////////////////////////////////////
@interface OSXBlackView : NSView
{
    OSXSurface*     m_requester ; ///< The Surface which invoked this object.
    NSWindow*       m_window ;    ///< If invoked with a NSWindow, not nil.
    NSView*         m_view ;      ///< If invoked with a NSView, not nil.
    NSTrackingArea* m_trackarea ; ///< A NSTrackingArea to track mouse's entered, exited, and moved.
    UInt32          m_deadkey ;   ///< Actual deadkey state used by UCKeyTranslate.
    NSPoint         m_cursorpos ; ///< Actual cursor position relative to this view.
    BOOL            m_cursorin ;  ///< YES if cursor is in view, NO if not.
}

////////////////////////////////////////////////////////////
/// \brief Initializes the OSXBlackView with a NSWindow.
///
/// Also makes this view the first responder (if possible) and
/// the contentview of the given window. Size is adjusted to the
/// NSWindow's frame rect.
///
/// \param window NSWindow to control as a first responder.
/// \param surface OSXSurface where to send event when received.
///
////////////////////////////////////////////////////////////
- (id) initWithWindow:(NSWindow*)window WithRequester:(OSXSurface*)surface ;

////////////////////////////////////////////////////////////
/// \brief Initializes the OSXBlackView with a NSView.
///
/// Also makes this view an event responder from its parent's
/// view. Size is adjusted to given view's frame.
///
/// \param view NSView to subchild.
/// \param surface OSXSurface where to send events.
///
////////////////////////////////////////////////////////////
- (id) initWithView:(NSView*)view WithRequester:(OSXSurface*)surface ;

////////////////////////////////////////////////////////////
/// \brief Called when the NSWindow will close.
///
////////////////////////////////////////////////////////////
- (void) windowWillClose:(NSNotification*)notification ;

////////////////////////////////////////////////////////////
/// \brief Called on NSWindowDidMoveNotification.
///
////////////////////////////////////////////////////////////
- (void) windowDidMove:(NSNotification*)notification ;

////////////////////////////////////////////////////////////
/// \brief Initializes the tracking area to the current view's
/// frame.
///
////////////////////////////////////////////////////////////
- (void) initTrackingArea ;

@end

#endif /* OSXBlackView_h */
