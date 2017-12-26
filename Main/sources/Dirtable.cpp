//  ========================================================================  //
//
//  File    : ATL/Dirtable.cpp
//  Project : atlresource
//  Author  : Luk2010
//  Date    : 05/12/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#include <ATL/Dirtable.hpp>

namespace atl
{
    namespace Detail
    {
        ////////////////////////////////////////////////////////////
        Dirtable::Dirtable() : m_dirty( true )
        {
            
        }
        
        ////////////////////////////////////////////////////////////
        Dirtable::~Dirtable()
        {
            
        }
        
        ////////////////////////////////////////////////////////////
        bool Dirtable::IsDirty() const
        {
            return m_dirty.load();
        }
        
        ////////////////////////////////////////////////////////////
        void Dirtable::SetDirty( bool dirty ) const
        {
            m_dirty.store( dirty );
        }
    }
}
