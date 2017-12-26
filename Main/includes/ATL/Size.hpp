//  ========================================================================  //
//
//  File    : ATL/Size.hpp
//  Project : atlresource
//  Author  : Luk2010
//  Date    : 09/10/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //

#ifndef Size_h
#define Size_h

#include <ATL/StdIncludes.hpp>

namespace atl
{
    ////////////////////////////////////////////////////////////
    /// \brief Defines a simple size structure (width, height),
    /// in pixels coordinates.
    ///
    ////////////////////////////////////////////////////////////
    struct Size
    {
        uint32_t width ;
        uint32_t height ;
        
        ////////////////////////////////////////////////////////////
        Size() : width( 0 ) , height( 0 ) { }
        
        ////////////////////////////////////////////////////////////
        Size( uint32_t w , uint32_t h ) : width( w ) , height( h ) { }
    };
}

#endif /* Size_h */
