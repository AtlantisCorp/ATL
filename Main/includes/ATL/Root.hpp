//  ========================================================================  //
//
//  File    : ATL/Root.hpp
//  Project : atlresource
//  Author  : Luk2010
//  Date    : 17/09/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#ifndef Root_hpp
#define Root_hpp

#include <ATL/StdIncludes.hpp>

#include <ATL/Logger.hpp>
#include <ATL/CoutChannel.hpp>
#include <ATL/Plugin.hpp>
#include <ATL/Driver.hpp>
#include <ATL/Filename.hpp>
#include <ATL/Surfacer.hpp>
#include <ATL/Metaclasser.hpp>
#include <ATL/MimeDatabase.hpp>
#include <ATL/MaterialManager.hpp>
#include <ATL/MeshManager.hpp>

namespace atl
{
    class Root : public Singleton < Root >
    {
    public:
        
        ////////////////////////////////////////////////////////////
        /// \brief Defines what's can be inside a configuration file.
        ///
        /// \note When parsing command line args, Root sees args with
        /// the same name as the objects in this structure. For example,
        /// you can pass '--surfacerlib' as option to set 'surfacerlib'
        /// file of this structure.
        ///
        /// At startup, Root will either create the config file from
        /// default one, or load it from 'config.atl' file. At closeup,
        /// Root always tries to write this file to disk, except if
        /// 'iDontSaveConfigFile' is set to true.
        ///
        ////////////////////////////////////////////////////////////
        struct ConfigFile
        {
            String surfacerlib ;    ///< Name of the surfacer library, without 'lib' and extension.
            String driverlib ;      ///< Name of the driver library, without 'lib' and extension.
            String autoloadpath ;   ///< Path to a plugin directory autoloaded at startup.
        };
        
    private:
        
        ////////////////////////////////////////////////////////////
        Shared < MimeDatabase >     iMimeDb ;
        Shared < Channel >          iChannel ;
        Shared < PluginDatabase >   iPluginDb ;
        Shared < Driver >           iDriver ;
        mutable Spinlock            iSpinlock ;
        ConfigFile                  iConfig ;
        bool                        iDontSaveConfigFile ;
        Shared < Surfacer >         iSurfacer ;
        Shared < ObjectGroup >      iDefaultGroup ; ///< Default ObjectGroup used by the engine.
        Shared < Metaclasser >      iMetaclasser ;
        Shared < MaterialManager >  iMaterialManager ;
        Shared < MeshManager >      iMeshManager ;
        
    public:

        ////////////////////////////////////////////////////////////
        Root();

        ////////////////////////////////////////////////////////////
        virtual ~Root();

        ////////////////////////////////////////////////////////////
        Weak < MimeDatabase > GetMimeDatabase() const ;
        
        ////////////////////////////////////////////////////////////
        Weak < PluginDatabase > GetPluginDatabase() const ;
        
        ////////////////////////////////////////////////////////////
        Weak < Driver > GetDriver() const ;

        ////////////////////////////////////////////////////////////
        Logger GetLogger() const ;
        
        ////////////////////////////////////////////////////////////
        void SetDefaultChannel( const Shared < Channel > & channel );

        ////////////////////////////////////////////////////////////
        void Reset();

        ////////////////////////////////////////////////////////////
        void InstallPlugin( const Shared < Plugin > & plugin );
        
        ////////////////////////////////////////////////////////////
        void UninstallPlugin( const Shared < Plugin > & plugin );
        
        ////////////////////////////////////////////////////////////
        void RemoveAllPlugins();

        ////////////////////////////////////////////////////////////
        /// \brief Install the given Driver or except on assert if a
        /// driver is already installed.
        ///
        /// \param driver Driver to install.
        ///
        ////////////////////////////////////////////////////////////
        void InstallDriver( const Shared < Driver > & driver );

        ////////////////////////////////////////////////////////////
        void LoadPluginDirectory( const Filename& dir );

