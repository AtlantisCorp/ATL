//  ========================================================================  //
//
//  File    : ATL/Renderable.hpp
//  Project : atlresource
//  Author  : Luk2010
//  Date    : 21/10/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#ifndef Renderable_h
#define Renderable_h

#include <ATL/StdIncludes.hpp>
#include <ATL/Object.hpp>
#include <ATL/VertexCommand.hpp>

namespace atl
{
    ////////////////////////////////////////////////////////////
    /// \brief Defines an object holding VertexCommands to present
    /// to the target.
    ///
    ////////////////////////////////////////////////////////////
    class Renderable : public Object
    {
        ////////////////////////////////////////////////////////////
        SharedVector < VertexCommand > m_commands ; ///< Main VertexCommands of this renderable.
        Atomic < bool >                m_dirty ;    ///< Dirty flag. True on set, false on unset.
        mutable Mutex                  m_mutex ;    ///< Access to data.
        
    public:
        
        ////////////////////////////////////////////////////////////
        Renderable();
        
        ////////////////////////////////////////////////////////////
        virtual ~Renderable();
        
        ////////////////////////////////////////////////////////////
        /// \brief Create a new VertexCommand and add it to the
        /// renderable data.
        ///
        /// \return Newly created VertexCommand.
        ///
        ////////////////////////////////////////////////////////////
        virtual Weak < VertexCommand > CreateAndAddVertexCommand();
        
        ////////////////////////////////////////////////////////////
        /// \brief Add a VertexCommand to this renderable but does not
        /// set the dirty flag.
        ///
        ////////////////////////////////////////////////////////////
        virtual void AddVertexCommand( const Shared < VertexCommand >& command );
        
        ////////////////////////////////////////////////////////////
        /// \brief Remove the given VertexCommand but does not modify
        /// the dirty flag.
        ///
        ////////////////////////////////////////////////////////////
        virtual void RemoveVertexCommand( const Weak < VertexCommand >& command );
        
        ////////////////////////////////////////////////////////////
        /// \brief Remove the given VertexCommand to this renderable but
        /// does not modify the dirty flag.
        ///
        ////////////////////////////////////////////////////////////
        virtual void RemoveVertexCommand( const VertexCommandId& id );
        
        ////////////////////////////////////////////////////////////
        /// \brief Retrieve the VertexCommand designed with given id.
        ///
        ////////////////////////////////////////////////////////////
        virtual Weak < VertexCommand > GetVertexCommand( const VertexCommandId& id ) const ;
        
    protected:
        
        ////////////////////////////////////////////////////////////
        /// \brief Returns currently the commands in this renderable.
        ///
        /// This method can only be used by derived classes when implementing
        /// 'Object::Update'. In order to prevent multithread overhelm,
        /// the mutex is locked the less time needed only to copy the vector
        /// of VertexCommands. The VertexCommand's vector is guaranteed not
        /// to be modified during utilisation. 
        ///
        ////////////////////////////////////////////////////////////
        virtual SharedVector < VertexCommand > CopyVertexCommands() const ;
    };
}

#endif /* Renderable_h */
