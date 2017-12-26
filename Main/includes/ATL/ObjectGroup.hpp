//  ========================================================================  //
//
//  File    : ATL/ObjectGroup.hpp
//  Project : atlresource
//  Author  : Luk2010
//  Date    : 20/10/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#ifndef ObjectGroup_hpp
#define ObjectGroup_hpp

#include <ATL/StdIncludes.hpp>
#include <ATL/Object.hpp>

namespace atl
{
    ////////////////////////////////////////////////////////////
    class RenderTarget ;
    
    ////////////////////////////////////////////////////////////
    /// \brief Local identifier for a group.
    ///
    ////////////////////////////////////////////////////////////
    typedef unsigned long long ObjectGroupId ;
    
    ////////////////////////////////////////////////////////////
    /// \brief Defines a group of Object.
    ///
    /// Permits to associate objects into groups, which will be
    /// updated by the rendertarget that has this group. A group
    /// can be updated by more than one target to maintain its
    /// VertexCommands list in the rendertarget.
    ///
    ////////////////////////////////////////////////////////////
    class ObjectGroup : public std::enable_shared_from_this < ObjectGroup >
    {
        ////////////////////////////////////////////////////////////
        static IDGenerator < ObjectGroupId > s_generator ;
        
        ////////////////////////////////////////////////////////////
        Atomic < ObjectGroupId >     m_id ;        ///< Identifier of this group.
        Weak < ObjectGroup >         m_parent ;    ///< Parent group of this group, expired if it does not have any.
        SharedVector < ObjectGroup > m_subgroups ; ///< Subgroups.
        SharedVector < Object >      m_objects ;   ///< Objects in this group.
        mutable Mutex                m_mutex ;     ///< Mutex to access some datas (Vectors).
        
    public:
        
        ////////////////////////////////////////////////////////////
        ObjectGroup();
        
        ////////////////////////////////////////////////////////////
        virtual ~ObjectGroup();
        
        ////////////////////////////////////////////////////////////
        /// \brief Returns local ID of this group.
        ///
        ////////////////////////////////////////////////////////////
        ObjectGroupId GetId() const ;
        
        ////////////////////////////////////////////////////////////
        /// \brief Returns the parent group.
        ///
        ////////////////////////////////////////////////////////////
        Weak < ObjectGroup > GetParent() const ;
        
        ////////////////////////////////////////////////////////////
        /// \brief Changes the parent group.
        ///
        ////////////////////////////////////////////////////////////
        void SetParent( const Weak < ObjectGroup >& parent );
        
        ////////////////////////////////////////////////////////////
        /// \brief Returns the subgroups.
        ///
        ////////////////////////////////////////////////////////////
        WeakVector < ObjectGroup > GetSubGroups() const ;
        
        ////////////////////////////////////////////////////////////
        /// \brief Find a subgroup by its id.
        ///
        ////////////////////////////////////////////////////////////
        Weak < ObjectGroup > FindSubGroup( const ObjectGroupId& id ) const ;
        
        ////////////////////////////////////////////////////////////
        /// \brief Remove a subgroup.
        ///
        ////////////////////////////////////////////////////////////
        void RemoveSubGroup( const Weak < ObjectGroup >& subgroup );
        
        ////////////////////////////////////////////////////////////
        /// \brief Adds a subgroup.
        ///
        ////////////////////////////////////////////////////////////
        void AddSubGroup( const Shared < ObjectGroup >& subgroup );
        
        ////////////////////////////////////////////////////////////
        /// \brief Creates a subgroup.
        ///
        ////////////////////////////////////////////////////////////
        Weak < ObjectGroup > CreateSubGroup();
        
        ////////////////////////////////////////////////////////////
        /// \brief Removes every subgroups.
        ///
        ////////////////////////////////////////////////////////////
        void RemoveAllSubGroups();
        
        ////////////////////////////////////////////////////////////
        /// \brief Adds an object.
        ///
        ////////////////////////////////////////////////////////////
        void AddObject( const Shared < Object >& object );
        
        ////////////////////////////////////////////////////////////
        /// \brief Find an object by its id.
        ///
        ////////////////////////////////////////////////////////////
        Weak < Object > FindObject( const ObjectId& id ) const ;
        
        ////////////////////////////////////////////////////////////
        /// \brief Remove an object.
        ///
        ////////////////////////////////////////////////////////////
        void RemoveObject( const Weak < Object >& object );
        
        ////////////////////////////////////////////////////////////
        /// \brief Remove all objects.
        ///
        ////////////////////////////////////////////////////////////
        void RemoveAllObjects();
        
        ////////////////////////////////////////////////////////////
        /// \brief Clear subgroups, objects, parent.
        ///
        ////////////////////////////////////////////////////////////
        void Reset();
        
        ////////////////////////////////////////////////////////////
        /// \brief Updates every objects and subgroups to the given
        /// rendertarget.
        ///
        /// \param target     RenderTarget from which the update should be
        ///                   called from.
        /// \param lockupdate Flag indicating wether the ObjectGroup should
        ///                   call 'Begin()' and 'End()' function between
        ///                   two objects. It is true only when 'TargetLocking'
        ///                   is 'PerObject'.
        ///
        ////////////////////////////////////////////////////////////
        void Update( RenderTarget& target , bool lockupdate );
    };
}

#endif /* ObjectGroup_h */
