//  ========================================================================  //
//
//  File    : ATL/ErrorEvent.cpp
//  Project : atlresource
//  Author  : Luk2010
//  Date    : 06/11/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#include <ATL/ErrorEvent.hpp>

namespace atl
{
    ////////////////////////////////////////////////////////////
    ErrorEvent::ErrorEvent( Error errcode , const String& message ) : m_errcode( errcode ) , m_message( message )
    {
        
    }
    
    ////////////////////////////////////////////////////////////
    const String& ErrorEvent::GetMessage() const
    {
        return m_message ;
    }
    
    ////////////////////////////////////////////////////////////
    const Error& ErrorEvent::GetError() const
    {
        return m_errcode ;
    }
    
    ////////////////////////////////////////////////////////////
    ExceptionErrorEvent::ExceptionErrorEvent( std::exception const& exception , Error errcode , const String& message )
    : ErrorEvent( errcode , message ) , m_exception( exception )
    {
        
    }
    
    ////////////////////////////////////////////////////////////
    const std::exception& ExceptionErrorEvent::GetException() const
    {
        return m_exception ;
    }
}
