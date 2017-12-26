//  ========================================================================  //
//
//  File    : ATL/RenderCommandGroup.cpp
//  Project : atlresource
//  Author  : Luk2010
//  Date    : 28/10/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#include <ATL/RenderCommandGroup.hpp>
#include <ATL/RenderTarget.hpp>

namespace atl
{
    ////////////////////////////////////////////////////////////
    RenderCommandGroup::RenderCommandGroup()
    {
        
    }
    
    ////////////////////////////////////////////////////////////
    RenderCommandGroup::~RenderCommandGroup()
    {
        
    }
    
    ////////////////////////////////////////////////////////////
    void RenderCommandGroup::AddRenderCommand( const Weak < RenderCommand >& command ,
                                               const RenderQueueCache& mode )
    {
        assert( !command.expired() && "Null command given." );
        auto scommand = command.lock();
        
        assert( !scommand->GetProgram().expired() && "RenderCommand has null program." );
        assert( !scommand->GetMaterial().expired() && "RenderCommand has null material." );
        
        auto pass = CreateOrGetRenderPass( scommand->GetProgram() );
        assert( pass && "Can't create RenderPass." );
        
        return pass->AddRenderCommand( scommand->GetMaterial() , command , mode );
    }
    
    ////////////////////////////////////////////////////////////
    void RenderCommandGroup::AddRenderCommands( const Weak < Program >& program ,
                                                const Weak < Material >& material ,
                                                const WeakVector < RenderCommand >& commands ,
                                                const RenderQueueCache& mode )
    {
        assert( !program.expired() && "Null program given." );
        assert( !material.expired() && "Null material given." );
        
        auto pass = CreateOrGetRenderPass( program );
        assert( pass && "'CreateRenderPass()' failed." );
        
        return pass->AddRenderCommands( material , commands , mode );
    }
    
    ////////////////////////////////////////////////////////////
    Shared < RenderPass > RenderCommandGroup::CreateOrGetRenderPass( const Weak < Program >& program )
    {
        assert( !program.expired() && "Null program given." );
        
        ProgramId id = program.lock()->GetId();
        assert( id > 0 && "Invalid Program ID." );
        
        MutexLocker lck( m_mutex );
        auto it = m_passbyprogid.find( id );
        
        if ( it != m_passbyprogid.end() )
        {
            return it->second.lock();
        }
        
        else
        {
            auto pass = std::make_shared < RenderPass >( program );
            assert( pass && "'std::make_shared<RenderPass>' failed." );
            
            m_passes.push_back( pass );
            m_passbyprogid[id] = pass ;
            return pass ;
        }
    }
    
    ////////////////////////////////////////////////////////////
    void RenderCommandGroup::Draw( const RenderTarget& target ) const
    {
        m_mutex.lock();
        auto tmppasses = m_passes ;
        m_mutex.unlock();
        
        auto scontext = target.GetContext().lock();
        assert( scontext && "'target' has no context." );
        
        auto cstparams = GetConstParameters();
        auto varparams = GetVarParameters();
        
        for ( auto pass : tmppasses )
        {
            auto wprogram = pass->GetProgram();
            assert( !wprogram.expired() && "RenderPass program expired." );
            auto program = wprogram.lock();
            
            program->Prepare( target );
            program->BindConstantParameters( cstparams );
            program->BindVaryingParameters( varparams );
            
            pass->Draw( *scontext , *program );
            pass->_ResetDynamicRenderQueues();
        }
    }
}
