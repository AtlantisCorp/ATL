//  ========================================================================  //
//
//  File    : ATL/AggregatedGroup.hpp
//  Project : atlresource
//  Author  : Luk2010
//  Date    : 10/12/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#ifndef AggregatedGroup_hpp
#define AggregatedGroup_hpp

#include <ATL/StdIncludes.hpp>
#include <ATL/AggregatedNode.hpp>

namespace atl
{
    ////////////////////////////////////////////////////////////
    /// \brief Groups AggregatedNodes into the same structure.
    ///
    /// An AggregatedGroup is created by a graph when making its
    /// SCENE-UPDATE phase (itself called by each rendertarget).
    /// As a SCENE-UPDATE is launched by a graph on each rendertarget
    /// that calls its update method, one AggregatedGroup is needed by
    /// rendertarget in a callable graph.
    ///
    /// An AggregatedGroup stores only Weak pointers to AggregatedNode,
    /// as it lets (and makes) the node's creator manage the lifetime of
    /// those nodes. A Creator node must retrieve the aggregated node from
    /// the pair { lsnodes , group } as a different aggregated group is
    /// given for different SCENE-UPDATE.
    ///
    ////////////////////////////////////////////////////////////
    class AggregatedGroup : public std::enable_shared_from_this < AggregatedGroup >
    {
        ////////////////////////////////////////////////////////////
        WeakVector < AggregatedNode > m_nodes ; ///< Nodes for this group.
        mutable Mutex                 m_mutex ; ///< Mutex to access data.
        
    public:
        
        ////////////////////////////////////////////////////////////
        AggregatedGroup();
        
        ////////////////////////////////////////////////////////////
        virtual ~AggregatedGroup();
        
        ////////////////////////////////////////////////////////////
        /// \brief Appends an AggregatedNode at the end of the list.
        /// It is equivalent to a 'push_back' method.
        ///
        /// \note It does not check if the node was already added to the
        /// node's list in this group. Please take a look at 'FindNode'
        /// for this purpose.
        ///
        ////////////////////////////////////////////////////////////
        virtual void AppendNode( const Shared < AggregatedNode >& node );
        
        ////////////////////////////////////////////////////////////
        /// \brief Finds an AggregatedNode by doing pointer compareason,
        /// and returns its Weak pointer.
        ///
        /// It can be used to ensure if an AggregatedNode is present in
        /// the group or not. If the returned weak pointer is expired,
        /// the desired node is not present and thus can be safely appended
        /// by using 'AppendNode'.
        ///
        ////////////////////////////////////////////////////////////
        virtual Weak < AggregatedNode > FindNode( const Shared < AggregatedNode >& node ) const ;
        
    protected:
        
        ////////////////////////////////////////////////////////////
        friend class AggregatedNode ;
        
        ////////////////////////////////////////////////////////////
        /// \brief Notifiate the group an AggregatedNode is destroyed.
        /// It does not modify the AggregatedNode but it does destroy the
        /// weak pointer associated to it.
        ///
        /// \note It is called by AggregatedNode in its destructor using
        /// std::shared_from_this() system. As Node destructor is called
        /// after AggregatedNode's one, it is guaranteed to have a valid
        /// Shared pointer at this point.
        ///
        ////////////////////////////////////////////////////////////
        virtual void NotifiateNodeDestroyed( const Shared < AggregatedNode >& node );
        
        ////////////////////////////////////////////////////////////
        /// \brief Notifiate the group an AggregatedNode is quitting the
        /// group (perhaps for another one).
        ///
        ////////////////////////////////////////////////////////////
        virtual void NotifiateNodeQuit( const Shared < AggregatedNode >& node );
    };
}

#endif /* AggregatedGroup_hpp */
