//  ========================================================================  //
//
//  File    : ATL/SurfaceHandle.hpp
//  Project : atlresource
//  Author  : Luk2010
//  Date    : 09/10/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //

#ifndef SurfaceHandle_h
#define SurfaceHandle_h

#include <cstdint>

namespace atl
{
    ////////////////////////////////////////////////////////////
    /// \brief Generic handle for every surface system handle.
    ///
    /// Any handle stored with this system must not be bigger than
    /// the uintptr_t size. A handle should be a HWND, a Window,
    /// an id, a xcb_window_t, ... Those datas never exceed uintptr_t.
    /// Conversion should be made using reinterpret_cast.
    ///
    ////////////////////////////////////////////////////////////
    typedef uintptr_t SurfaceHandle ;
    
    ////////////////////////////////////////////////////////////
    /// \brief Convert the SurfaceHandle to given handle type.
    ///
    ////////////////////////////////////////////////////////////
    template < typename Handle >
    Handle HandleConvert( SurfaceHandle handle )
    {
        return reinterpret_cast < Handle >( handle );
    }
    
    ////////////////////////////////////////////////////////////
    /// \brief Convert a handle to SurfaceHandle.
    ///
    ////////////////////////////////////////////////////////////
    template < typename Handle >
    SurfaceHandle HandleConvert( Handle handle )
    {
        return reinterpret_cast < SurfaceHandle >( handle );
    }
}

#endif /* SurfaceHandle_h */
