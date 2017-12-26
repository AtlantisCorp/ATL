//  ========================================================================  //
//
//  File    : ATL/Surfacer.cpp
//  Project : atlresource
//  Author  : Luk2010
//  Date    : 10/10/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //

#include <ATL/Surfacer.hpp>

namespace atl
{
    ////////////////////////////////////////////////////////////
    Surfacer::Surfacer()
    {
        
    }
    
    ////////////////////////////////////////////////////////////
    Surfacer::~Surfacer()
    {
        
    }
    
    ////////////////////////////////////////////////////////////
    WeakVector < Surface > Surfacer::GetSurfaces() const
    {
        MutexLocker lck( m_mutex );
        WeakVector < Surface > retvalue ;
        
        for ( auto surf : m_surfaces )
            retvalue.push_back( surf );
        
        return retvalue ;
    }
    
    ////////////////////////////////////////////////////////////
    void Surfacer::RemoveSurface( const Weak < Surface >& surface )
    {
        MutexLocker lck( m_mutex );
        auto it = std::find( m_surfaces.begin() , m_surfaces.end() , surface.lock() );
        
        if ( it != m_surfaces.end() )
            m_surfaces.erase( it );
    }
    
    ////////////////////////////////////////////////////////////
    void Surfacer::AddSurface( const Shared < Surface >& surface )
    {
        MutexLocker lck( m_mutex );
        m_surfaces.push_back( surface );
    }
}
