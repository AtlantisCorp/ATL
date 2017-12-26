//  ========================================================================  //
//
//  File    : firstexample/main.cpp
//  Project : ATL/OSXWindow
//  Author  : Luk2010
//  Date    : 16/09/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#include <ATL/Root.hpp>
#include <ATL/SurfaceEvent.hpp>
#include <ATL/Key.hpp>
#include <ATL/LoadingQueue.hpp>
#include <ATL/Mesh.hpp>
#include <ATL/ErrorEvent.hpp>

using namespace atl ;

////////////////////////////////////////////////////////////
/// \brief Example Error handler.
///
/// Sends a message when a Metaclass does not succeed to create
/// a class. This class must be instanciated and added to the
/// global ErrorCenter, accessible with 'ErrorCenter::AddListener'.
///
////////////////////////////////////////////////////////////
class ExampleErrorListener : public Listener
{
    ////////////////////////////////////////////////////////////
    Logger m_logger ; ///< Logger used to log errors.
    
public:
    
    ////////////////////////////////////////////////////////////
    ExampleErrorListener( const Logger& logger ) : m_logger( logger )
    {
        
    }
    
    ////////////////////////////////////////////////////////////
    void ProceedEvent( const Shared < Event >& event )
    {
        if ( event -> Is < ExceptionErrorEvent >() )
        {
            auto eee = event -> To < ExceptionErrorEvent >();
            m_logger.warn( "Exception handled by ErrorCenter: " , eee->GetException().what() );
            m_logger.warn( "  Message = " , eee->GetMessage() );
            m_logger.warn( "  Error code = " , static_cast < unsigned long >( eee->GetError() ) );
        }
        
        else if ( event -> Is < ErrorEvent >() )
        {
            auto ee = event -> To < ErrorEvent >();
            m_logger.warn( "Error handled by ErrorCenter: " , ee->GetMessage() );
            m_logger.warn( "  Error code = " , static_cast < unsigned long >( ee->GetError() ) );
        }
    }
};

////////////////////////////////////////////////////////////
/// \brief Example listener for atl::Surface.
///
////////////////////////////////////////////////////////////
class ExampleSurfaceListener : public Listener
{
    ////////////////////////////////////////////////////////////
    Logger                  m_logger ;
    Weak < Surface >        m_surface ;
    Shared < LoadingQueue > m_loadqueue ;
    
public:
    
    ////////////////////////////////////////////////////////////
    Shared < RenderCommand > m_command ;
    Shared < Program >       m_program ;
    
public:
    
    ////////////////////////////////////////////////////////////
    ExampleSurfaceListener( const Weak < Surface >& surface , const Weak < RenderWindow >& renderwindow ) : m_logger( Root::Get().GetLogger() ) , m_surface( surface ) , m_loadqueue( nullptr )
    {
        m_loadqueue = std::make_shared < LoadingQueue >( renderwindow , []( LoadingContext& ctxt ){
            
            ExampleSurfaceListener* _this = (ExampleSurfaceListener*) ctxt.data ;
            ctxt.renderwindow.lock()->Begin();
            
            auto material = MaterialManager::Get()->Create();
            material.lock()->SetAmbient({ 0.2f , 0.2f , 0.2f , 1.0f });
            
            float pos [] = {
               -0.5f , -0.5f , 0.0f , 1.0f , 0.0f , 0.0f ,
                0.0f ,  0.5f , 0.0f , 0.0f , 1.0f , 0.0f ,
                0.5f , -0.5f , 0.0f , 0.0f , 0.0f , 1.0f
            };
            
            auto vertexbuffer = std::make_shared < CBuffer >( pos , 18 * sizeof( float ) );
            
            VertexComponent vertexcomponent( Attribute::Position1 , VertexComponent::Position3 ,
                                             6 * sizeof( float ) , 0 ,
                                             vertexbuffer );
            
            VertexComponent colorcomponent( Attribute::Color1 , VertexComponent::Color3 ,
                                            6 * sizeof( float ) , 3 * sizeof( float ) ,
                                            vertexbuffer );
            
            uint8_t indexes [] = { 0 , 1 , 2 };
            auto indexbuffer = std::make_shared < CBuffer >( indexes , 3 * sizeof( uint8_t ) );
            
            auto mesh = MeshManager::Get()->Create().lock();
            assert( mesh && "'mesh' is null." );
            
            mesh->AddVertexCBuffer( vertexbuffer );
            mesh->AddVertexComponent( vertexcomponent );
            mesh->AddVertexComponent( colorcomponent );
            mesh->SetVertexCount( 3 );
            
            mesh->SetIndexCBuffer( indexbuffer , 3 , IndexType::UI8 );
            mesh->SetMaterial( material );
            
            mesh->GenVertexCommands( ctxt.renderwindow );
            
            _this->m_command = std::make_shared < RenderCommand >( mesh->GetVertexCommands() , material );
            _this->m_command->AddConstParameter( ConstantParameter( ParameterValue( glm::mat4() ) , Alias::MatrixModel ) );
            
            auto context = ctxt.renderwindow.lock()->GetContext();
            assert( !context.expired() && "'context' is null." );
            
            auto vshader = context.lock()->GetDefaultShader( Stage::Vertex );
            assert( vshader && "'vshader' is null." );
            auto fshader = context.lock()->GetDefaultShader( Stage::Fragment );
            assert( fshader && "'fshader' is null." );
            
            _this->m_program = ctxt.renderwindow.lock()->CreateProgram({ vshader , fshader });
            assert( _this->m_program && "'prog' is null." );
            _this->m_program->GetVertexLayout().lock()->SetAttribute( Attribute::Position1 , "position" , VertexComponent::Position3 );
            _this->m_program->GetVertexLayout().lock()->SetAttribute( Attribute::Color1 , "color" , VertexComponent::Color3 );
            _this->m_command->SetProgram( _this->m_program );
            
            auto rendergroup = std::make_shared < RenderCommandGroup >();
            rendergroup->AddRenderCommand( _this->m_command );
            ctxt.renderwindow.lock()->AddRenderCommandGroup( rendergroup );
            
            // auto scene = SceneManager::Get().Create();
            // auto root  = scene -> GetRootPosition();
            // auto node  = root -> AddChild( scene -> CreateRenderNode( position , program , material , mesh ) );
            
            // auto camera = CameraManager::Get().Create();
            // auto graph  = scene -> CreateAndAddCameraGraph( camera );
            
            // scene -> StartAsync();
            
            auto group = Root::Get().GetDefaultObjectGroup();
            assert( !group.expired() && "Invalid default group." );
            
            // group.lock()->AddObject( graph );
            ctxt.renderwindow.lock()->AddObjectGroup( group );
            
            ctxt.renderwindow.lock()->End();
        } , this );
    }
    
