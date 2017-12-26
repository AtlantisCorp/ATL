//  ========================================================================  //
//
//  File    : ATL/SurfaceStyle.hpp
//  Project : atlresource
//  Author  : Luk2010
//  Date    : 09/10/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //

#ifndef SurfaceStyle_h
#define SurfaceStyle_h

namespace atl
{
    namespace SurfaceStyle
    {
        ////////////////////////////////////////////////////////////
        /// \brief Enumeration of the Surface's styles.
        ///
        ////////////////////////////////////////////////////////////
        enum
        {
            None        = 0 ,
            Titlebar    = 1 << 0 ,
            Resizable   = 1 << 1 , ///< Titlebar + resizable border + maximize button.
            Closable    = 1 << 2 , ///< Titlebar + close button.
            Fullscreen  = 1 << 3 , ///< Nothing but fullscreen mode.
            
            Default = Titlebar | Resizable | Closable
        };
    }
    
    typedef unsigned long Style ;
}

#endif /* SurfaceStyle_h */
