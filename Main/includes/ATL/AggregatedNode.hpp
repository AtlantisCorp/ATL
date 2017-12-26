//  ========================================================================  //
//
//  File    : ATL/AggregatedNode.hpp
//  Project : atlresource
//  Author  : Luk2010
//  Date    : 06/12/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#ifndef AggregatedNode_hpp
#define AggregatedNode_hpp

#include <ATL/Node.hpp>

namespace atl
{
    ////////////////////////////////////////////////////////////
    class AggregatedMaterial ;
    class AggregatedGroup ;
    
    ////////////////////////////////////////////////////////////
    /// \brief Hold informations about post-aggregation process.
    ///
    ////////////////////////////////////////////////////////////
    class AggregatedNode : public Node
    {
        ////////////////////////////////////////////////////////////
        Shared < AggregatedMaterial > m_material ; ///< Direct holding of the AggregatedMaterial.
        Shared < RenderCommand >      m_command  ; ///< RenderCommand for this node.
        Weak < AggregatedGroup >      m_group ;    ///< Group associated to this aggregated node.
        NodesBySubtype                m_lsnodes ;  ///< Nodes by Subtypes needed for this node.
        mutable Spinlock              m_spinlock ; ///< Access to shared pointers.
        
    public:
        
        ////////////////////////////////////////////////////////////
        AggregatedNode( const NodesBySubtype& lsnodes , const Shared < RenderCommand >& , const Weak < AggregatedMaterial >& );
        
        ////////////////////////////////////////////////////////////
        virtual ~AggregatedNode();
        
        ////////////////////////////////////////////////////////////
        virtual void SetRenderCommand( const Shared < RenderCommand >& command );
        
        ////////////////////////////////////////////////////////////
        virtual Shared < RenderCommand > GetRenderCommand() const ;
        
        ////////////////////////////////////////////////////////////
        virtual void SetMaterial( const Shared < AggregatedMaterial >& material );
        
        ////////////////////////////////////////////////////////////
        virtual Shared < AggregatedMaterial > GetMaterial() const ;
        
        ////////////////////////////////////////////////////////////
        /// \brief Launch Aggregation process by giving to lsnodes the
        /// material and rendercommand that will be used to aggregate
        /// everything together.
        ///
        /// Aggregation subsystem consist in launching 'Aggregate()' on
        /// every nodes held in 'm_lsnodes' property. Each of this node
        /// will aggregate its own content to this node's material and
        /// rendercommand (RenderCommand should be modified only under
        /// certain conditions). 
        ///
        ////////////////////////////////////////////////////////////
        virtual void Aggregation() const ;
        
        ////////////////////////////////////////////////////////////
        /// \brief Returns true if the given lsnodes map is equal to
        /// the one used by this AggregatedNode.
        ///
        /// It is used to retrieve an AggregatedNode for the specified
        /// lsnodes map in the specified group. Generally it is in the
        /// SCENE-UPDATE function of a creator node to determine weither
        /// it should create a new AggregatedNode for the determined group
        /// or not.
        ///
        /// \note 'group' should be the exact same parameter as the
        /// 'AggregatedGroup' given in 'Node::Update()' function's argument.
        ///
        ////////////////////////////////////////////////////////////
        virtual bool IsLsnodesEqual( const NodesBySubtype& lsnodes , const AggregatedGroup& group ) const ;
        
        ////////////////////////////////////////////////////////////
        /// \brief Changes the current group this node is affiliated
        /// with. If the node already is affiliated in another group,
        /// it will notifiate the group it is quitting it by calling
        /// 'AggregatedGroup::NotifyNodeQuit()'.
        ///
        /// \note It does not check if the given group registered this
        /// node as one of its children. Indeed, this function is called
        /// by 'AggregatedGroup::AppendNode' and should be the only one
        /// who calls it.
        ///
        ////////////////////////////////////////////////////////////
        virtual void SetParentGroup( const Shared < AggregatedGroup >& group );
    };
}

#endif /* AggregatedNode_hpp */
