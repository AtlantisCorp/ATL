//  ========================================================================  //
//
//  File    : ATL/Metaclasser.cpp
//  Project : atlresource
//  Author  : Luk2010
//  Date    : 02/11/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#include <ATL/Metaclasser.hpp>

namespace atl
{
    ////////////////////////////////////////////////////////////
    Metaclasser::Metaclasser()
    {
        
    }
    
    ////////////////////////////////////////////////////////////
    Metaclasser::~Metaclasser()
    {
        
    }
    
    ////////////////////////////////////////////////////////////
    Detail::IMetaclass* Metaclasser::GetMetaclass( const MimeType& mime )
    {
        MutexLocker lck( m_mutex );
        
        auto it = m_metabymime.find( mime );
        
        if ( it == m_metabymime.end() )
            return nullptr ;
        
        return it->second ;
    }
    
    ////////////////////////////////////////////////////////////
    const Detail::IMetaclass* Metaclasser::GetMetaclass( const MimeType& mime ) const
    {
        MutexLocker lck( m_mutex );
        
        auto it = m_metabymime.find( mime );
        
        if ( it == m_metabymime.end() )
            return nullptr ;
        
        return it->second ;
    }
}
