//  ========================================================================  //
//
//  File    : ATL/MeshManager.hpp
//  Project : atlresource
//  Author  : Luk2010
//  Date    : 18/11/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#ifndef MeshManager_hpp
#define MeshManager_hpp

#include <ATL/Mesh.hpp>
#include <ATL/Manager.hpp>

namespace atl
{
    ////////////////////////////////////////////////////////////
    /// \brief A basic manager for Meshes objects.
    ///
    /// As a Mesh relies on some internal buffers or on some external
    /// file, a Manager for Resource is a good solution to manage those
    /// objects easily.
    ///
    ////////////////////////////////////////////////////////////
    class MeshManager : public Manager < Mesh >
    {
        
    };
}

#endif /* MeshManager_hpp */
