//  ========================================================================  //
//
//  File    : ATL/VertexLayout.hpp
//  Project : atlresource
//  Author  : Luk2010
//  Date    : 29/10/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#ifndef VertexLayout_hpp
#define VertexLayout_hpp

#include <ATL/StdIncludes.hpp>
#include <ATL/VertexAttrib.hpp>
#include <ATL/Attribute.hpp>

namespace atl
{
    ////////////////////////////////////////////////////////////
    /// \brief Defines an input layout for a program.
    ///
    /// The input layout is a list of attributes or slots available
    /// to the user, and does not relate with the actual attributes
    /// aliases used by the user to stream data.
    /// A VertexLayout links the Attribute with the VertexAttrib object
    /// that hold the actual name or index (slot) of the attribute in
    /// the program object.
    ///
    /// \see VertexAttrib, Attribute, VertexComponent, Program.
    ///
    ////////////////////////////////////////////////////////////
    class VertexLayout
    {
        ////////////////////////////////////////////////////////////
        Vector < VertexAttrib >           m_attribs ;        ///< VertexAttribs for that layout.
        Map < Attribute , VertexAttrib* > m_attribsbyalias ; ///< Association between alias and attribs.
        mutable Mutex                     m_mutex ;          ///< Mutex to access vector and map.
        
    public:
        
        ////////////////////////////////////////////////////////////
        VertexLayout();
        
        ////////////////////////////////////////////////////////////
        VertexLayout( const Vector < VertexAttrib >& attribs );
        
        ////////////////////////////////////////////////////////////
        virtual ~VertexLayout();
        
        ////////////////////////////////////////////////////////////
        /// \brief Sets the given attribute for given slot.
        ///
        /// \param attribute Arbitrary attribute to associate with.
        /// \param slot      A valid slot found in a VertexAttrib. If
        ///                  this slot is not valid, no association is
        ///                  done and the function return false.
        /// \param type      It not zero, check if the VertexAttrib's type
        ///                  match this type. No association is done if types
        ///                  mismatch.
        ///
        /// \return true if the association is done.
        ///
        ////////////////////////////////////////////////////////////
        bool SetAttribute( Attribute attribute , uint32_t slot , uint32_t type = 0 );
        
        ////////////////////////////////////////////////////////////
        /// \brief Sets the given attribute for given name.
        ///
        /// \param attribute Arbitrary attribute to associate with.
        /// \param name      A valid name indicating a VertexAttrib. If
        ///                  this name is invalid, no association is done
        ///                  and the function return false.
        /// \param type      It not zero, check if the VertexAttrib's type
        ///                  match this type. No association is done if types
        ///                  mismatch.
        ///
        ////////////////////////////////////////////////////////////
        bool SetAttribute( Attribute attribute , const String& slot , uint32_t type = 0 );
        
        ////////////////////////////////////////////////////////////
        /// \brief Returns the VertexAttrib associated for given Attribute,
        /// or null if none was found.
        ///
        ////////////////////////////////////////////////////////////
        const VertexAttrib* GetAttribute( Attribute attribute ) const ;
        
        ////////////////////////////////////////////////////////////
        /// \brief Manually adds a VertexAttrib to this layout.
        ///
        ////////////////////////////////////////////////////////////
        void AddVertexAttrib( const VertexAttrib& attrib );
    };
}

#endif /* VertexLayout_hpp */
