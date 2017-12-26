//  ========================================================================  //
//
//  File    : ATL/ProgramNode.hpp
//  Project : atlresource
//  Author  : Luk2010
//  Date    : 29/11/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#ifndef ProgramNode_hpp
#define ProgramNode_hpp

#include <ATL/DerivedNode.hpp>
#include <ATL/Program.hpp>

namespace atl
{
    ////////////////////////////////////////////////////////////
    /// \brief Store and aggregate a specific Program in the aggregation
    /// chain.
    ///
    /// Wen aggregating, this node change the program used by the
    /// render command. Last node of this type found is the actual
    /// program that will be used by the aggregated node.
    ///
    /// A Program node should be available depending on the node
    /// storage strategy you choose. Normally, no inheritance is
    /// allowed and one program node should be available for one
    /// mesh/material nodes couple. However, another node strategy
    /// would be to englobate mesh/material elements in subgroups,
    /// all differenciated by their program. This way if no program
    /// is specified, the parent program will be used to render them.
    ///
    ////////////////////////////////////////////////////////////
    class ProgramNode : public DerivedNode < ProgramNode >
    {
        ////////////////////////////////////////////////////////////
        Weak < Program > m_program ; ///< Program stored.
        
    public:
        
        ////////////////////////////////////////////////////////////
        ProgramNode( const Weak < Program >& program );
        
        ////////////////////////////////////////////////////////////
        virtual ~ProgramNode();
        
        ////////////////////////////////////////////////////////////
        /// \brief Changes program used by this node.
        ///
        ////////////////////////////////////////////////////////////
        virtual void SetProgram( const Weak < Program >& program );
        
        ////////////////////////////////////////////////////////////
        virtual Weak < Program > GetProgram() const ;
        
        ////////////////////////////////////////////////////////////
        /// \brief Aggregates the program to the given rendercommand.
        ///
        /// If the given command's program is equal to this program,
        /// the command is left untouched.
        ///
        /// \note Aggregation is then passed to parent's routine.
        ///
        ////////////////////////////////////////////////////////////
        virtual void Aggregate( AggregatedMaterial& , RenderCommand& ) const ;
    };
}

#endif /* ProgramNode_hpp */
