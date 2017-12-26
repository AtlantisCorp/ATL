//  ========================================================================  //
//
//  File    : ATL/Mouse.hpp
//  Project : atlresource
//  Author  : Luk2010
//  Date    : 13/10/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#ifndef Mouse_h
#define Mouse_h

#include <ATL/StdIncludes.hpp>

namespace atl
{
    ////////////////////////////////////////////////////////////
    /// \brief Defines Mouse's buttons.
    ///
    ////////////////////////////////////////////////////////////
    enum class MouseButton : unsigned long
    {
        Left  = 1 << 0 ,
        Right = 1 << 1 ,
        Wheel = 1 << 2
    };
    
    ////////////////////////////////////////////////////////////
    /// \brief Defines Mouse's actions.
    ///
    ////////////////////////////////////////////////////////////
    enum class MouseAction : unsigned long
    {
        Pressed  = 1 << 0 ,
        Released = 1 << 1
    };
}

#endif /* Mouse_h */
