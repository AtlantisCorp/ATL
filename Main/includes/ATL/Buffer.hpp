//  ========================================================================  //
//
//  File    : ATL/Buffer.hpp
//  Project : atlresource
//  Author  : Luk2010
//  Date    : 25/10/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#ifndef Buffer_hpp
#define Buffer_hpp

#include <ATL/StdIncludes.hpp>
#include <ATL/IDGenerator.hpp>

namespace atl
{
    ////////////////////////////////////////////////////////////
    /// \brief Local identifier.
    ///
    ////////////////////////////////////////////////////////////
    typedef unsigned long long BufferId ;
    
    ////////////////////////////////////////////////////////////
    /// \brief Interface for a driver-created buffer.
    ///
    /// Generally this buffer is hold on the GPU memory. It is
    /// bound before use, unbound after use, and data can be modified
    /// or accessed using 'Map'. However, using 'Map' is not recommended
    /// as it may imply a synchronization between CPU and GPU.
    ///
    ////////////////////////////////////////////////////////////
    class Buffer
    {
        ////////////////////////////////////////////////////////////
        static IDGenerator < BufferId > s_generator ;
        
        ////////////////////////////////////////////////////////////
        Atomic < BufferId > m_id ; ///< Buffer local id.
        
    public:
        
        ////////////////////////////////////////////////////////////
        Buffer();
        
        ////////////////////////////////////////////////////////////
        virtual ~Buffer();
        
        ////////////////////////////////////////////////////////////
        /// \brief Make the buffer usable.
        ///
        ////////////////////////////////////////////////////////////
        virtual void Bind() = 0 ;
        
        ////////////////////////////////////////////////////////////
        /// \brief Make the buffer unusable.
        ///
        ////////////////////////////////////////////////////////////
        virtual void Unbind() = 0 ;
    };
}

#endif /* Buffer_hpp */
