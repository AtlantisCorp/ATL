//  ========================================================================  //
//
//  File    : Platform.hpp - Darwin
//  Project : atlresource
//  Author  : Luk2010
//  Date    : 30/09/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //

#ifndef Platform_darwin_hpp
#define Platform_darwin_hpp

#include <ATL/StdIncludes.hpp>

#if defined(__OBJC__)
#   include <Carbon/Carbon.h>
#   include <Cocoa/Cocoa.h>
#
#else
#   include <Carbon/Carbon.h>
#   include <ApplicationServices/ApplicationServices.h>
    typedef void* id ;
#
#endif

namespace atl
{
    ////////////////////////////////////////////////////////////
    /// \brief Defines some utilities platform-dependent.
    ///
    /// Those basics are needed when launching the Root object. It
    /// can deploy an OSX Application, or initialize X11, or whatever
    /// is needed when starting an application.
    ///
    ////////////////////////////////////////////////////////////
    class Platform : public Singleton < Platform >
    {
        id iAutoReleasePool ;
        id iAppDelegate ;

    public:

        Platform();
        ~Platform();

        bool Init();
        
        ////////////////////////////////////////////////////////////
        /// \brief Returns a brief platform's name.
        ///
        ////////////////////////////////////////////////////////////
        String GetName() const ;
        
        ////////////////////////////////////////////////////////////
        /// \brief Get default surfacer lib for this platform.
        ///
        ////////////////////////////////////////////////////////////
        String GetDefaultSurfacer() const ;
        
        ////////////////////////////////////////////////////////////
        /// \brief Get default driver lib for this platform.
        ///
        ////////////////////////////////////////////////////////////
        String GetDefaultDriver() const ;
        
        ////////////////////////////////////////////////////////////
        /// \brief Get default autoload path for this platform.
        ///
        ////////////////////////////////////////////////////////////
        String GetDefaultAutoload() const ;
    };
}

#endif // Platform_darwin_hpp
