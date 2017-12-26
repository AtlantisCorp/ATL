//  ========================================================================  //
//
//  File    : ATL/ContextSettings.cpp
//  Project : atlresource
//  Author  : Luk2010
//  Date    : 10/10/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //

#include <ATL/ContextSettings.hpp>

namespace atl
{
    ContextSettings ContextSettings::Default()
    {
        return
        {
            true , 32 , true , false , 1 , 4
        };
    }
}
