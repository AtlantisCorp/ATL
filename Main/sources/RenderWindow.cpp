//  ========================================================================  //
//
//  File    : ATL/RenderWindow.cpp
//  Project : atlresource
//  Author  : Luk2010
//  Date    : 10/10/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //

#include <ATL/RenderWindow.hpp>
#include <ATL/Root.hpp>
#include <ATL/SurfaceEvent.hpp>

namespace atl
{
    ////////////////////////////////////////////////////////////
    RenderWindow::RenderWindow( const Weak < Surface >& surface , const Weak < Context >& context )
    : RenderTarget( context ) , m_surface( surface ) , m_context( context.lock() ) , m_displayed( false ) , m_slistened( false )
    , m_autoresize( true )
    {
        assert( !surface.expired() && "'surface' expired." );
        SetViewport({ surface.lock()->GetSize() , { 0 , 0 } });
    }
    
    ////////////////////////////////////////////////////////////
    RenderWindow::~RenderWindow()
    {
        auto surfacer = Root::Get().GetSurfacer();

        if ( !m_surface.expired() && !surfacer.expired() )
            surfacer.lock()->RemoveSurface( m_surface );
    }
    
    ////////////////////////////////////////////////////////////
    Weak < Surface > RenderWindow::GetSurface() const
    {
        return m_surface ;
    }
    
    ////////////////////////////////////////////////////////////
    void RenderWindow::AddSurfaceListener( const Shared < Listener >& listener )
    {
        if ( m_surface.expired() )
        {
            Root::Get().GetLogger().warn( "Trying to add a listener to a Surface but none has been added yet." );
            return ;
        }
        
        m_surface.lock()->AddListener( listener );
    }
    
    ////////////////////////////////////////////////////////////
    void RenderWindow::ResetSurfaceListeners()
    {
        if ( !m_surface.expired() )
        {
            m_surface.lock()->Emitter::Reset();
        }
    }
    
    ////////////////////////////////////////////////////////////
    void RenderWindow::ProcessEvents()
    {
        if ( !m_surface.expired() )
        {
            m_surface.lock()->ProcessEvents();
        }
    }
    
    ////////////////////////////////////////////////////////////
    bool RenderWindow::Closed( void ) const
    {
        if ( m_surface.expired() )
            return true ;
        return m_surface.lock()->Closed();
    }
    
    ////////////////////////////////////////////////////////////
    void RenderWindow::Show() const
    {
        if ( !m_surface.expired() )
            m_surface.lock()->Show();
    }
    
    ////////////////////////////////////////////////////////////
    void RenderWindow::Flush() const
    {
        if ( m_context )
        {
            m_context->Flush();
        }
    }
    
    ////////////////////////////////////////////////////////////
    void RenderWindow::Display()
    {
        Flush();
        ProcessEvents();
        
        if ( !m_slistened.load() )
        {
            using namespace std::placeholders ;
            auto callable = std::bind( []( const SurfaceResizeEvent& event , const Weak < RenderTarget >& wthis ) {
                
                if ( !wthis.expired() )
                {
                    auto sthis = std::static_pointer_cast < RenderWindow >( wthis.lock() );
                    
                    if ( sthis->ShouldAutoresize() )
                    sthis->SetViewport({ event.GetSize() , { 0 , 0 } });
                }
                
            } , _1 , shared_from_this() );
            m_surface.lock()->AddListener( CreateAutoListener < SurfaceResizeEvent >( callable ) );
            m_slistened.store( true );
        }
        
        if ( !m_displayed.load() )
        {
            m_displayed.store( true );
            m_surface.lock()->SendAsyncEvent < SurfaceFirstDisplayedEvent >( m_surface );
        }
    }
    
    ////////////////////////////////////////////////////////////
    Shared < VertexCommand > RenderWindow::CreateVertexCommand( const Vector < VertexComponent >& components ,
                                                                const SharedVector < CBuffer >& vcbuffers ,
                                                                uint32_t vcount ,
                                                                const Shared < CBuffer >& icbuffer ,
                                                                uint32_t icount ,
                                                                IndexType itype )
    {
        assert( m_context && "'m_context' is null." );
        
        Map < Shared < CBuffer > , Shared < Buffer > > vbuffers ;
        
        for ( const Shared < CBuffer >& cbuffer : vcbuffers )
        {
            auto vbuffer = m_context->CreateVertexBuffer( cbuffer->GetData() , cbuffer->GetSize() ).lock();
            assert( vbuffer && "'vbuffer' creation failed." );
            vbuffers[cbuffer] = vbuffer ;
        }
        
        if ( vbuffers.empty() )
            return nullptr ;
        
        Shared < VertexCommand > command = std::make_shared < VertexCommand >();
        assert( command && "'command' creation failed." );
        command->SetVertexCount( vcount );
        
        for ( const VertexComponent& component : components )
        {
            VertexComponent cpy = component ;
            auto cbuffer = cpy.GetCBuffer().lock();
            assert( cbuffer && "VertexComponent has invalid CBuffer." );
            cpy.SetBuffer( vbuffers.at(cbuffer) );
            command->AddVertexComponent( cpy );
        }
        
        if ( icbuffer && icount && itype != IndexType::Unknown )
        {
            Shared < Buffer > ibuffer = m_context->CreateIndexBuffer( icbuffer->GetData() , icbuffer->GetSize() ).lock();
            assert( ibuffer && "'ibuffer' creation failed." );
            command->SetIndexBuffer( ibuffer );
            command->SetIndexCount( icount );
            command->SetIndexType( itype );
        }
        
        return command ;
    }
    
    ////////////////////////////////////////////////////////////
    Shared < Program > RenderWindow::CreateProgram( const StringVector& shadfiles )
    {
        auto smimedb = Root::Get().GetMimeDatabase().lock();
        assert( smimedb && "'smimedb' is null." );
        auto smetaclasser = Root::Get().GetMetaclasser().lock();
        assert( smetaclasser && "'smetaclasser' is null." );
        assert( m_context && "'m_context' is null." );
        
        SharedVector < Shader > shaders ;
        
        for ( auto const& shadfile : shadfiles )
        {
            auto mime = smimedb->FindHigherForFile( Filename( shadfile ) );
            if ( mime.IsEmpty() )
                continue ;
            auto metaclass = smetaclasser->GetMetaclass( mime );
            if ( !metaclass )
                continue ;
            auto shader = std::static_pointer_cast < Shader >( metaclass->Create( false , shadfile , m_context ) );
            if ( shader )
                shaders.push_back( shader );
        }
        
        if ( shaders.empty() )
            return nullptr ;
        
        return CreateProgram( shaders );
    }
    
    ////////////////////////////////////////////////////////////
    Shared < Program > RenderWindow::CreateProgram( const SharedVector < Shader >& shaders )
    {
        assert( m_context && "'m_context' is null." );
        
        if ( shaders.empty() )
            return nullptr ;
        
        MutexLocker lck( m_mutex );
        return m_context->CreateProgram( shaders );
    }
    
    ////////////////////////////////////////////////////////////
    void RenderWindow::SetAutoresize( bool autoresize )
    {
        m_autoresize.store( autoresize );
    }
    
    ////////////////////////////////////////////////////////////
    bool RenderWindow::ShouldAutoresize() const
    {
        return m_autoresize.load();
    }
}
