//
//  Image.cpp
//  atlresource
//
//  Created by Jacques Tronconi on 21/09/2017.
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//

#include <ATL/Image.hpp>

namespace atl
{
    Image::Image( const Filename& filename ) : iFilename( filename )
    {

    }

    Image::~Image()
    {

    }

    void Image::SetBuffer(const CBuffer&buf)
    {
        iBuffer.Set( buf );
    }

    CBuffer& Image::GetBuffer()
    {
        return iBuffer ;
    }

    const CBuffer& Image::GetBuffer() const
    {
        return iBuffer ;
    }

    unsigned char* Image::GetData()
    {
        return (unsigned char*) iBuffer.GetData();
    }

    const unsigned char* Image::GetData() const
    {
        return (const unsigned char*) iBuffer.GetData();
    }

    size_t Image::GetSize() const
    {
        return iBuffer.GetSize();
    }
}
