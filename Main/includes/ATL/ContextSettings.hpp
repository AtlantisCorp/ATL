//  ========================================================================  //
//
//  File    : ATL/ContextSettings.hpp
//  Project : atlresource
//  Author  : Luk2010
//  Date    : 09/10/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //

#ifndef ContextSettings_h
#define ContextSettings_h

#include <ATL/StdIncludes.hpp>

namespace atl
{
    ////////////////////////////////////////////////////////////
    /// \brief Defines Context settings available when creating
    /// a context by using a Driver implementation.
    ///
    ////////////////////////////////////////////////////////////
    class ContextSettings
    {
    public:
        
        ////////////////////////////////////////////////////////////
        bool     doublebuffered ;  ///< True if context should be double-buffered.
        uint32_t depthbits ;       ///< 0 if default value, otherwise counts for the number of depth bits.
        bool     accelerated ;     ///< Force accelerated-only contextes if true.
        bool     multisampled ;    ///< Flag indicating if multisample context must be created. (Default is false)
        int32_t  samplesbuffers ;  ///< If 'multisampled' is true, indicates the number of buffers to perform multisampling. (Default is 1)
        int32_t  samples ;         ///< If 'multisampled' is true, indicates the number of samples to perform multisampling. (Default is 4)
        
        ////////////////////////////////////////////////////////////
        /// \brief Return a default context setting that can be used
        /// as a base to create a new context.
        ///
        ////////////////////////////////////////////////////////////
        static ContextSettings Default();
    };
}

#endif /* ContextSettings_h */
