//  ========================================================================  //
//
//  File    : Gl3Driver/Gl3Includes.h
//  Project : ATL/Gl3Driver
//  Author  : Luk2010
//  Date    : 15/10/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#ifndef GL3DRIVER_GL3INCLUDES_H
#define GL3DRIVER_GL3INCLUDES_H

#include <ATL/StdIncludes.hpp>

/// \brief Undef this constant if you want to disable glGetError() checks (this can be a speed optimization for releases).
#define GL3DRIVER_CATCHGLERROR

#if ATL_PLATFORM == ATL_PLATFORM_DARWIN

#   import <OpenGL/OpenGL.h>
#   import <OpenGL/gl3.h>

#   ifdef __OBJC__
#       import <Cocoa/Cocoa.h>
        typedef NSOpenGLContext* Gl3ContextClass ;
#   else
        typedef void* Gl3ContextClass ;
#   endif

#endif // ATL_PLATFORM_DARWIN

////////////////////////////////////////////////////////////
/// \brief Enumerates possible errors to throw a Gl3Exception.
///
////////////////////////////////////////////////////////////
enum class Gl3Error : unsigned long
{
    None = 0 ,
    
    EmptyFile ,
    EmptyStream ,
    
    GlCompileShader ,
    GlCreateShader ,
    GlLinkProgram
};

////////////////////////////////////////////////////////////
/// \brief Defines a classic Exception on top of std::exception
/// to make easier instanciation of exceptions.
///
////////////////////////////////////////////////////////////
class Gl3Exception : public std::exception
{
    ////////////////////////////////////////////////////////////
    atl::String m_message ; ///< Message to return in 'what'.
    
    ////////////////////////////////////////////////////////////
    Gl3Error m_error ; ///< Error code.
    
public:
    
    ////////////////////////////////////////////////////////////
    Gl3Exception( Gl3Error errcode , const char* format , ... );
    
    ////////////////////////////////////////////////////////////
    const char* what() const noexcept ;
};

#endif // GL3DRIVER_GL3INCLUDES_H
