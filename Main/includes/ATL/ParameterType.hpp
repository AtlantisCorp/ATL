//  ========================================================================  //
//
//  File    : ATL/ParameterType.hpp
//  Project : atlresource
//  Author  : Luk2010
//  Date    : 29/10/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#ifndef ParameterType_hpp
#define ParameterType_hpp

#include <ATL/StdIncludes.hpp>

namespace atl
{
    ////////////////////////////////////////////////////////////
    /// \brief Enumerates types available for a parameter.
    ///
    /// \note 'Texture' is a special parameter type where the parameter
    /// will hold a 'Weak < Texture >' object. When the parameter is bound
    /// to the program, it will have a different behaviour. 
    ///
    ////////////////////////////////////////////////////////////
    enum class ParameterType : unsigned short
    {
        Float1 , Float2 , Float3 , Float4 ,
        Int1 , Int2 , Int3 , Int4 ,
        Uint1 , Uint2 , Uint3 , Uint4 ,
        Bool1 , Bool2 , Bool3 , Bool4 ,
        Mat2 , Mat3 , Mat4 ,
        Texture
    };
}

#endif /* ParameterType_hpp */
