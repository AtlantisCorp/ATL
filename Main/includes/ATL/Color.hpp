//  ========================================================================  //
//
//  File    : ATL/Color.hpp
//  Project : atlresource
//  Author  : Luk2010
//  Date    : 16/10/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#ifndef Color_h
#define Color_h

#include <ATL/StdIncludes.hpp>

namespace atl
{
    ////////////////////////////////////////////////////////////
    /// \brief Defines a generic color3 object.
    ///
    ////////////////////////////////////////////////////////////
    struct Color3
    {
        union
        {
            float data [3] ; ///< Data representing the color (rgb).
            
            struct
            {
                float r ;
                float g ;
                float b ;
            };
        };
        
        
        ////////////////////////////////////////////////////////////
        Color3();
        
        ////////////////////////////////////////////////////////////
        Color3( float r , float g , float b );
        
        ////////////////////////////////////////////////////////////
        Color3( const Color3& color );
    };
    
    ////////////////////////////////////////////////////////////
    /// \brief Defines a generic color4 object.
    ///
    /// As OpenGL uses RGBA, DirectX uses ARGB, and those two are the
    /// two major rendering drivers, only those two formats are supported
    /// with this class. If your set of colors is not RGBA or ARGB, please
    /// use PixelSet instead wich can be used to store arbitrary pixels.
    ///
    /// When getting a 'Color4*' array, don't forget to set 'sizeof(Color4)'
    /// and not 'sizeof(float)*4' as the size between two color component,
    /// because there is a bool right in the middle and data might be
    /// corrupted when forgotten.
    ///
    ////////////////////////////////////////////////////////////
    struct Color4
    {
        ////////////////////////////////////////////////////////////
        struct rgba_t
        {
            float r ;
            float g ;
            float b ;
            float a ;
        };
        
        ////////////////////////////////////////////////////////////
        struct argb_t
        {
            float a ;
            float r ;
            float g ;
            float b ;
        };
        
        ////////////////////////////////////////////////////////////
        union
        {
            float  data [4] ; ///< Data representing the color (rgba).
            rgba_t rgba ;     ///< Data for RGBA format.
            argb_t argb ;     ///< Data for ARGB format.
        };
        
        bool isrgba ; ///< true when RGBA , false when ARGB.
        
        ////////////////////////////////////////////////////////////
        Color4();
        
        ////////////////////////////////////////////////////////////
        Color4( float c1 , float c2 , float c3 , float c4 , bool rgba = true );
        
        ////////////////////////////////////////////////////////////
        Color4( const Color3& rgb , float a , bool rgba = true );
        
        ////////////////////////////////////////////////////////////
        Color4( const Color4& color );
        
        ////////////////////////////////////////////////////////////
        Color3 RGB() const ;
        
        ////////////////////////////////////////////////////////////
        Color4 RGBA() const ;
        
        ////////////////////////////////////////////////////////////
        Color4 ARGB() const ;
    };
}

#endif /* Color_h */
