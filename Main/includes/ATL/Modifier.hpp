//  ========================================================================  //
//
//  File    : ATL/Modifier.hpp
//  Project : atlresource
//  Author  : Luk2010
//  Date    : 14/10/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#ifndef Modifier_hpp
#define Modifier_hpp

#include <ATL/StdIncludes.hpp>

namespace atl
{
    ////////////////////////////////////////////////////////////
    /// \brief Defines some key modifiers.
    ///
    ////////////////////////////////////////////////////////////
    namespace Modifier
    {
        enum
        {
            None     = 0 ,
            
            Capslock = 1 << 0 ,
            Help     = 1 << 1 ,
            Shift    = 1 << 2 ,
            Option   = 1 << 3 ,
            Command  = 1 << 4 ,
            Control  = 1 << 5 ,
            Function = 1 << 6 ,
            NumPad   = 1 << 7 ,
            
            DeviceIndependent = 1 << 8
        };
    }
    
    ////////////////////////////////////////////////////////////
    typedef unsigned long Modifiers ;
}

#endif /* Modifier_hpp */