    ////////////////////////////////////////////////////////////
    void ProceedEvent( const Shared < Event >& event )
    {
        if ( event->Is<SurfaceKeyDownEvent>() )
        {
            auto skde = event->To<SurfaceKeyDownEvent>();
            String text = skde->GetKey();
            
            if ( text == atl::Key::Escape )
            {
                m_logger.info( "Escape pressed: Closing surface." );
                m_surface.lock()->Close();
            }
        }
        
        else if ( event->Is < SurfaceFirstDisplayedEvent >() )
        {
            auto sfde = event->To < SurfaceFirstDisplayedEvent >();
            m_logger.info( "Surface displayed for the first time ! Loading example..." );
            
            assert( m_loadqueue && "LoadingQueue not initialized." );
            m_loadqueue->StartAsync();
            m_loadqueue->Wait();
            
            assert( m_loadqueue->IsFinished() && "Loading Queue had an error." );
            m_logger.info( "LoadingQueue loaded in " , m_loadqueue->GetPerformer().GetMillis() , "ms." );
        }
    }
};

////////////////////////////////////////////////////////////
int main(int argc, char ** argv)
{
    {
        atl::Root & root = atl::Root::Get().PlatformInit( argc , argv );
        root.Init();
        
        auto logger = root.GetLogger();
        logger.info( "Initialized Root (" , atl::Platform::Get().GetName() , ")." );
        logger.info( "Working directory: " , root.GetWorkingDirectory() );
        ErrorCenter::AddListener( std::make_shared < ExampleErrorListener >( logger ) );
        
        auto surfacer = root.GetSurfacer();
        assert( !surfacer.expired() && "Invalid surfacer provided." );
        logger.info( "Surfacer name: " , surfacer.lock()->GetName() );
        
        atl::VideoMode desktop = surfacer.lock()->GetDesktopVideoMode();
        assert( desktop.width && desktop.height && desktop.bitsperpixels && "Invalid Desktop Video Mode." );
        logger.info( "Desktop VideoMode: Width = " , desktop.width , " ; Height = " , desktop.height , " ; Bpp = " , desktop.bitsperpixels );
        
        auto driver = root.GetDriver();
        assert( !driver.expired() && "Invalid driver provided." );
        logger.info( "Driver name: " , driver.lock()->GetName() );
        
        auto contextsettings = ContextSettings::Default();
        contextsettings.multisampled = true ;
        
        auto renderwindow = driver.lock()->CreateRenderWindow( atl::VideoMode( 400 , 300 , desktop.bitsperpixels ) , "Example" , SurfaceStyle::Default , contextsettings );
        assert( !renderwindow.expired() && "Invalid renderwindow created." );
        renderwindow.lock()->AddSurfaceListener( std::make_shared < ExampleSurfaceListener >( renderwindow.lock()->GetSurface() , renderwindow ) );
        renderwindow.lock()->SetClearColor( Color4( 0.7f , 0.7f , 0.7f , 1.0f ) );
        renderwindow.lock()->Show();
        renderwindow.lock()->Display();
        
        auto path = driver.lock()->CreateRenderPath( renderwindow );
        assert( path && "Invalid RenderPath creation." );
        path->Easyloop();
        
        root.Reset();
    }
    
    Root::Destroy();
    
    return 0;
}
