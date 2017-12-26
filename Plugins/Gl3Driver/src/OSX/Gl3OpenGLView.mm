//  ========================================================================  //
//
//  File    : Gl3Driver/OSX/Gl3OpenGLView.mm
//  Project : ATL/Gl3Driver
//  Author  : Luk2010
//  Date    : 15/10/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#include <Gl3Driver/OSX/Gl3OpenGLView.h>
#include <Gl3Driver/Gl3Context.h>

////////////////////////////////////////////////////////////
@implementation Gl3OpenGLView

////////////////////////////////////////////////////////////
- (id) initWithView:(NSView*)view andFormat:(NSOpenGLPixelFormat *)format andRequester:(Gl3Context*)requester
{
    assert( view && "Null NSView parent view given." );
    assert( requester && "Null Requester given." );
    assert( format && "Null NSOpenGLPixelFormat given." );
    
    if ( self = [super initWithFrame:[view frame]] )
    {
        m_context = nil ;
        m_pixformat = nil ;
        m_requester = nil ;
        
        m_context = [[NSOpenGLContext alloc] initWithFormat:format shareContext:nil];
        assert( m_context && "Impossible to create NSOpenGLContext." );
        
        m_pixformat = format ;
        m_requester = requester ;
        
        [view addSubview:self];
        [view setAutoresizesSubviews:YES];
        [self setAutoresizingMask:NSViewWidthSizable|NSViewHeightSizable];
        
        [[NSNotificationCenter defaultCenter] addObserver:self
                                                 selector:@selector(_surfaceNeedsUpdate:)
                                                     name:NSViewGlobalFrameDidChangeNotification
                                                   object:self];
    }
    
    return self ;
}

////////////////////////////////////////////////////////////
- (void) dealloc
{
    [[NSNotificationCenter defaultCenter] removeObserver:self
                                                    name:NSViewGlobalFrameDidChangeNotification
                                                  object:self];
    if ( m_context )
    {
        [m_context release];
    }
    
    [super dealloc];
}

////////////////////////////////////////////////////////////
- (void) _surfaceNeedsUpdate:(NSNotification*)notification
{
    [self update];
}

////////////////////////////////////////////////////////////
- (void) update
{
    if ( m_context )
    {
        [m_context update];
    }
}

////////////////////////////////////////////////////////////
- (void) setContextActive:(BOOL)active
{
    if ( m_context )
    {
        if ( active )
        {
            [m_context lock];
            [m_context makeCurrentContext];
        }
        
        else
        {
            [m_context unlock];
            [[NSOpenGLContext class] clearCurrentContext];
        }
    }
}

////////////////////////////////////////////////////////////
- (void) flushContext
{
    if ( m_context )
    {
        [m_context flushBuffer];
    }
}

////////////////////////////////////////////////////////////
- (void) lockFocus
{
    [super lockFocus];
    [m_context setView:self];
}

////////////////////////////////////////////////////////////
- (void) clearColorFloat4:(float*)color
{
    assert( glGetError() == GL_NO_ERROR && "Previous OpenGL error not caught." );
    
    glClearColor( color[0] , color[1] , color[2] , color[3] );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    
    assert( glGetError() == GL_NO_ERROR && "OpenGL Error occured. Did you called 'RenderWindow::Display()' before ?" );
}

@end
