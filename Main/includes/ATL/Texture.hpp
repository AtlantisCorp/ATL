//
//  Texture.hpp
//  atlresource
//
//  Created by Jacques Tronconi on 21/09/2017.
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//

#ifndef Texture_hpp
#define Texture_hpp

#include <ATL/StdIncludes.hpp>
#include <ATL/Image.hpp>

namespace atl
{
    class Texture : public Resource
    {
        Weak < Image > iImage ;
        
    public:
        
        Texture( const Weak < Image > image );
        virtual ~Texture();
        
        ////////////////////////////////////////////////////////////
        /// \brief Binds the texture for use.
        ///
        ////////////////////////////////////////////////////////////
        virtual void Bind() const = 0 ;
    };
}

#endif /* Texture_hpp */
