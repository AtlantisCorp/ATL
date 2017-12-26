//  ========================================================================  //
//
//  File    : OSXWindow/OSXSurfacer.h
//  Project : ATL/OSXWindow
//  Author  : Luk2010
//  Date    : 10/10/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#ifndef OSXWINDOW_OSXSURFACER_H
#define OSXWINDOW_OSXSURFACER_H

#include <ATL/Surfacer.hpp>
using namespace atl ;

////////////////////////////////////////////////////////////
/// \brief Creates and manages OSXSurface objects.
///
////////////////////////////////////////////////////////////
class OSXSurfacer : public atl::Surfacer
{
public:
    
    ////////////////////////////////////////////////////////////
    OSXSurfacer();
    
    ////////////////////////////////////////////////////////////
    virtual ~OSXSurfacer();
    
    ////////////////////////////////////////////////////////////
    /// \brief Return "OSX Surfacer".
    ///
    ////////////////////////////////////////////////////////////
    virtual String GetName() const ;
    
    ////////////////////////////////////////////////////////////
    /// \brief Return the current desktop video mode.
    ///
    ////////////////////////////////////////////////////////////
    virtual VideoMode GetDesktopVideoMode() const ;
    
    ////////////////////////////////////////////////////////////
    /// \brief Create a Surface which is can be assimilated to a
    /// NSWindow object.
    ///
    /// The NSWindow object is owned by the Surface and is released
    /// when the Surface object is destroyed. This means that 'Close()'
    /// does not destroy the NSWindow nor the NSOpenGLView.
    ///
    /// \param mode VideoMode to create the Surface.
    /// \param title Title to give to this Surface.
    ///
    /// \return An initialized Surface object.
    ///
    ////////////////////////////////////////////////////////////
    virtual Weak < Surface > CreateSurface( const VideoMode& mode ,
                                            const String& title ,
                                            atl::Style style = SurfaceStyle::Default );
    
    ////////////////////////////////////////////////////////////
    /// \brief Create a Surface from a pre-existing SurfaceHandle.
    ///
    /// \param handle A valid surface handle to create the Surface
    /// from. It can be a NSView or a NSWindow handle. The Surface
    /// will take control of a subview of class NSOpenGLView.
    ///
    /// \return An initialized Surface object.
    ///
    ////////////////////////////////////////////////////////////
    virtual Weak < Surface > CreateSurface( SurfaceHandle handle );
};

#endif // OSXWINDOW_OSXSURFACER_H
