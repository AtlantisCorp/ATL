//  ========================================================================  //
//
//  File    : ATL/Driver.hpp
//  Project : atlresource
//  Author  : Luk2010
//  Date    : 19/09/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#ifndef Driver_hpp
#define Driver_hpp

#include <ATL/StdIncludes.hpp>
#include <ATL/RenderWindow.hpp>
#include <ATL/ContextSettings.hpp>
#include <ATL/RenderPath.hpp>

namespace atl
{
    ////////////////////////////////////////////////////////////
    /// \brief Manages a special drawing API, as OpenGL or DirectX10.
    ///
    /// Its role is to create specific instances of managed resources
    /// linked to the underlying API. A Driver should not use platform-dependent
    /// behaviour, but should rely on the surfacer. A Driver can get the underlying
    /// API of the surfacer by using 'Surfacer::GetSystemAPI()'. This can let the
    /// driver manages its compatibility.
    ///
    /// When creating a RenderWindow, the object takes ownership of the given
    /// Surface and of the given Context. This way, when the RenderWindow is
    /// destroyed, the Surface is removed from the Surfacer and the Context is
    /// destroyed.
    ///
    ////////////////////////////////////////////////////////////
    class Driver
    {
        SharedVector < RenderWindow > m_windows ;   ///< Holds renderwindows objects.
        mutable Mutex                 m_mutex ;     ///< Mutex to access objects.

    public:

        ////////////////////////////////////////////////////////////
        Driver();
        
        ////////////////////////////////////////////////////////////
        virtual ~Driver();
        
        ////////////////////////////////////////////////////////////
        /// \brief Get the driver's readable name.
        ///
        ////////////////////////////////////////////////////////////
        virtual String GetName() const = 0 ;
        
        ////////////////////////////////////////////////////////////
        /// \brief Create a RenderWindow from the given Surface.
        ///
        /// \param surface  Surface created with a Surfacer to implement
        ///                 a new context.
        /// \param settings Settings for the created Context.
        ///
        /// \return An initialized RenderWindow object.
        ///
        ////////////////////////////////////////////////////////////
        virtual Weak < RenderWindow > CreateRenderWindow( const Weak < Surface >& surface ,
                                                          const ContextSettings& settings = ContextSettings::Default() ) = 0 ;
        
        ////////////////////////////////////////////////////////////
        /// \brief Create a RenderWindow and its Surface, by using the
        /// selected Surfacer available in the Root object.
        ///
        /// \param mode     VideoMode to create the Surface.
        /// \param title    Title for the Surface.
        /// \param style    Style for the Surface.
        /// \param settings Settings for the created context.
        ///
        /// \return An initialized RenderWindow object.
        ///
        ////////////////////////////////////////////////////////////
        virtual Weak < RenderWindow > CreateRenderWindow( const VideoMode& mode ,
                                                          const String& title ,
                                                          atl::Style style = atl::SurfaceStyle::Default ,
                                                          const ContextSettings& settings = ContextSettings::Default() );
        
        ////////////////////////////////////////////////////////////
        /// \brief Creates an empty renderpath.
        ///
        ////////////////////////////////////////////////////////////
        virtual Shared < RenderPath > CreateRenderPath( const Weak < RenderWindow >& window ) const ;
        
        ////////////////////////////////////////////////////////////
        /// \brief Remove the given renderwindow.
        ///
        ////////////////////////////////////////////////////////////
        virtual void RemoveRenderWindow( const Weak < RenderWindow >& window );
        
    protected:
        
        ////////////////////////////////////////////////////////////
        /// \brief Adds the created RenderWindow to the driver.
        ///
        ////////////////////////////////////////////////////////////
        virtual void AddRenderWindow( const Shared < RenderWindow >& rw );
    };
}

#endif /* Driver_hpp */
