//  ========================================================================  //
//
//  File    : ATL/Instanced.hpp
//  Project : atlresource
//  Author  : Luk2010
//  Date    : 14/11/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#ifndef Instanced_hpp
#define Instanced_hpp

#include <ATL/StdIncludes.hpp>

namespace atl
{
    ////////////////////////////////////////////////////////////
    /// \brief Makes a Class instanciable by the Root object.
    ///
    ////////////////////////////////////////////////////////////
    template < typename Class >
    class Instanced
    {
        ////////////////////////////////////////////////////////////
        static Weak < Class > s_instance ;
        
    public:
        
        ////////////////////////////////////////////////////////////
        static void Set( const Shared < Class >& instance )
        {
            s_instance = instance ;
        }
        
        ////////////////////////////////////////////////////////////
        static Shared < Class > Get()
        {
            return s_instance.lock();
        }
        
        ////////////////////////////////////////////////////////////
        static bool IsInstanced()
        {
            return !s_instance.expired();
        }
    };
    
    ////////////////////////////////////////////////////////////
    template < typename Class >
    Weak < Class > Instanced < Class > :: s_instance = Weak < Class >();
}

#endif /* Instanced_hpp */
