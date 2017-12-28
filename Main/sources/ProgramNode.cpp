//  ========================================================================  //
//
//  File    : ATL/ProgramNode.cpp
//  Project : atlresource
//  Author  : Luk2010
//  Date    : 29/11/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#include <ATL/ProgramNode.hpp>
#include <ATL/RenderCommand.hpp>

namespace atl
{
    ////////////////////////////////////////////////////////////
    ProgramNode::ProgramNode( const Weak < atl::Program >& program )
    : DerivedNode < ProgramNode >( Node::Subtype::Program ) , m_program( program )
    {
        
    }
    
    ////////////////////////////////////////////////////////////
    ProgramNode::~ProgramNode()
    {
        
    }
    
    ////////////////////////////////////////////////////////////
    Weak < Program > ProgramNode::GetProgram() const
    {
        return m_program ;
    }
    
    ////////////////////////////////////////////////////////////
    void ProgramNode::SetProgram( const Weak < atl::Program >& program )
    {
        m_program = program ;
    }
    
    ////////////////////////////////////////////////////////////
    void ProgramNode::Aggregate( AggregatedMaterial& material , RenderCommand& command ) const
    {
        auto program  = command.GetProgram().lock();
        auto thisprog = m_program.lock();
        
        if ( program != thisprog )
        command.SetProgram( thisprog );
        
        DerivedNode < ProgramNode >::Aggregate( material , command );
    }
}
