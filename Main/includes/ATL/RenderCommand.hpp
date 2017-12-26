//  ========================================================================  //
//
//  File    : ATL/RenderCommand.hpp
//  Project : atlresource
//  Author  : Luk2010
//  Date    : 28/10/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#ifndef RenderCommand_hpp
#define RenderCommand_hpp

#include <ATL/StdIncludes.hpp>
#include <ATL/IDGenerator.hpp>
#include <ATL/VertexCommand.hpp>
#include <ATL/ParameterGroup.hpp>

namespace atl
{
    ////////////////////////////////////////////////////////////
    class Material ;
    class Program ;
    class RenderCommandGroup ;
    
    ////////////////////////////////////////////////////////////
    /// \brief Local id.
    ///
    ////////////////////////////////////////////////////////////
    typedef unsigned long long RenderCommandId ;
    
    ////////////////////////////////////////////////////////////
    /// \brief Groups VertexCommands for specific user-defined
    /// parameters for the current bound program.
    ///
    /// A render command is associated to a render command group,
    /// that can be associated to one or more targets. When the
    /// target updates itself, it will send to objects the 'update'
    /// call. RenderCommands inside the object might insert themself
    /// into their parent group if they want to, for example when they
    /// have been modified, or if they are stored in dynamic render queues.
    ///
    /// A render command group is associated to one or more targets,
    /// but different objects might update different targets with the
    /// same render command group. In that purpose, a default render
    /// command group is available, reachable with 'Root::GetDefaultRenderCommandGroup()'.
    /// This render command group is not associated to a new render target,
    /// you must use 'RenderTarget::AddRenderCommandGroup()'.
    ///
    ////////////////////////////////////////////////////////////
    class RenderCommand : public ParameterGroup
    {
        ////////////////////////////////////////////////////////////
        friend class RenderCommandGroup ;
        
        ////////////////////////////////////////////////////////////
        static IDGenerator < RenderCommandId > s_generator ;
        
        ////////////////////////////////////////////////////////////
        Atomic < RenderCommandId >             m_id ;          ///< Local id.
        mutable Mutex                          m_mutex ;       ///< Acces all data.
        SharedVector < VertexCommand >         m_commands ;    ///< VertexCommand in this rendercommand.
        Weak < Material >                      m_material ;    ///< Material associated to this render command (optional).
        Weak < Program >                       m_program ;     ///< Program associated to this render command (optional).
        Weak < RenderCommandGroup >            m_parentgroup ; ///< RenderCommandGroup associated to this render command.
        
    public:
        
        ////////////////////////////////////////////////////////////
        RenderCommand();
        
        ////////////////////////////////////////////////////////////
        RenderCommand( const Shared < VertexCommand >& command ,
                       const Weak < Material >& material = Weak < Material >() ,
                       const Weak < Program >& program = Weak < Program >() );
        
        ////////////////////////////////////////////////////////////
        RenderCommand( const SharedVector < VertexCommand >& command ,
                       const Weak < Material >& material = Weak < Material >() ,
                       const Weak < Program >& program = Weak < Program >() );
        
        ////////////////////////////////////////////////////////////
        virtual ~RenderCommand();
        
        ////////////////////////////////////////////////////////////
        RenderCommandId GetId() const ;
        
        ////////////////////////////////////////////////////////////
        /// \brief Adds a VertexCommand to this RenderCommand.
        ///
        /// The VertexCommand will be ready to be drawed by a Driver
        /// using this RenderCommand Material and Program.
        ///
        ////////////////////////////////////////////////////////////
        virtual void AddVertexCommand( const Shared < VertexCommand >& command );
        
        ////////////////////////////////////////////////////////////
        /// \brief Adds a group of vertex command to this RenderCommand.
        ///
        ////////////////////////////////////////////////////////////
        virtual void AddVertexCommands( const SharedVector < VertexCommand >& commands );
        
        ////////////////////////////////////////////////////////////
        /// \brief Resets vertex commands in this render command.
        ///
        ////////////////////////////////////////////////////////////
        virtual void ResetVertexCommands();
        
        ////////////////////////////////////////////////////////////
        /// \brief Returns the material associated to this rendercommand.
        ///
        ////////////////////////////////////////////////////////////
        virtual Weak < Material > GetMaterial() const ;
        
        ////////////////////////////////////////////////////////////
        /// \brief Returns the program associated to this rendercommand.
        ///
        ////////////////////////////////////////////////////////////
        virtual Weak < Program > GetProgram() const ;
        
        ////////////////////////////////////////////////////////////
        /// \brief Returns the parent render command group if this
        /// command has been associated to a group.
        ///
        ////////////////////////////////////////////////////////////
        Weak < RenderCommandGroup > GetParentGroup() const ;
        
        ////////////////////////////////////////////////////////////
        /// \brief Changes the program to given one.
        ///
        /// It should not be used while the rendercommand has already
        /// been set in a rendercommand group. However, considering that
        /// dynamic renderqueues must be re-updated each frame, changing
        /// program's rendercommand are automatically managed.
        ///
        ////////////////////////////////////////////////////////////
        virtual void SetProgram( const Weak < Program >& program );
        
        ////////////////////////////////////////////////////////////
        /// \brief Returns every vertexcommands in this rendercommand.
        ///
        ////////////////////////////////////////////////////////////
        virtual SharedVector < VertexCommand > GetVertexCommands() const ;
    };
}

#endif /* RenderCommand_hpp */
