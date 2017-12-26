//  ========================================================================  //
//
//  File    : ATL/RenderCommandGroup.hpp
//  Project : atlresource
//  Author  : Luk2010
//  Date    : 28/10/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#ifndef RenderCommandGroup_hpp
#define RenderCommandGroup_hpp

#include <ATL/StdIncludes.hpp>
#include <ATL/RenderCommand.hpp>
#include <ATL/ParameterGroup.hpp>
#include <ATL/RenderPass.hpp>

namespace atl
{
    ////////////////////////////////////////////////////////////
    class RenderTarget ;
    
    ////////////////////////////////////////////////////////////
    /// \brief Organizes RenderCommand into passes (by program) and
    /// render queues (by material).
    ///
    /// When a RenderCommand is added to this group, it is filtered
    /// using a three-way insertion method: by program, by material
    /// and by caching mode (static vs dynamic).
    ///
    /// \see RenderPass, RenderQueue, RenderCommand
    ///
    ////////////////////////////////////////////////////////////
    class RenderCommandGroup : public ParameterGroup
    {
        ////////////////////////////////////////////////////////////
        typedef Map < ProgramId , Weak < RenderPass > > RenderPassByProgId ;
        
        ////////////////////////////////////////////////////////////
        SharedVector < RenderPass >  m_passes ;       ///< Passes held for this target.
        RenderPassByProgId           m_passbyprogid ; ///< Passes by program id.
        mutable Mutex                m_mutex ;        ///< Local mutex.
        
    public:
        
        ////////////////////////////////////////////////////////////
        RenderCommandGroup();
        
        ////////////////////////////////////////////////////////////
        virtual ~RenderCommandGroup();
        
        ////////////////////////////////////////////////////////////
        /// \brief Adds a render command by selecting its pass and
        /// render queue.
        ///
        /// \param commands The RenderCommand to add.
        /// \param mode     Select the renderqueues to look in the renderpass:
        ///                 the renderpass classifies the renderqueues into two
        ///                 separate arrays for simplification of the implementation.
        ///                 Weither you select Static or Dynamic is your choice.
        ///
        ////////////////////////////////////////////////////////////
        virtual void AddRenderCommand( const Weak < RenderCommand >& command ,
                                       const RenderQueueCache& mode = RenderQueueCache::Static );
        
        ////////////////////////////////////////////////////////////
        /// \brief Adds more than one render command by selecting their
        /// pass and renderqueue.
        ///
        /// \note As each render command given here might have different
        /// program and material, it is assumed the given program and the
        /// given material are commun for each render command.
        ///
        /// \param program  Primary factor of selection for the RenderCommand:
        ///                 based upon the program used the correct renderpass
        ///                 is selected.
        /// \param material Secondary factor of selection for the
        ///                 RenderCommand: based in the renderpass to select
        ///                 the correct renderqueue.
        /// \param commands The RenderCommand batch to add.
        /// \param mode     Select the renderqueues to look in the renderpass:
        ///                 the renderpass classifies the renderqueues into two
        ///                 separate arrays for simplification of the implementation.
        ///                 Weither you select Static or Dynamic is your choice.
        ///
        ////////////////////////////////////////////////////////////
        virtual void AddRenderCommands( const Weak < Program >& program ,
                                        const Weak < Material >& material ,
                                        const WeakVector < RenderCommand >& commands ,
                                        const RenderQueueCache& mode = RenderQueueCache::Static );
        
        ////////////////////////////////////////////////////////////
        /// \brief Create or Get the renderpass for given program.
        ///
        ////////////////////////////////////////////////////////////
        virtual Shared < RenderPass > CreateOrGetRenderPass( const Weak < Program >& program );
        
        ////////////////////////////////////////////////////////////
        /// \brief Draw the renderpasses in this group in the given
        /// target's context.
        ///
        ////////////////////////////////////////////////////////////
        virtual void Draw( const RenderTarget& target ) const ;
    };
}

#endif /* RenderCommandGroup_hpp */
