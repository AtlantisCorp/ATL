//  ========================================================================  //
//
//  File    : Gl3Driver/Gl3Includes.cpp
//  Project : ATL/Gl3Driver
//  Author  : Luk2010
//  Date    : 08/11/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#include <Gl3Driver/Gl3Includes.h>

////////////////////////////////////////////////////////////
Gl3Exception::Gl3Exception( Gl3Error errcode , const char* format , ... ) : m_error( errcode )
{
    char* buffer = new char [1024];
    memset( buffer , 0 , 1024 );
    
    va_list args ;
    va_start( args , format );
    vsnprintf( buffer , 1024 , format , args );
    va_end( args );
    
    m_message = atl::String( buffer );
    delete[] buffer ;
}

////////////////////////////////////////////////////////////
const char* Gl3Exception::what() const noexcept 
{
    return m_message.data();
}
