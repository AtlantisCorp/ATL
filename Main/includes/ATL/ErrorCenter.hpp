//  ========================================================================  //
//
//  File    : ATL/ErrorCenter.hpp
//  Project : atlresource
//  Author  : Luk2010
//  Date    : 06/11/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#ifndef ErrorCenter_hpp
#define ErrorCenter_hpp

#include <ATL/StdIncludes.hpp>
#include <ATL/Listener.hpp>
#include <ATL/Error.hpp>

namespace atl
{
    ////////////////////////////////////////////////////////////
    /// \brief Describe a static ErrorCenter interface to catch
    /// errors and exceptions through other user's created listeners.
    ///
    ////////////////////////////////////////////////////////////
    class ErrorCenter
    {
        ////////////////////////////////////////////////////////////
        static ErrorCenter s_center ; ///< Static instance of the ErrorCenter.
        
        ////////////////////////////////////////////////////////////
        Emitter m_emitter ; ///< Emitter used to send ErrorEvents to the listeners.
        
    public:
        
        ////////////////////////////////////////////////////////////
        /// \brief Catches an exception and create an ExceptionErrorEvent from
        /// the given exception, error code and format a message by using
        /// vsnprintf.
        ///
        ////////////////////////////////////////////////////////////
        static void CatchException( std::exception const& exception , Error errcode , const char* format , ... );
        
        ////////////////////////////////////////////////////////////
        /// \brief Catches an error and create an ErrorEvent from the
        /// given error code and format a message by using vsnprintf.
        ///
        ////////////////////////////////////////////////////////////
        static void CatchError( Error errcode , const char* format , ... );
        
        ////////////////////////////////////////////////////////////
        /// \brief Add a listener to errors and exceptions catched.
        ///
        ////////////////////////////////////////////////////////////
        static void AddListener( const Shared < Listener >& listener );
        
        ////////////////////////////////////////////////////////////
        /// \brief Reset all listeners.
        ///
        ////////////////////////////////////////////////////////////
        static void ResetListeners();
        
    protected:
        
        ////////////////////////////////////////////////////////////
        ErrorCenter();
        
        ////////////////////////////////////////////////////////////
        ~ErrorCenter();
    };
}

#endif /* ErrorCenter_hpp */
