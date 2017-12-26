//  ========================================================================  //
//
//  File    : ATL/LoadingContext.hpp
//  Project : atlresource
//  Author  : Luk2010
//  Date    : 25/10/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#ifndef LoadingContext_hpp
#define LoadingContext_hpp

#include <ATL/StdIncludes.hpp>

namespace atl
{
    ////////////////////////////////////////////////////////////
    class RenderWindow ;
    class Driver ;
    class Surfacer ;
    
    ////////////////////////////////////////////////////////////
    /// \brief A simple context that is given to the loading queue
    /// subfunction when called.
    ///
    ////////////////////////////////////////////////////////////
    struct LoadingContext
    {
        ////////////////////////////////////////////////////////////
        Weak < RenderWindow > renderwindow ; ///< Passed RenderWindow.
        Weak < Driver >       driver ;       ///< Current Driver registered in Root.
        Weak < Surfacer >     surfacer ;     ///< Current Surfacer registered in Root.
        void*                 data ;         ///< Arbitrary structure given to the function.
    };
}

#endif /* LoadingContext_hpp */
