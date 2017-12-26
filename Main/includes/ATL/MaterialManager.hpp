//  ========================================================================  //
//
//  File    : ATL/MaterialManager.hpp
//  Project : atlresource
//  Author  : Luk2010
//  Date    : 17/10/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#ifndef MaterialManager_hpp
#define MaterialManager_hpp

#include <ATL/Material.hpp>
#include <ATL/Manager.hpp>

namespace atl
{
    ////////////////////////////////////////////////////////////
    /// \brief Defines a simple Manager for Materials.
    ///
    ////////////////////////////////////////////////////////////
    class MaterialManager : public Manager < Material >
    {
        
    };
}

#endif /* MaterialManager_hpp */
