//  ========================================================================  //
//
//  File    : ATL/Key.cpp
//  Project : atlresource
//  Author  : Luk2010
//  Date    : 13/10/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#include <ATL/Key.hpp>

namespace atl
{
    namespace Key
    {
        ////////////////////////////////////////////////////////////
        bool IsSpecialKey( const String& key )
        {
            if ( key.size() != 2 )
                return false ;
            
            if ( ( (unsigned char) key.at(0) ) != 0xF7 )
                return false ;
            
            return ( (unsigned char) key.at(1) ) <= ( (unsigned char) Key::Unsupported.at(1) ) ;
        }
        
        ////////////////////////////////////////////////////////////
        bool IsControlKey( const String& key )
        {
            if ( key.size() != 1 )
                return false ;
            
            return ( (unsigned char) key.at(0) ) <= 0x1F || key == Key::Delete ;
        }
    }
}
