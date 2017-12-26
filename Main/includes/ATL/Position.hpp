//  ========================================================================  //
//
//  File    : ATL/Position.hpp
//  Project : atlresource
//  Author  : Luk2010
//  Date    : 09/10/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //

#ifndef Position_h
#define Position_h

#include <ATL/StdIncludes.hpp>

namespace atl
{
    ////////////////////////////////////////////////////////////
    /// \brief Defines a simple position structure ( x, y ) in pixels.
    ///
    ////////////////////////////////////////////////////////////
    struct Position
    {
        int32_t x ;
        int32_t y ;
        
        ////////////////////////////////////////////////////////////
        Position() : x( 0 ) , y( 0 ) { }
        
        ////////////////////////////////////////////////////////////
        Position( int32_t _x , int32_t _y ) : x(_x) , y(_y) { }
    };
}

#endif /* Position_h */
