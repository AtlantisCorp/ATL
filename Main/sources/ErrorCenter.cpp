//  ========================================================================  //
//
//  File    : ATL/ErrorCenter.cpp
//  Project : atlresource
//  Author  : Luk2010
//  Date    : 06/11/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#include <ATL/ErrorCenter.hpp>
#include <ATL/ErrorEvent.hpp>

namespace atl
{
    ////////////////////////////////////////////////////////////
    ErrorCenter ErrorCenter::s_center ;
    
    ////////////////////////////////////////////////////////////
    void ErrorCenter::CatchException( const std::exception& exception , Error errcode , const char* format , ... )
    {
        char* buffer = new char [1024];
        memset( buffer , 0 , 1024 );
        
        va_list args ;
        va_start( args , format );
        vsnprintf( buffer , 1024 , format , args );
        va_end( args );
        
        String message( buffer );
        delete[] buffer ;
        
        s_center.m_emitter.SendEvent < ExceptionErrorEvent >( exception , errcode , message );
    }
    
    ////////////////////////////////////////////////////////////
    void ErrorCenter::CatchError( Error errcode , const char* format , ... )
    {
        char* buffer = new char [1024];
        memset( buffer , 0 , 1024 );
        
        va_list args ;
        va_start( args , format );
        vsnprintf( buffer , 1024 , format , args );
        va_end( args );
        
        String message( buffer );
        delete[] buffer ;
        
        s_center.m_emitter.SendEvent < ErrorEvent >( errcode , message );
    }
    
    ////////////////////////////////////////////////////////////
    void ErrorCenter::AddListener( const Shared < Listener >& listener )
    {
        s_center.m_emitter.AddListener( listener );
    }
    
    ////////////////////////////////////////////////////////////
    void ErrorCenter::ResetListeners()
    {
        s_center.m_emitter.Reset();
    }
    
    ////////////////////////////////////////////////////////////
    ErrorCenter::ErrorCenter()
    {
        
    }
    
    ////////////////////////////////////////////////////////////
    ErrorCenter::~ErrorCenter()
    {
        
    }
}
