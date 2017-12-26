//
//  Plugin.cpp
//  atlresource
//
//  Created by Jacques Tronconi on 17/09/2017.
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//

#include <ATL/Plugin.hpp>
#include <ATL/Root.hpp>

namespace atl
{
    Plugin::Plugin()
    {

    }

    Plugin::~Plugin()
    {

    }

    void Plugin::SetName(const String &name)
    {
        Spinlocker lck( iSpinlock );
        iName = name ;
    }

    void Plugin::SetDesc(const String &desc)
    {
        Spinlocker lck( iSpinlock );
        iDescription = desc ;
    }

    void Plugin::SetAuthor(const String &author)
    {
        Spinlocker lck( iSpinlock );
        iAuthor = author ;
    }

    void Plugin::AddMimeType(const atl::MimeType &mime)
    {
        Spinlocker lck( iSpinlock );

        auto it = std::find( iMimeTypes.begin() , iMimeTypes.end() , mime );

        if ( it == iMimeTypes.end() )
        iMimeTypes.push_back( mime );
    }

    String Plugin::GetName() const
    {
        Spinlocker lck( iSpinlock );
        return iName ;
    }

    String Plugin::GetDesc() const
    {
        Spinlocker lck( iSpinlock );
        return iDescription ;
    }

    String Plugin::GetAuthor() const
    {
        Spinlocker lck( iSpinlock );
        return iAuthor ;
    }

    Vector < MimeType > Plugin::GetMimeTypes() const
    {
        Spinlocker lck( iSpinlock );
        return iMimeTypes ;
    }

    void Plugin::Lock()
    {
        iSpinlock.lock();
    }

    void Plugin::Unlock()
    {
        iSpinlock.unlock();
    }

    Vector < MimeType > & Plugin::GetMimeTypes()
    {
        return iMimeTypes ;
    }

    // -------------------------------------------------------------------------------------------------------

    PluginDatabase::PluginDatabase()
    {

    }

    PluginDatabase::~PluginDatabase()
    {

    }

    void PluginDatabase::Add(const Shared<atl::Plugin> &plugin)
    {
        MutexLocker lck( iMutex );

        auto it = std::find( iPlugins.begin() , iPlugins.end() , plugin );

        if ( it == iPlugins.end() )
        iPlugins.push_back( plugin );
    }

    void PluginDatabase::Remove(const Shared<atl::Plugin> &plugin)
    {
        MutexLocker lck( iMutex );

        auto it = std::find( iPlugins.begin() , iPlugins.end() , plugin );

        if ( it != iPlugins.end() )
        iPlugins.erase( it );

        for ( auto pair : iPluginsByDynlib )
        {
            for ( auto it = pair.second.begin() ; it != pair.second.end() ; it++ )
            {
                if ( it->lock() == plugin )
                {
                    pair.second.erase( it );
                    return ;
                }
            }
        }
    }

    SharedVector < Plugin > PluginDatabase::GetPlugins() const
    {
        MutexLocker lck( iMutex );
        return iPlugins ;
    }

    void PluginDatabase::Reset()
    {
        MutexLocker lck( iMutex );
        iPlugins.clear();
        iPluginsByDynlib.clear();
    }

    Weak < Dynlib > PluginDatabase::LoadDynlib(const atl::Filename &filename)
    {
        assert( FindDynlib( filename ).expired()
           && ( String( "Dynlib already loaded: " ) + filename.GetPath() ).size() );

        if ( filename.GetExtension() != DYNLIB_EXTENSION )
        return Weak < Dynlib >();

        Shared < Dynlib > dynlib = std::make_shared < Dynlib >( filename );
        
        if ( !dynlib->GetHandle() )
        {
            Root::Get().GetLogger().warn( "Invalid handle for dylib: " , filename.GetPath() );
            return Weak < Dynlib >();
        }

        if ( !dynlib -> IsStartable() )
        return Weak < Dynlib > ();

        dynlib -> GetPerformer().Start( [dynlib](){ dynlib -> Start(); } );
        dynlib -> GetPerformer().Wait();

        MutexLocker lck( iMutex );
        iPluginsByDynlib[dynlib] = { };

        return dynlib ;
    }

    Weak < Dynlib > PluginDatabase::FindDynlib(const atl::Filename &filename) const
    {
        MutexLocker lck( iMutex );

        for ( const auto& pair : iPluginsByDynlib )
        {
            if ( pair.first -> GetFilename() == filename )
            return pair.first ;
        }

        return Weak < Dynlib >();
    }
}
