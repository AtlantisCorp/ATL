//  ========================================================================  //
//
//  File    : ATL/Root.cpp
//  Project : atlresource
//  Author  : Luk2010
//  Date    : 17/09/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#include <ATL/Root.hpp>
#include <ATL/Platform.hpp>
#include <ATL/EventQueue.hpp>

namespace atl
{
    ////////////////////////////////////////////////////////////
    Root::Root()
    {
        iMimeDb       = std::make_shared < MimeDatabase >();
        MimeDatabase::Set( iMimeDb );
        
        iChannel      = std::make_shared < ThreadedCoutChannel >();
        iPluginDb     = std::make_shared < PluginDatabase >();
        iDefaultGroup = std::make_shared < ObjectGroup >();
        
        iMetaclasser  = std::make_shared < Metaclasser >();
        Metaclasser::Set( iMetaclasser );
        
        iMaterialManager = std::make_shared < MaterialManager >();
        MaterialManager::Set( iMaterialManager );
        
        iMeshManager = std::make_shared < MeshManager >();
        MeshManager::Set( iMeshManager );
        
        iDriver.reset();
        iDontSaveConfigFile = false ;
        iSurfacer.reset();
    }

    ////////////////////////////////////////////////////////////
    Root::~Root()
    {
        RemoveAllPlugins();
        
        if ( !iDontSaveConfigFile )
        {
            SaveConfigFile();
        }
        
        MeshManager::Set( nullptr );
        MaterialManager::Set( nullptr );
        Metaclasser::Set( nullptr );
        MimeDatabase::Set( nullptr );
    }

    ////////////////////////////////////////////////////////////
    Weak < MimeDatabase > Root::GetMimeDatabase() const
    {
        return iMimeDb ;
    }

    ////////////////////////////////////////////////////////////
    Weak < PluginDatabase > Root::GetPluginDatabase() const
    {
        return iPluginDb ;
    }

    ////////////////////////////////////////////////////////////
    Weak < Driver > Root::GetDriver() const
    {
        return iDriver ;
    }

    ////////////////////////////////////////////////////////////
    Logger Root::GetLogger() const
    {
        return Logger( iChannel );
    }

    ////////////////////////////////////////////////////////////
    void Root::SetDefaultChannel(const Shared<atl::Channel> &channel)
    {
        iChannel = channel ;
    }

    ////////////////////////////////////////////////////////////
    void Root::Reset()
    {
        RemoveAllPlugins();
        
        iMimeDb       = std::make_shared < MimeDatabase >();
        MimeDatabase::Set( iMimeDb );
        
        iChannel      = std::make_shared < ThreadedCoutChannel >();
        iPluginDb     = std::make_shared < PluginDatabase >();
        iDefaultGroup = std::make_shared < ObjectGroup >();
        
        iMetaclasser  = std::make_shared < Metaclasser >();
        Metaclasser::Set( iMetaclasser );
        
        iMaterialManager = std::make_shared < MaterialManager >();
        MaterialManager::Set( iMaterialManager );
        
        iMeshManager = std::make_shared < MeshManager >();
        MeshManager::Set( iMeshManager );
        
        iDriver.reset();
        iDontSaveConfigFile = false ;
        iSurfacer.reset();
    }

    ////////////////////////////////////////////////////////////
    void Root::InstallPlugin(const Shared<atl::Plugin> &plugin)
    {
        assert( plugin && "Invalid Plugin." );

        iPluginDb -> Add( plugin );

        plugin -> Lock();

        iMimeDb -> AddTypes( plugin -> GetMimeTypes() );

        plugin -> Unlock();
    }

    ////////////////////////////////////////////////////////////
    void Root::UninstallPlugin(const Shared<atl::Plugin> &plugin)
    {
        assert( plugin && "Invalid Plugin." );

        plugin -> Lock();

        iMimeDb -> RemoveTypes( plugin -> GetMimeTypes() );

        plugin -> Unlock();
    }

    ////////////////////////////////////////////////////////////
    void Root::RemoveAllPlugins()
    {
        for ( auto plugin : iPluginDb -> GetPlugins() )
        {
            UninstallPlugin( plugin );
        }

        iPluginDb -> Reset();
    }

    ////////////////////////////////////////////////////////////
    void Root::InstallDriver( const Shared < Driver >& driver )
    {
        assert( driver && "Bad Driver given (null). " );
        assert( !iDriver && "Driver already installed." );
        iDriver = driver ;
    }

