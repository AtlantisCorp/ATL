//  ========================================================================  //
//
//  File    : Platform.hpp
//  Project : atlresource
//  Author  : Luk2010
//  Date    : 30/09/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //

#ifndef Platform_hpp
#define Platform_hpp

#include <ATL/StdIncludes.hpp>

#if ATL_PLATFORM == ATL_PLATFORM_LINUX
#   include <ATL/Linux/Platform.hpp>
#
#elif ATL_PLATFORM == ATL_PLATFORM_DARWIN
#   include <ATL/Darwin/Platform.hpp>
#
#elif ATL_PLATFORM == ATL_PLATFORM_WINDOWS
#   include <ATL/Windows/Platform.hpp>
#
#else
#   include <ATL/Unknown/Platform.hpp>
#
#endif

#endif // Platform_hpp
