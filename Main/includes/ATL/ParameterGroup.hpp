//  ========================================================================  //
//
//  File    : ATL/ParameterGroup.hpp
//  Project : atlresource
//  Author  : Luk2010
//  Date    : 28/10/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#ifndef ParameterGroup_hpp
#define ParameterGroup_hpp

#include <ATL/StdIncludes.hpp>
#include <ATL/ConstantParameter.hpp>
#include <ATL/VaryingParameter.hpp>

namespace atl
{
    ////////////////////////////////////////////////////////////
    /// \brief Summarize operations on Constant/Varying parameters.
    ///
    ////////////////////////////////////////////////////////////
    class ParameterGroup
    {
        ////////////////////////////////////////////////////////////
        Vector < ConstantParameter >           m_constparams ; ///< Constant parameters for this rendercommand.
        Vector < Shared < VaryingParameter > > m_varparams ;   ///< Varying parameters.
        mutable Mutex                          m_mutex ;       ///< Local mutex.
        
    public:
        
        ////////////////////////////////////////////////////////////
        ParameterGroup();
        
        ////////////////////////////////////////////////////////////
        virtual ~ParameterGroup();
        
        ////////////////////////////////////////////////////////////
        virtual void AddConstParameter( const ConstantParameter& param );
        
        ////////////////////////////////////////////////////////////
        virtual void AddConstParameters( const Vector < ConstantParameter >& params );
        
        ////////////////////////////////////////////////////////////
        virtual void ResetConstParameters();
        
        ////////////////////////////////////////////////////////////
        virtual void AddVarParameter( const Shared < VaryingParameter >& param );
        
        ////////////////////////////////////////////////////////////
        virtual void AddVarParameters( const SharedVector < VaryingParameter >& params );
        
        ////////////////////////////////////////////////////////////
        virtual void ResetVarParameters();
        
        ////////////////////////////////////////////////////////////
        /// \brief Returns a copy of each constant parameters in the
        /// render command.
        ///
        ////////////////////////////////////////////////////////////
        Vector < ConstantParameter > GetConstParameters() const ;
        
        ////////////////////////////////////////////////////////////
        /// \brief Returns a copy of the list to pointers to varying
        /// parameters of this render command.
        ///
        /// As this is a SharedVector, parameters are guaranteed not
        /// to die or expire before utilisation and destruction of the
        /// returned vector.
        ///
        ////////////////////////////////////////////////////////////
        SharedVector < VaryingParameter > GetVarParameters() const ;
    };
}

#endif /* ParameterGroup_hpp */
