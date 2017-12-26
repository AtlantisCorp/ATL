//  ========================================================================  //
//
//  File    : Gl3Driver/OSX/Gl3PixelFormat.mm
//  Project : ATL/Gl3Driver
//  Author  : Luk2010
//  Date    : 15/10/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#include <Gl3Driver/OSX/Gl3PixelFormat.h>

////////////////////////////////////////////////////////////
NSOpenGLPixelFormat* Gl3ConvertContextSettings( const atl::ContextSettings& settings )
{
    NSOpenGLPixelFormatAttribute attrs [30] ;
    int i = 0 ;
    
#define PUSH_ATTR( a ) attrs[i] = (NSOpenGLPixelFormatAttribute) a ; i++
    
    if ( settings.doublebuffered ) {
        PUSH_ATTR( NSOpenGLPFADoubleBuffer );
    }
    
    if ( settings.depthbits ) {
        PUSH_ATTR( NSOpenGLPFADepthSize );
        PUSH_ATTR( settings.depthbits );
    }
    
    if ( settings.accelerated ) {
        PUSH_ATTR( NSOpenGLPFAAccelerated );
    }
    
    if ( settings.multisampled ) {
        PUSH_ATTR( NSOpenGLPFAMultisample );
        
        PUSH_ATTR( NSOpenGLPFASampleBuffers );
        PUSH_ATTR( settings.samplesbuffers );
        
        PUSH_ATTR( NSOpenGLPFASamples );
        PUSH_ATTR( settings.samples );
    }
    
    PUSH_ATTR( NSOpenGLPFAOpenGLProfile );
    PUSH_ATTR( NSOpenGLProfileVersion3_2Core );
    
    PUSH_ATTR( 0 );
    
#undef PUSH_ATTR
    
    return [[NSOpenGLPixelFormat alloc] initWithAttributes:attrs];
}
