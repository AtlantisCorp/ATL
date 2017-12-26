//  ========================================================================  //
//
//  File    : ATL/Alias.hpp
//  Project : atlresource
//  Author  : Luk2010
//  Date    : 29/10/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#ifndef Alias_hpp
#define Alias_hpp

#include <ATL/StdIncludes.hpp>

namespace atl
{
    ////////////////////////////////////////////////////////////
    /// \brief Defines some often used aliases for program's parameters.
    ///
    ////////////////////////////////////////////////////////////
    enum class Alias : unsigned long long
    {
        Unknown = 0 ,
        
        MatrixView ,
        MatrixProjection ,
        MatrixModel ,
        Matrix3View ,
        Matrix3Projection ,
        Matrix3Model ,
        MatrixViewProjection ,
        Matrix3ViewProjection ,
        MatrixMVP ,
        Matrix3MVP ,
        
        Texture1 , Texture2 , Texture3 , Texture4 , Texture5 , Texture6 , Texture7 , Texture8 , Texture9 ,
        Texture10 , Texture11 , Texture12 , Texture13 , Texture14 , Texture15 , Texture16 ,
        
        MaterialAmbient ,
        MaterialDiffuse ,
        MaterialSpecular ,
        MaterialTextureAmbient ,
        MaterialTextureDiffuse ,
        MaterialTextureSpecular ,
        MaterialTexture1 ,
        MaterialTexture2 ,
        MaterialTexture3 ,
        MaterialTexture4 ,
        MaterialShininess ,
        MaterialComponent1 ,
        MaterialComponent2 ,
        MaterialComponent3 ,
        MaterialComponent4 ,
        MaterialComponent5
    };
}

#endif /* Alias_hpp */
