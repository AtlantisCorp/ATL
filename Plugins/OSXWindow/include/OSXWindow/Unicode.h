//  ========================================================================  //
//
//  File    : OSXWindow/Unicode.h
//  Project : ATL/OSXWindow
//  Author  : Luk2010
//  Date    : 14/10/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#ifndef OSXWINDOW_UNICODE_H
#define OSXWINDOW_UNICODE_H

#include <ATL/StdIncludes.hpp>
#include <Cocoa/Cocoa.h>

////////////////////////////////////////////////////////////
NSString * translateInputForKeyDown(NSEvent *event, UInt32 *deadKeyState);

////////////////////////////////////////////////////////////
/// \brief Detect if a given UTF8 character (as NSString) is
/// a special handled key, otherwise return 'AtlStringFromNSString()'.
///
////////////////////////////////////////////////////////////
atl::String AtlDetectKeyFromNSString( NSString* str );

#endif // OSXWINDOW_UNICODE_H
