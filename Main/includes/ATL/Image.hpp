//
//  Image.hpp
//  atlresource
//
//  Created by Jacques Tronconi on 21/09/2017.
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//

#ifndef Image_hpp
#define Image_hpp

#include <ATL/StdIncludes.hpp>
#include <ATL/Resource.hpp>
#include <ATL/Filename.hpp>
#include <ATL/CBuffer.hpp>

namespace atl
{    
    class Image : public Resource
    {
        Filename iFilename ;
        CBuffer  iBuffer ;
        
    public:
        
        Image( const Filename& filename );
        virtual ~Image();
        
        virtual void SetBuffer( const CBuffer& buf );
        virtual CBuffer& GetBuffer();
        virtual const CBuffer& GetBuffer() const ;
        
        virtual unsigned char* GetData();
        virtual const unsigned char* GetData() const ;
        
        virtual size_t GetSize() const ;
    };
}

#endif /* Image_hpp */
