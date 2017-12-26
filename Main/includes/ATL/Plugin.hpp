//
//  Plugin.hpp
//  atlresource
//
//  Created by Jacques Tronconi on 17/09/2017.
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//

#ifndef Plugin_hpp
#define Plugin_hpp

#include <ATL/StdIncludes.hpp>
#include <ATL/MimeType.hpp>
#include <ATL/Dynlib.hpp>
#include <ATL/Metaclasser.hpp>

namespace atl
{
    class Plugin
    {
        String iName ;
        String iDescription ;
        Vector < MimeType > iMimeTypes ;
        mutable Spinlock iSpinlock ;
        String iAuthor ;
        
    public:
        
        Plugin();
        virtual ~Plugin();
        
        virtual void SetName( const String& name );
        virtual void SetDesc( const String& desc );
        virtual void SetAuthor( const String& author );
        virtual void AddMimeType( const MimeType& mime );
        
        virtual String GetName() const ;
        virtual String GetDesc() const ;
        virtual String GetAuthor() const ;
        virtual Vector < MimeType > GetMimeTypes() const ;
        
        virtual void Lock();
        virtual void Unlock();
        
        virtual Vector < MimeType > & GetMimeTypes();
    };
    
    class PluginDatabase
    {
        Map < Shared < Dynlib > , WeakVector < Plugin > > iPluginsByDynlib ;
        SharedVector < Plugin > iPlugins ;
        mutable Mutex iMutex ;
        
    public:
        
        PluginDatabase();
        virtual ~PluginDatabase();
        
        virtual void Add( const Shared < Plugin > & plugin );
        virtual void Remove( const Shared < Plugin > & plugin );
        virtual SharedVector < Plugin > GetPlugins() const ;
        virtual void Reset();
        
        virtual Weak < Dynlib > LoadDynlib( const Filename& filename );
        virtual Weak < Dynlib > FindDynlib( const Filename& filename ) const ;
    };
}

#endif /* Plugin_hpp */
