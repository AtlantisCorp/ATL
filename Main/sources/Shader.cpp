//  ========================================================================  //
//
//  File    : ATL/Shader.cpp
//  Project : atlresource
//  Author  : Luk2010
//  Date    : 04/11/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#include <ATL/Shader.hpp>

namespace atl
{
    ////////////////////////////////////////////////////////////
    Shader::Shader( Stage stage , const String& file , const MimeType& mime )
    : Resource( file , mime ) , m_stage( stage )
    {
        
    }
    
    ////////////////////////////////////////////////////////////
    Shader::Shader( const String& file , va_list& args )
    {
        
    }
    
    ////////////////////////////////////////////////////////////
    Shader::~Shader()
    {
        
    }
    
    ////////////////////////////////////////////////////////////
    Stage Shader::GetStage() const
    {
        return m_stage.load();
    }
}
