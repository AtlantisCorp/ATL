//  ========================================================================  //
//
//  File    : ATL/ErrorEvent.hpp
//  Project : atlresource
//  Author  : Luk2010
//  Date    : 06/11/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#ifndef ErrorEvent_hpp
#define ErrorEvent_hpp

#include <ATL/StdIncludes.hpp>
#include <ATL/Listener.hpp>
#include <ATL/Error.hpp>

namespace atl
{
    ////////////////////////////////////////////////////////////
    class ErrorEvent : public Event
    {
        ////////////////////////////////////////////////////////////
        Error  m_errcode ; ///< Error related to this event.
        String m_message ; ///< Message for this event.
        
    public:
        
        ////////////////////////////////////////////////////////////
        ErrorEvent( Error errcode , const String& message );
        
        ////////////////////////////////////////////////////////////
        const String& GetMessage() const ;
        
        ////////////////////////////////////////////////////////////
        const Error& GetError() const ;
    };
    
    ////////////////////////////////////////////////////////////
    class ExceptionErrorEvent : public ErrorEvent
    {
        ////////////////////////////////////////////////////////////
        std::exception const& m_exception ; ///< Exception associated to this event.
        
    public:
        
        ////////////////////////////////////////////////////////////
        ExceptionErrorEvent( std::exception const& exception , Error errcode , const String& message );
        
        ////////////////////////////////////////////////////////////
        const std::exception& GetException() const ;
    };
}

#endif /* ErrorEvent_hpp */