        ////////////////////////////////////////////////////////////
        const String GetPathSeparator() const ;
        
        ////////////////////////////////////////////////////////////
        void LoadSimpleMimeDatabase( const String& filename );

        ////////////////////////////////////////////////////////////
        /// \brief Initializes Platform, EventQueue, and Configuration
        /// file using given command line args or default ones.
        ///
        /// \param argc Number of argument.
        /// \param argv Array of strings.
        ///
        /// \note When finished this initialization, you can modify
        /// the ConfigFile by setting a new configuration. After that,
        /// you can load the configuration selected by using 'Init()'.
        ///
        /// \see Init
        ///
        ////////////////////////////////////////////////////////////
        Root& PlatformInit( int argc , char** argv );
        
        ////////////////////////////////////////////////////////////
        /// \brief Initializes the Root objects with the currently
        /// selected Configuration.
        ///
        /// Loads the Surfacer lib, then the Driver lib and then load
        /// every plugins in the Autoload directory.
        ///
        ////////////////////////////////////////////////////////////
        bool Init( void );
        
        ////////////////////////////////////////////////////////////
        /// \brief Get the current working directory.
        ///
        /// By default, this corresponds to './'.
        ///
        ////////////////////////////////////////////////////////////
        String GetWorkingDirectory() const ;
        
        ////////////////////////////////////////////////////////////
        /// \brief Changes the current working directory.
        ///
        ////////////////////////////////////////////////////////////
        void SetWorkingDirectory( const String& cwd );
        
        ////////////////////////////////////////////////////////////
        /// \brief Changes config file saving behaviour.
        ///
        ////////////////////////////////////////////////////////////
        void SetDontSaveConfigFile( bool value );
        
        ////////////////////////////////////////////////////////////
        /// \brief Gets the current config file.
        ///
        ////////////////////////////////////////////////////////////
        ConfigFile GetConfigFile() const ;
        
        ////////////////////////////////////////////////////////////
        /// \brief Changes the Configuration file.
        ///
        /// \param cfg Structure to replace.
        ///
        ////////////////////////////////////////////////////////////
        void SetConfigFile( const ConfigFile& cfg );
        
        ////////////////////////////////////////////////////////////
        /// \brief Get the Surfacer selected.
        ///
        ////////////////////////////////////////////////////////////
        Weak < Surfacer > GetSurfacer() const ;
        
        ////////////////////////////////////////////////////////////
        /// \brief Install a Surfacer onto this Root.
        ///
        /// If a surfacer is already installed, throw an assertion error
        /// and end the program. This is done because no plugin should
        /// install a surfacer. Only the library set in configuration
        /// file can install one.
        ///
        ////////////////////////////////////////////////////////////
        void InstallSurfacer( const Shared < Surfacer >& surfacer );
        
        ////////////////////////////////////////////////////////////
        /// \brief Return all registered Surface.
        ///
        ////////////////////////////////////////////////////////////
        WeakVector < Surface > GetSurfaces( void ) const ;
        
        ////////////////////////////////////////////////////////////
        /// \brief Return the default group used by the root system.
        ///
        ////////////////////////////////////////////////////////////
        Weak < ObjectGroup > GetDefaultObjectGroup() const ;
        
        ////////////////////////////////////////////////////////////
        Weak < Metaclasser > GetMetaclasser() const ;
        
        ////////////////////////////////////////////////////////////
        Weak < MaterialManager > GetMaterialManager() const ;
        
        ////////////////////////////////////////////////////////////
        Weak < MeshManager > GetMeshManager() const ;
        
    protected:
        
        ////////////////////////////////////////////////////////////
        /// \brief Save the ConfigFile to 'config.atl'.
        ///
        ////////////////////////////////////////////////////////////
        void SaveConfigFile();
        
        ////////////////////////////////////////////////////////////
        /// \brief Load the ConfigFile from 'config.atl'.
        ///
        ////////////////////////////////////////////////////////////
        void LoadConfigFile();
    };
}

#endif /* Root_hpp */
