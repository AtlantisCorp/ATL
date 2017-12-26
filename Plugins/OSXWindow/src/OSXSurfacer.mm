//  ========================================================================  //
//
//  File    : OSXWindow/OSXSurfacer.mm
//  Project : ATL/OSXWindow
//  Author  : Luk2010
//  Date    : 10/10/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#include <ATL/Root.hpp>
#include <OSXWindow/OSXSurfacer.h>
#include <OSXWindow/OSXSurface.h>
#include <OSXWindow/Scaling.h>
#include <ApplicationServices/ApplicationServices.h>
#include <Foundation/Foundation.h>

////////////////////////////////////////////////////////////
/// \brief Converts the CGDisplayMode to atl::VideoMode.
///
////////////////////////////////////////////////////////////
static VideoMode ConvertCGToAtlVideoMode( CGDisplayModeRef cgmode )
{
    VideoMode mode ;
    mode.width = CGDisplayModeGetWidth( cgmode );
    mode.height = CGDisplayModeGetHeight( cgmode );
    
    // Since macOS 10.11, CGDisplayModeCopyPixelEncoding is deprecated. However, we do not have any
    // other solution to get bpp, and as this function is not removed, we can use it safely.
    CFStringRef pixenc = CGDisplayModeCopyPixelEncoding( cgmode );
    if ( CFStringCompare( pixenc , CFSTR(IO32BitDirectPixels) , kCFCompareCaseInsensitive ) == kCFCompareEqualTo )
        mode.bitsperpixels = 32 ;
    else if ( CFStringCompare( pixenc , CFSTR(IO16BitDirectPixels) , kCFCompareCaseInsensitive ) == kCFCompareEqualTo )
        mode.bitsperpixels = 16 ;
    else if ( CFStringCompare( pixenc , CFSTR(IO8BitIndexedPixels) , kCFCompareCaseInsensitive ) == kCFCompareEqualTo )
        mode.bitsperpixels = 8 ;
    else
        mode.bitsperpixels = 0 ;
    
    ScaleOutWidthHeight( mode , nil );
    return mode ;
}

////////////////////////////////////////////////////////////
OSXSurfacer::OSXSurfacer()
{
    assert( NSApp != nil && "NSApplication was not loaded correctly. Please use atl::Root::PlatformInit() before loading Surfacer." );
}

////////////////////////////////////////////////////////////
OSXSurfacer::~OSXSurfacer()
{
    
}

////////////////////////////////////////////////////////////
String OSXSurfacer::GetName() const
{
    return "OSX Surfacer" ;
}

////////////////////////////////////////////////////////////
VideoMode OSXSurfacer::GetDesktopVideoMode() const
{
    VideoMode retvalue ;
    
    CGDirectDisplayID display = CGMainDisplayID();
    CGDisplayModeRef dmode = CGDisplayCopyDisplayMode( display );
    retvalue = ConvertCGToAtlVideoMode( dmode );
    
    return retvalue ;
}

////////////////////////////////////////////////////////////
Weak < Surface > OSXSurfacer::CreateSurface( const VideoMode& mode , const String& title , atl::Style style )
{
    auto osxsurface = std::make_shared < OSXSurface >( mode , title , style );
    
    if ( osxsurface )
    {
        Surfacer::AddSurface( std::static_pointer_cast < Surface >( osxsurface ) );
        return std::static_pointer_cast< Surface >( osxsurface );
    }
    
    else
    {
        Root::Get().GetLogger().warn( "Can't allocate OSXSurface instance." );
        return Weak < Surface >();
    }
}

////////////////////////////////////////////////////////////
Weak < Surface > OSXSurfacer::CreateSurface( SurfaceHandle handle )
{
    auto osxsurface = std::make_shared < OSXSurface >( handle );
    
    if ( osxsurface )
    {
        Surfacer::AddSurface( std::static_pointer_cast < Surface >( osxsurface ) );
        return std::static_pointer_cast< Surface >( osxsurface );
    }
    
    else
    {
        Root::Get().GetLogger().warn( "Can't allocate OSXSurface instance." );
        return Weak < Surface >();
    }
}
