//  ========================================================================  //
//
//  File    : ATL/Error.hpp
//  Project : atlresource
//  Author  : Luk2010
//  Date    : 06/11/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#ifndef Error_hpp
#define Error_hpp

#include <ATL/StdIncludes.hpp>

namespace atl
{
    ////////////////////////////////////////////////////////////
    enum class Error : unsigned long
    {
        None = 0 ,
        MetaclassCreate , ///< Error from Metaclass::Create. Usually sent when it fails to create an object.
        ProgramCreate ,   ///< Launched when Context::CreateProgram() fails and catch an exception.
        PluginError ,     ///< Launched by any Plugin for their errors.
        InvalidWeak ,     ///< A Weak pointer is invalid but should not be.
        ParameterBinding  ///< A parameter should not be bound to the given value type, or the parameter does
                          ///  not exist in the program.
    };
}

#endif /* Error_hpp */
