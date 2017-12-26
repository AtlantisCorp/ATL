//  ========================================================================  //
//
//  File    : OSXWindow/Scaling.mm
//  Project : ATL/OSXWindow
//  Author  : Luk2010
//  Date    : 12/10/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#include <OSXWindow/Scaling.h>

////////////////////////////////////////////////////////////
atl::String AtlStringFromNSString( NSString* str )
{
    return atl::String([str UTF8String]);
}

////////////////////////////////////////////////////////////
NSString* AtlStringToNSString( const atl::String& str )
{
    return [NSString stringWithUTF8String:str.data()];
}
