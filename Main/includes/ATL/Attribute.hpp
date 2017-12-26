//  ========================================================================  //
//
//  File    : ATL/Attribute.hpp
//  Project : atlresource
//  Author  : Luk2010
//  Date    : 13/11/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#ifndef Attribute_hpp
#define Attribute_hpp

#include <ATL/StdIncludes.hpp>

namespace atl
{
    ////////////////////////////////////////////////////////////
    /// \brief Represents some possible aliases that will be bound
    /// to any program's attribute.
    ///
    /// As HLSL and GLSL accepts no more than 15 attributes (or slots),
    /// Slot0 to Slot14 are provided for custom attributes. Other commonly
    /// used attributes can be used as Position1, Position2, etc.
    ///
    /// Attributes aliases are not related to the type it might represent.
    /// If you want to have Position1 represents positions in a buffer
    /// of Matrix 4 by 4, you just have to specify the correct VertexComponent
    /// format that will be used to match the VertexLayout of Attribute.
    ///
    ////////////////////////////////////////////////////////////
    enum class Attribute : unsigned long
    {
        Slot0 , Slot1 , Slot2 , Slot3 , Slot4 ,
        Slot5 , Slot6 , Slot7 , Slot8 , Slot9 ,
        Slot10 , Slot11 , Slot12 , Slot13 , Slot14 ,
        
        Position1 , Position2 ,
        Normal1 , Normal2 ,
        Tangent1 , Tangent2 ,
        Bitangent1 , Bitangent2 ,
        Color1 , Color2 
    };
}

#endif /* Attribute_hpp */
