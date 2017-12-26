//  ========================================================================  //
//
//  File    : ATL/Stage.hpp
//  Project : atlresource
//  Author  : Luk2010
//  Date    : 30/10/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#ifndef Stage_hpp
#define Stage_hpp

#include <ATL/StdIncludes.hpp>

namespace atl
{
    ////////////////////////////////////////////////////////////
    /// \brief Defines values for often-used shader stages over
    /// different APIs.
    ///
    ////////////////////////////////////////////////////////////
    enum class Stage : unsigned int
    {
        Unknown = 0 ,
        
        Vertex ,                ///< Unambiguous Vertex shader stage, process vertex datas.
        
        Fragment ,              ///< Fragment stages, process fragments or pixels.
        Pixel = Fragment ,      ///< D3D equivalent of Fragment.
        
        Hull ,                  ///< First stage of tesselation stages.
        TessControl = Hull ,    ///< OpenGL equivalent of Hull-stage.
        
        Domain ,                ///< Last (third) stage of tesselation stages, second programmable tesselation stage.
        TessEvaluation = Domain,///< OpenGL equivalent for Domain-stage.
        
        Geometry ,              ///< Geometry stage, same for D3D and OpenGL.
        Compute                 ///< Compute stage, generally outside the normal shader pipeline.
    };
}

#endif /* Stage_hpp */
