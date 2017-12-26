//  ========================================================================  //
//
//  File    : ATL/VideoMode.hpp
//  Project : atlresource
//  Author  : Luk2010
//  Date    : 09/10/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#ifndef VideoMode_hpp
#define VideoMode_hpp

#include <ATL/StdIncludes.hpp>

namespace atl
{
    ////////////////////////////////////////////////////////////
    /// \brief Defines a simple video mode for a Window.
    ///
    /// You can retrieve current desktop mode by using Driver::GetDesktopMode()
    /// and fullscreen modes by using Driver::GetFullscreenModes().
    ///
    ////////////////////////////////////////////////////////////
    struct VideoMode
    {
        uint32_t width ;
        uint32_t height ;
        uint32_t bitsperpixels ;
        
        ////////////////////////////////////////////////////////////
        VideoMode() : width(0) , height(0) , bitsperpixels(0) { }
        
        ////////////////////////////////////////////////////////////
        VideoMode( uint32_t w , uint32_t h , uint32_t bpp ) : width(w) , height(h) , bitsperpixels(bpp) { }
    };
}

#endif /* VideoMode_hpp */
