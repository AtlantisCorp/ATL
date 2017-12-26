//  ========================================================================  //
//
//  File    : ATL/VaryingParameter.hpp
//  Project : atlresource
//  Author  : Luk2010
//  Date    : 28/10/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#ifndef VaryingParameter_hpp
#define VaryingParameter_hpp

#include <ATL/StdIncludes.hpp>
#include <ATL/Alias.hpp>
#include <ATL/ParameterValue.hpp>

namespace atl
{
    ////////////////////////////////////////////////////////////
    /// \brief A Varying parameter for Program.
    ///
    /// A Varying parameter is stored with a shared pointer, is
    /// modified and accessed using a spinlock lock but no copy
    /// occurs when updating the program.
    ///
    /// As Program uses ConstantParameters to store its own parameters,
    /// when binding a parameter, the program looks for its own parameter
    /// to bind it with this parameter's value. Getting alias and index
    /// is a lock-free operation (using atomic's operations) and thus is
    /// faster than getting the parameter's name, that require a spinlock
    /// locking.
    ///
    ////////////////////////////////////////////////////////////
    class VaryingParameter
    {
        ////////////////////////////////////////////////////////////
        Atomic < Alias >   m_alias ;    ///< Alias for this parameter.
        String             m_name ;     ///< Name of this parameter.
        Atomic < int32_t > m_index ;    ///< Index of this parameter.
        ParameterValue     m_value ;    ///< Value of this parameter.
        mutable Spinlock   m_spinlock ; ///< Spinlock to access data.
        
    public:
        
        ////////////////////////////////////////////////////////////
        VaryingParameter();
        
        ////////////////////////////////////////////////////////////
        VaryingParameter( const ParameterValue& value , const String& name , int32_t index = -1 );
        
        ////////////////////////////////////////////////////////////
        VaryingParameter( const ParameterValue& value , Alias alias );
        
        ////////////////////////////////////////////////////////////
        ~VaryingParameter();
        
        ////////////////////////////////////////////////////////////
        ParameterValue GetValue() const ;
        
        ////////////////////////////////////////////////////////////
        String GetName() const ;
        
        ////////////////////////////////////////////////////////////
        int32_t GetIndex() const ;
        
        ////////////////////////////////////////////////////////////
        Alias GetAlias() const ;
        
        ////////////////////////////////////////////////////////////
        void SetValue( const ParameterValue& value );
        
        ////////////////////////////////////////////////////////////
        void SetName( const String& name );
        
        ////////////////////////////////////////////////////////////
        void SetIndex( int32_t index );
        
        ////////////////////////////////////////////////////////////
        void SetAlias( Alias alias );
    };
}

#endif /* VaryingParameter_hpp */
