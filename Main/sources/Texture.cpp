//
//  Texture.cpp
//  atlresource
//
//  Created by Jacques Tronconi on 21/09/2017.
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//

#include <ATL/Texture.hpp>

namespace atl
{
    Texture::Texture( const Weak < Image > image ) : iImage( image )
    {
        
    }
    
    Texture::~Texture()
    {
        
    }
}
