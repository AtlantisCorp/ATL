//  ========================================================================  //
//
//  File    : Gl3Driver/OSX/Gl3PixelFormat.h
//  Project : ATL/Gl3Driver
//  Author  : Luk2010
//  Date    : 15/10/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#ifndef Gl3PixelFormat_h
#define Gl3PixelFormat_h

#include <Gl3Driver/Gl3Includes.h>
#include <ATL/ContextSettings.hpp>

////////////////////////////////////////////////////////////
/// \brief Converts the given ContextSettings to its NSOpenGLPixelFormat
/// corresponding object.
///
////////////////////////////////////////////////////////////
NSOpenGLPixelFormat* Gl3ConvertContextSettings( const atl::ContextSettings& settings );

#endif /* Gl3PixelFormat_h */
