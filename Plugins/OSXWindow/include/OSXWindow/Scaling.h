//  ========================================================================  //
//
//  File    : OSXWindow/Scaling.h
//  Project : ATL/OSXWindow
//  Author  : Luk2010
//  Date    : 10/10/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#ifndef Scaling_h
#define Scaling_h

#include <ATL/StdIncludes.hpp>
#import <AppKit/AppKit.h>

////////////////////////////////////////////////////////////
/// \brief Default Scaling factor on main screen.
///
////////////////////////////////////////////////////////////
inline CGFloat GetDefaultScaleFactor( void )
{
    return [[NSScreen mainScreen] backingScaleFactor];
}

////////////////////////////////////////////////////////////
/// \brief Scale ATL coordinates (pixels) to backing coordinates.
///
/// \param in Coordinate to scale.
/// \param delegate A NSObject that implements 'displayScaleFactor'
///                 function. 'nil' to get default scale factor.
///
/// \see https://github.com/SFML/SFML/blob/master/src/SFML/Window/OSX/Scaling.h
///
////////////////////////////////////////////////////////////
template < typename T >
void ScaleIn( T& in , id delegate )
{
    in /= /* delegate ? [delegate displayScaleFactor] : */ GetDefaultScaleFactor();
}

////////////////////////////////////////////////////////////
template < typename T >
void ScaleInWidthHeight( T& in , id delegate )
{
    ScaleIn( in.width , delegate );
    ScaleIn( in.height , delegate );
}

////////////////////////////////////////////////////////////
template < typename T >
void ScaleInXY( T& in , id delegate )
{
    ScaleIn( in.x , delegate );
    ScaleIn( in.y , delegate );
}

////////////////////////////////////////////////////////////
/// \brief Scale backing coordinates to ATL coordinates (pixels).
///
/// \param out Coordinate to scale.
/// \param delegate NSObject that implements 'displayScaleFactor',
///                 or nil if you want default scale factor.
///
////////////////////////////////////////////////////////////
template < typename T >
void ScaleOut( T& out , id delegate )
{
    out *= /* delegate ? [delegate displayScaleFactor] : */ GetDefaultScaleFactor();
}

////////////////////////////////////////////////////////////
template < typename T >
void ScaleOutWidthHeight( T& out , id delegate )
{
    ScaleOut( out.width , delegate );
    ScaleOut( out.height , delegate );
}

////////////////////////////////////////////////////////////
template < typename T >
void ScaleOutXY( T& out , id delegate )
{
    ScaleOut( out.x , delegate );
    ScaleOut( out.y , delegate );
}

////////////////////////////////////////////////////////////
/// \brief Converts an atl::String from a NSString.
///
////////////////////////////////////////////////////////////
atl::String AtlStringFromNSString( NSString* str );

////////////////////////////////////////////////////////////
/// \brief Converts an atl::String to a NSString.
///
////////////////////////////////////////////////////////////
NSString* AtlStringToNSString( const atl::String& str );

#endif /* Scaling_h */
