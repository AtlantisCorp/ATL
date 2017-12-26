//  ========================================================================  //
//
//  File    : ATL/Surface.hpp
//  Project : atlresource
//  Author  : Luk2010
//  Date    : 09/10/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //

#ifndef Surface_h
#define Surface_h

#include <ATL/StdIncludes.hpp>
#include <ATL/SurfaceHandle.hpp>
#include <ATL/SurfaceStyle.hpp>
#include <ATL/VideoMode.hpp>
#include <ATL/Listener.hpp>
#include <ATL/Size.hpp>
#include <ATL/Position.hpp>

namespace atl
{
    ////////////////////////////////////////////////////////////
    /// \brief Define an interface for a drawing surface.
    ///
    /// Surfacer is responsible for creating those objects. They must
    /// be creable before creating the Context object, which is created
    /// by the Driver.
    ///
    /// A Surface is then associated with a Context in a RenderWindow.
    /// This RenderWindow is used to draw and display things on the
    /// screen. Events from the underlying Surface object can be accessed
    /// using listeners. Event processing is done by calling 'ProcessEvents()'.
    ///
    /// \note
    /// The association between Context and Surface is not done in
    /// RenderWindow but in the implementation of Context::AssociateSurface().
    /// The Context associates the Surface using OS - dependent functions
    /// like glX, CGL, AGL, ... or event D3D11. This is why you can have
    /// more than one Driver, like WinGl3Driver, OSXGl3Driver, XCBGl3Driver,
    /// or one Gl3Driver that implements everything for each platform, but
    /// those drivers always use the same Surfacer to create their Surface.
    ///
    ////////////////////////////////////////////////////////////
    class Surface : public Emitter , public std::enable_shared_from_this < Surface >
    {
    public:
        
        ////////////////////////////////////////////////////////////
        /// \brief Assimilate the Surface.
        ///
        /// \param handle Underlying handle to assimilate the Surface.
        ///               The underlying surface will be controlled by
        ///               this object.
        ///
        ////////////////////////////////////////////////////////////
        Surface( SurfaceHandle handle );
        
        ////////////////////////////////////////////////////////////
        /// \brief Construct the Surface.
        ///
        /// \param mode VideoMode for the created surface.
        /// \param title Title for the created surface, if applicable.
        /// \param style Style for the created surface, if applicable.
        ///
        ////////////////////////////////////////////////////////////
        Surface( const VideoMode& mode , const String& title , Style style );
        
        ////////////////////////////////////////////////////////////
        virtual ~Surface();
        
        ////////////////////////////////////////////////////////////
        /// \brief Get the surface's title.
        ///
        ////////////////////////////////////////////////////////////
        virtual String GetTitle() const = 0 ;
        
        ////////////////////////////////////////////////////////////
        /// \brief Changes the surface title, if applicable.
        ///
        ////////////////////////////////////////////////////////////
        virtual void SetTitle( const String& title ) = 0 ;
        
        ////////////////////////////////////////////////////////////
        /// \brief Get the surface's size, in pixels.
        ///
        ////////////////////////////////////////////////////////////
        virtual atl::Size GetSize() const = 0 ;
        
        ////////////////////////////////////////////////////////////
        /// \brief Changes the surface's size, in pixels.
        ///
        /// \param size New size to apply.
        ///
        ////////////////////////////////////////////////////////////
        virtual void SetSize( const atl::Size& size ) = 0 ;
        
        ////////////////////////////////////////////////////////////
        /// \brief Moves the surface, if applicable, in pixels.
        ///
        /// \param pos New position, in pixels.
        ///
        ////////////////////////////////////////////////////////////
        virtual void Move( const Position& pos ) = 0 ;
        
        ////////////////////////////////////////////////////////////
        /// \brief Get the surface position's relative to screen, in
        /// pixels.
        ///
        ////////////////////////////////////////////////////////////
        virtual Position GetPosition() const = 0 ;
        
        ////////////////////////////////////////////////////////////
        /// \brief Process events and send them to registered listeners.
        ///
        ////////////////////////////////////////////////////////////
        virtual void ProcessEvents( void ) const = 0 ;
        
        ////////////////////////////////////////////////////////////
        /// \brief Return 'true' if the Surface is closed.
        ///
        ////////////////////////////////////////////////////////////
        virtual bool Closed( void ) const = 0 ;
        
        ////////////////////////////////////////////////////////////
        /// \brief Close the Surface.
        ///
        ////////////////////////////////////////////////////////////
        virtual void Close( void ) = 0 ;
        
        ////////////////////////////////////////////////////////////
        /// \brief Show the Surface.
        ///
        /// Must be called after creating the Surface using the Surfacer,
        /// because default behaviour does not show the surface right
        /// after creation.
        ///
        ////////////////////////////////////////////////////////////
        virtual void Show( void ) const = 0 ;
        
        ////////////////////////////////////////////////////////////
        /// \brief Hide the Surface.
        ///
        ////////////////////////////////////////////////////////////
        virtual void Hide( void ) const = 0 ;
        
        ////////////////////////////////////////////////////////////
        /// \brief Returns the virtually representing the concrete surface
        /// handle.
        ///
        ////////////////////////////////////////////////////////////
        virtual SurfaceHandle GetSystemHandle() const = 0 ;
    };
}

#endif /* Surface_h */
