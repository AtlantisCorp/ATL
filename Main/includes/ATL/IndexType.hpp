//  ========================================================================  //
//
//  File    : ATL/IndexType.hpp
//  Project : atlresource
//  Author  : Luk2010
//  Date    : 25/10/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#ifndef IndexType_hpp
#define IndexType_hpp

#include <ATL/StdIncludes.hpp>

namespace atl
{
    ////////////////////////////////////////////////////////////
    /// \brief Define multiple type an index can be of.
    ///
    ////////////////////////////////////////////////////////////
    enum class IndexType : unsigned int
    {
        Unknown = 0 ,
        UI8 , I8 , UI16 , I16 , UI32 , I32
    };
}

#endif /* IndexType_hpp */
