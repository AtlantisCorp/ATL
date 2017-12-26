//  ========================================================================  //
//
//  File    : ATL/Object.hpp
//  Project : atlresource
//  Author  : Luk2010
//  Date    : 20/10/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#ifndef Object_hpp
#define Object_hpp

#include <ATL/StdIncludes.hpp>
#include <ATL/IDGenerator.hpp>

namespace atl
{
    ////////////////////////////////////////////////////////////
    class RenderTarget ;
    class ObjectGroup ;
    
    ////////////////////////////////////////////////////////////
    /// \brief Local object identifier.
    ///
    ////////////////////////////////////////////////////////////
    typedef unsigned long long ObjectId ;
    
    ////////////////////////////////////////////////////////////
    /// \brief Defines a renderable object.
    ///
    /// An object is 'renderable' when it can maintain a list of
    /// VertexCommands into a rendertarget, calling its 'Update()'
    /// method to perform this task.
    ///
    /// An object should never load its content during update, but
    /// instead use the LoadingQueue system.
    ///
    ////////////////////////////////////////////////////////////
    class Object
    {
        ////////////////////////////////////////////////////////////
        friend class ObjectGroup ;
        
        ////////////////////////////////////////////////////////////
        static IDGenerator < ObjectId > s_generator ;
        
        ////////////////////////////////////////////////////////////
        Atomic < ObjectId >  m_id ;    ///< Local id.
        Weak < ObjectGroup > m_group ; ///< Current object's group.
        
    public:
        
        ////////////////////////////////////////////////////////////
        Object();
        
        ////////////////////////////////////////////////////////////
        virtual ~Object();
        
        ////////////////////////////////////////////////////////////
        ObjectId GetId() const ;
        
        ////////////////////////////////////////////////////////////
        /// \brief Updates the VertexCommands in the rendertarget.
        ///
        ////////////////////////////////////////////////////////////
        virtual void Update( RenderTarget& target ) = 0 ;
        
        ////////////////////////////////////////////////////////////
        /// \brief Returns current group.
        ///
        ////////////////////////////////////////////////////////////
        virtual Weak < ObjectGroup > GetGroup() const ;
        
    protected:
        
        ////////////////////////////////////////////////////////////
        /// \brief Called by ObjectGroup::AddObject() to set the current
        /// object's group and by ObjectGroup::RemoveObject() to unset
        /// the current object's group.
        ///
        ////////////////////////////////////////////////////////////
        virtual void SetGroup( const Weak < ObjectGroup >& group );
    };
}

#endif /* Object_h */