    ////////////////////////////////////////////////////////////
    void Root::LoadPluginDirectory(const atl::Filename &fdir)
    {
        if ( fdir.GetPath().empty() )
            return ;

        DIR* dir = opendir( fdir.GetPath().data() );
        if ( !dir )
            return ;

        struct dirent* ent = readdir( dir ) ;

        while ( ent != NULL )
        {
            if ( String( ent -> d_name ) == "."
                || String( ent -> d_name ) == ".." )
            {
                ent = readdir( dir );
                continue ;
            }

            String fullpath = fdir.GetPath() + GetPathSeparator() + ent -> d_name ;
            Logger( iChannel ).log( "Loading plugin path: " , fullpath );

            iPluginDb -> LoadDynlib( fullpath );
            ent = readdir( dir );
        }

        closedir( dir );
    }

    ////////////////////////////////////////////////////////////
    const String Root::GetPathSeparator() const
    {
        return "/" ;
    }

    ////////////////////////////////////////////////////////////
    void Root::LoadSimpleMimeDatabase(const String &filename)
    {
        iMimeDb -> LoadSimpleMimeDatabase( filename );
    }

    ////////////////////////////////////////////////////////////
    Root& Root::PlatformInit( int argc , char** argv )
    {
        // Initializes platform.
        
        Platform& platform = Platform::Get();
        assert( platform.Init() && "Platform initialization failed." );
        
        // Initializes the main event queue.

        EventQueue& mainqueue = EventQueue::GetMainQueue();
        mainqueue.Run();
        assert( mainqueue.Running() && "Can't run Event Main Queue." );
        
        // Initializes default platform config.
        
        iSpinlock.lock();
        
        iConfig.surfacerlib = platform.GetDefaultSurfacer();
        iConfig.driverlib = platform.GetDefaultDriver();
        iConfig.autoloadpath = platform.GetDefaultAutoload();
        
        iSpinlock.unlock();
        
        // Try to load a configuration file 'config.atl' at root working directory.
        
        LoadConfigFile();
        
        // Parse command line args. Notice we skip the first arg as it should be the
        // executable invokation.
        
        StringVector args ;
        
        for ( int i = 1 ; i < argc ; i++ )
            args.push_back( argv[i] );
        
        iSpinlock.lock();
        
        for ( int i = 0 ; i < args.size() ; i++ )
        {
            if ( args[i] == "--surfacerlib" && i+1 < args.size() )
            {
                iConfig.surfacerlib = args[++i];
            }
            
            else if ( args[i] == "--driverlib" && i+1 < args.size() )
            {
                iConfig.driverlib = args[++i];
            }
            
            else if ( args[i] == "--autoloadpath" && i+1 < args.size() )
            {
                iConfig.autoloadpath = args[++i];
            }
            
            else
            {
                GetLogger().warn( "Unknown parsing arg: " , args[i] );
            }
        }
        
        iSpinlock.unlock();

        return *this ;
    }
    
    ////////////////////////////////////////////////////////////
    bool Root::Init( void )
    {
        // Try to load Surfacer.
        
        iSpinlock.lock();
        Filename surfacerfile( iConfig.surfacerlib );
        iSpinlock.unlock();
        
        surfacerfile.SetPath( String("lib") + surfacerfile.GetPath() + "." + DYNLIB_EXTENSION );
        GetLogger().info( "Loading Surfacer lib: " , surfacerfile.GetPath() );
        
        if ( iPluginDb -> LoadDynlib( surfacerfile ).expired() )
        {
            GetLogger().warn( "Can't load Surfacer lib: " , surfacerfile.GetPath() );
            return false ;
        }
        
        // Try to load Driver.
        
        iSpinlock.lock();
        Filename driverfile( iConfig.driverlib );
        iSpinlock.unlock();
        
        driverfile.SetPath( String("lib") + driverfile.GetPath() + "." + DYNLIB_EXTENSION );
        GetLogger().info( "Loading Driver lib: " , driverfile.GetPath() );
        
        if ( iPluginDb -> LoadDynlib( driverfile ).expired() )
        {
            GetLogger().warn( "Can't load Driver lib: " , driverfile.GetPath() );
            return false ;
        }
        
        // Try to load plugin directory.
        
        iSpinlock.lock();
        Filename autoloadfile( iConfig.autoloadpath );
        iSpinlock.unlock();
        
        LoadPluginDirectory( autoloadfile.GetPath() );
        
        return true ;
    }
    
