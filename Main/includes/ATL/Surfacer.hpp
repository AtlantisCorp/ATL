//  ========================================================================  //
//
//  File    : ATL/Surfacer.hpp
//  Project : atlresource
//  Author  : Luk2010
//  Date    : 09/10/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //

#ifndef Surfacer_h
#define Surfacer_h

#include <ATL/StdIncludes.hpp>
#include <ATL/VideoMode.hpp>
#include <ATL/SurfaceHandle.hpp>
#include <ATL/Surface.hpp>

namespace atl
{
    ////////////////////////////////////////////////////////////
    /// \brief Defines an interface which creates and manages atl::Surface
    /// objects.
    ///
    /// A Surfacer can be provided from an external library from
    /// the 'config.atl' file, from the command line arg '--surfacerlib'
    /// or from 'Platform::GetDefaultSurfacer()', in that order of priority.
    ///
    ////////////////////////////////////////////////////////////
    class Surfacer
    {
        SharedVector < Surface > m_surfaces ; ///< List of surfaces created by this surfacer.
        mutable Mutex            m_mutex ;    ///< Mutex to watch for data.
        
    public:
        
        ////////////////////////////////////////////////////////////
        Surfacer();
        
        ////////////////////////////////////////////////////////////
        virtual ~Surfacer();
        
        ////////////////////////////////////////////////////////////
        /// \brief Return a human-readable name for this surfacer.
        ///
        ////////////////////////////////////////////////////////////
        virtual String GetName() const = 0 ;
        
        ////////////////////////////////////////////////////////////
        /// \brief Return the current desktop video mode.
        ///
        ////////////////////////////////////////////////////////////
        virtual VideoMode GetDesktopVideoMode() const = 0 ;
        
        ////////////////////////////////////////////////////////////
        /// \brief Create a Surface which is generally a window object.
        ///
        /// \param mode VideoMode to create the Surface.
        /// \param title Title to give to this Surface.
        ///
        /// \return An initialized Surface object.
        ///
        ////////////////////////////////////////////////////////////
        virtual Weak < Surface > CreateSurface( const VideoMode& mode ,
                                                const String& title ,
                                                Style style = SurfaceStyle::Default ) = 0 ;
        
        ////////////////////////////////////////////////////////////
        /// \brief Create a Surface from a pre-existing SurfaceHandle.
        ///
        /// \param handle A valid surface handle to create the Surface
        /// from. You can get this handle to SurfaceHandle by using
        /// 'HandleConvert( systemhandle );'.
        ///
        /// \return An initialized Surface object.
        ///
        ////////////////////////////////////////////////////////////
        virtual Weak < Surface > CreateSurface( SurfaceHandle handle ) = 0 ;
        
        ////////////////////////////////////////////////////////////
        /// \brief Retrieve registered/created Surfaces.
        ///
        ////////////////////////////////////////////////////////////
        virtual WeakVector < Surface > GetSurfaces( void ) const ;
        
        ////////////////////////////////////////////////////////////
        /// \brief Remove a Surface by locking the internal mutex.
        ///
        ////////////////////////////////////////////////////////////
        virtual void RemoveSurface( const Weak < Surface >& surface );
        
    protected:
        
        ////////////////////////////////////////////////////////////
        /// \brief Add a Surface by locking the mutex.
        ///
        ////////////////////////////////////////////////////////////
        virtual void AddSurface( const Shared < Surface >& surface );
    };
}

#endif /* Surfacer_h */
