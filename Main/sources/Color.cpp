//  ========================================================================  //
//
//  File    : ATL/Color.cpp
//  Project : atlresource
//  Author  : Luk2010
//  Date    : 16/10/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#include <ATL/Color.hpp>

namespace atl
{
    ////////////////////////////////////////////////////////////
    Color3::Color3()
    {
        memset( data , 0 , sizeof(float)*3 );
    }
    
    ////////////////////////////////////////////////////////////
    Color3::Color3( float r_ , float g_ , float b_ )
    {
        data[0] = r_ ;
        data[1] = g_ ;
        data[2] = b_ ;
    }
    
    ////////////////////////////////////////////////////////////
    Color3::Color3( const Color3& color )
    {
        memcpy( data , color.data , sizeof(float)*3 );
    }
    
    ////////////////////////////////////////////////////////////
    Color4::Color4() : isrgba( true )
    {
        memset( data , 0 , sizeof(float)*4 );
    }
    
    ////////////////////////////////////////////////////////////
    Color4::Color4( float a , float b , float c , float d , bool rgba_ ) : isrgba( rgba_ )
    {
        if ( isrgba )
        {
            rgba.r = a ;
            rgba.g = b ;
            rgba.b = c ;
            rgba.a = d ;
        }
        
        else
        {
            argb.a = a ;
            argb.r = b ;
            argb.g = c ;
            argb.b = d ;
        }
    }
    
    ////////////////////////////////////////////////////////////
    Color4::Color4( const Color3& color , float a , bool rgba_ ) : isrgba( rgba_ )
    {
        if ( isrgba )
        {
            memcpy( data , color.data , sizeof(float)*3 );
            rgba.a = a ;
        }
        
        else
        {
            memcpy( data + 1 , color.data , sizeof(float)*3 );
            argb.a = a ;
        }
    }
    
    ////////////////////////////////////////////////////////////
    Color4::Color4( const Color4& color ) : isrgba( color.isrgba )
    {
        memcpy( data , color.data , sizeof(float)*4 );
    }
    
    ////////////////////////////////////////////////////////////
    Color3 Color4::RGB() const
    {
        if ( isrgba )
        {
            return Color3( rgba.r , rgba.g , rgba.b );
        }
        
        else
        {
            return Color3( argb.r , argb.g , argb.b );
        }
    }
    
    ////////////////////////////////////////////////////////////
    Color4 Color4::RGBA() const
    {
        if ( isrgba )
        {
            return Color4( *this );
        }
        
        else
        {
            return Color4( RGB() , argb.a );
        }
    }
    
    ////////////////////////////////////////////////////////////
    Color4 Color4::ARGB() const
    {
        if ( isrgba )
        {
            return Color4( RGB() , rgba.a );
        }
        
        else
        {
            return Color4( *this );
        }
    }
}
