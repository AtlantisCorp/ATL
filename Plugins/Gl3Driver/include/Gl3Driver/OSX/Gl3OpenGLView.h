//  ========================================================================  //
//
//  File    : Gl3Driver/OSX/Gl3OpenGLView.h
//  Project : ATL/Gl3Driver
//  Author  : Luk2010
//  Date    : 15/10/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#ifndef Gl3OpenGLView_h
#define Gl3OpenGLView_h

#include <Gl3Driver/Gl3Includes.h>

class Gl3Context ;

////////////////////////////////////////////////////////////
/// \brief Interface to manage a NSOpenGLContext and a
/// NSOpenGLPixelFormat together.
///
////////////////////////////////////////////////////////////
@interface Gl3OpenGLView : NSView
{
    NSOpenGLContext*     m_context ;    ///< Context associated with this view.
    NSOpenGLPixelFormat* m_pixformat ;  ///< Pixel format associated to the context.
    Gl3Context*          m_requester ;  ///< Gl3Context that created this view.
}

////////////////////////////////////////////////////////////
/// \brief Inits the glview with a parent view and a format.
///
/// The glview takes the maximum size it can take (the view's frame)
/// and sets autoresizing to resize its content to the parent's
/// view frame.
///
/// \param view   A view to take as parent.
/// \param format Generally a format taken from Gl3ConvertContextSettings
///               and passed to this function from Gl3Context.
///
////////////////////////////////////////////////////////////
- (id) initWithView:(NSView*)view andFormat:(NSOpenGLPixelFormat*)format andRequester:(Gl3Context*)requester ;

////////////////////////////////////////////////////////////
/// \brief Updates the view.
///
////////////////////////////////////////////////////////////
- (void) update ;

////////////////////////////////////////////////////////////
- (void) setContextActive:(BOOL)active ;

////////////////////////////////////////////////////////////
- (void) flushContext ;

////////////////////////////////////////////////////////////
- (void) clearColorFloat4:(float*)color ;

@end

#endif /* Gl3OpenGLView_h */