    ////////////////////////////////////////////////////////////
    String Root::GetWorkingDirectory() const
    {
        char buf [ PATH_MAX ];
        memset( buf , 0 , PATH_MAX );
        assert( getcwd( buf , PATH_MAX ) );
        return String( buf );
    }
    
    ////////////////////////////////////////////////////////////
    void Root::SetWorkingDirectory( const String& cwd )
    {
        assert( !chdir( cwd.data() ) );
    }
    
    ////////////////////////////////////////////////////////////
    void Root::SetDontSaveConfigFile( bool value )
    {
        Spinlocker lck( iSpinlock );
        iDontSaveConfigFile = value ;
    }
    
    ////////////////////////////////////////////////////////////
    void Root::SaveConfigFile()
    {
        iSpinlock.lock();
        ConfigFile cfg = iConfig ;
        iSpinlock.unlock();
        
        std::ofstream stream( "config.atl" , std::ios::out );
        assert( stream && "Invalid stream opening." );
        
        stream << "surfacerlib : " << cfg.surfacerlib << std::endl ;
        stream << "driverlib : "   << cfg.driverlib << std::endl ;
        stream << "autoload : "    << cfg.autoloadpath << std::endl ;
        
        stream.close();
        GetLogger().info( "Written Config file ('config.atl')." );
    }
    
    ////////////////////////////////////////////////////////////
    void Root::LoadConfigFile()
    {
        iSpinlock.lock();
        ConfigFile cfg = iConfig ;
        iSpinlock.unlock();
        
        std::ifstream stream( "config.atl" , std::ios::in );
        
        if ( !stream )
        {
            GetLogger().warn( "'config.atl' is not present and will be generated at closeup." );
            GetLogger().warn( "Default config values are used." );
            return ;
        }
        
        String line ;
        while( std::getline( stream , line ) )
        {
            std::istringstream iss( line );
            String key , point , value ;
            
            iss >> key >> point >> value ;
            assert( point == ":" && "Invalid processing token." );
            
            if ( key == "surfacerlib" ) {
                cfg.surfacerlib = value ;
            }
            
            else if ( key == "driverlib" ) {
                cfg.driverlib = value ;
            }
            
            else if ( key == "autoload" ) {
                cfg.autoloadpath = value ;
            }
            
            else {
                GetLogger().warn( "Invalid token processed: " , key , " => " , value );
            }
        }
        
        stream.close();
        
        iSpinlock.lock();
        iConfig = cfg ;
        iSpinlock.unlock();
        
        GetLogger().info( "Processed Config file ('config.atl')." );
    }
    
    ////////////////////////////////////////////////////////////
    Root::ConfigFile Root::GetConfigFile() const
    {
        Spinlocker lck( iSpinlock );
        return iConfig ;
    }
    
    ////////////////////////////////////////////////////////////
    void Root::SetConfigFile( const ConfigFile& cfg )
    {
        Spinlocker lck( iSpinlock );
        iConfig = cfg ;
    }
    
    ////////////////////////////////////////////////////////////
    Weak < Surfacer > Root::GetSurfacer() const
    {
        return iSurfacer ;
    }
    
    ////////////////////////////////////////////////////////////
    void Root::InstallSurfacer( const Shared < Surfacer >& surfacer )
    {
        assert( surfacer && "Invalid surfacer provided." );
        assert( !iSurfacer && "Surfacer already installed." );
        iSurfacer = surfacer ;
    }
    
    ////////////////////////////////////////////////////////////
    WeakVector < Surface > Root::GetSurfaces( void ) const
    {
        assert( iSurfacer && "Surfacer invalid/null." );
        return iSurfacer->GetSurfaces();
    }
    
    ////////////////////////////////////////////////////////////
    Weak < ObjectGroup > Root::GetDefaultObjectGroup() const
    {
        return iDefaultGroup ;
    }
    
    ////////////////////////////////////////////////////////////
    Weak < Metaclasser > Root::GetMetaclasser() const
    {
        return iMetaclasser ;
    }
    
    ////////////////////////////////////////////////////////////
    Weak < MaterialManager > Root::GetMaterialManager() const
    {
        return iMaterialManager ;
    }
    
    ////////////////////////////////////////////////////////////
    Weak < MeshManager > Root::GetMeshManager() const
    {
        return iMeshManager ;
    }
}
