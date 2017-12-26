//  ========================================================================  //
//
//  File    : ATL/IDGenerator.hpp
//  Project : atlresource
//  Author  : Luk2010
//  Date    : 17/10/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#ifndef IDGenerator_hpp
#define IDGenerator_hpp

#include <ATL/StdIncludes.hpp>

namespace atl
{
    ////////////////////////////////////////////////////////////
    /// \brief Generic local identifier generator.
    ///
    ////////////////////////////////////////////////////////////
    template < typename IdClass >
    class IDGenerator
    {
        Atomic < IdClass > m_curid ; ///< Current ID. Initialized by value 1. Invalid value is 0.
        
    public:
        
        ////////////////////////////////////////////////////////////
        IDGenerator() : m_curid( 1 ) { }
        
        ////////////////////////////////////////////////////////////
        ~IDGenerator() { }
        
        ////////////////////////////////////////////////////////////
        /// \brief (Pre)Generates a new ID and returns the previous id.
        ///
        ////////////////////////////////////////////////////////////
        IdClass New()
        {
            return m_curid.fetch_add( 1 , std::memory_order_relaxed );
        }
    };
}

#endif /* IDGenerator_hpp */
