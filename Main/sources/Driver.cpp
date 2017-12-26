//  ========================================================================  //
//
//  File    : ATL/Driver.cpp
//  Project : atlresource
//  Author  : Luk2010
//  Date    : 19/09/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#include <ATL/Driver.hpp>
#include <ATL/Root.hpp>

namespace atl
{
    ////////////////////////////////////////////////////////////
    Driver::Driver()
    {

    }

    ////////////////////////////////////////////////////////////
    Driver::~Driver()
    {

    }
    
    ////////////////////////////////////////////////////////////
    Weak < RenderWindow > Driver::CreateRenderWindow( const VideoMode& mode , const String& title , atl::Style style , const ContextSettings& settings )
    {
        auto surfacer = Root::Get().GetSurfacer();
        assert( !surfacer.expired() && "Surfacer is 'null'." );
        return CreateRenderWindow( surfacer.lock()->CreateSurface(mode, title, style) , settings );
    }
    
    ////////////////////////////////////////////////////////////
    void Driver::AddRenderWindow( const Shared < RenderWindow >& rw )
    {
        MutexLocker lck( m_mutex );
        m_windows.push_back( rw );
    }
    
    ////////////////////////////////////////////////////////////
    Shared < RenderPath > Driver::CreateRenderPath( const Weak < RenderWindow >& window ) const
    {
        return std::make_shared < RenderPath >( window );
    }
    
    ////////////////////////////////////////////////////////////
    void Driver::RemoveRenderWindow( const Weak < RenderWindow >& window )
    {
        MutexLocker lck( m_mutex );
        auto it = std::find( m_windows.begin() , m_windows.end() , window.lock() );
        
        if ( it != m_windows.end() )
        {
            m_windows.erase( it );
        }
    }
}
