//  ========================================================================  //
//
//  File    : Gl3Driver/Gl3Driver.h
//  Project : ATL/Gl3Driver
//  Author  : Luk2010
//  Date    : 15/10/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#ifndef Gl3Driver_h
#define Gl3Driver_h

#include <Gl3Driver/Gl3Includes.h>
#include <ATL/Driver.hpp>
using namespace atl ;

////////////////////////////////////////////////////////////
/// \brief Specialization of atl::Driver for OpenGL3.
///
////////////////////////////////////////////////////////////
class Gl3Driver : public atl::Driver
{
public:
    
    ////////////////////////////////////////////////////////////
    Gl3Driver();
    
    ////////////////////////////////////////////////////////////
    virtual ~Gl3Driver();
    
    ////////////////////////////////////////////////////////////
    /// \brief Get the driver's readable name.
    ///
    ////////////////////////////////////////////////////////////
    virtual String GetName() const ;
    
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
                                                      const ContextSettings& settings = ContextSettings::Default() );
    
    ////////////////////////////////////////////////////////////
    /// \brief Draw the given VertexCommand.
    /// \see atl::Driver::DrawVertexCommand.
    ///
    /// \param command VertexCommand to draw (Can't be expired).
    ///
    ////////////////////////////////////////////////////////////
    virtual void DrawVertexCommand( const Weak < VertexCommand >& command ) const ;
    
    ////////////////////////////////////////////////////////////
    virtual void DrawRenderCommand( const Weak < RenderCommand >& command , const Program& program ) const ;
};

#endif /* Gl3Driver_h */
