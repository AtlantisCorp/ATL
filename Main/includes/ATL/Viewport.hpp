//  ========================================================================  //
//
//  File    : ATL/Viewport.hpp
//  Project : atlresource
//  Author  : Luk2010
//  Date    : 20/11/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#ifndef Viewport_hpp
#define Viewport_hpp

#include <ATL/StdIncludes.hpp>
#include <ATL/Size.hpp>
#include <ATL/Position.hpp>

namespace atl
{
    ////////////////////////////////////////////////////////////
    /// \brief Defines a Viewport for a RenderTarget.
    ///
    ////////////////////////////////////////////////////////////
    struct Viewport
    {
        ////////////////////////////////////////////////////////////
        Size     size ;   ///< Size in Pixels of the Viewport.
        Position origin ; ///< Bottom-left origin of the Viewport.
    };
}

#endif /* Viewport_hpp */
