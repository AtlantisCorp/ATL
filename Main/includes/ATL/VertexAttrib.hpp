//  ========================================================================  //
//
//  File    : ATL/VertexAttrib.hpp
//  Project : atlresource
//  Author  : Luk2010
//  Date    : 13/11/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#ifndef VertexAttrib_hpp
#define VertexAttrib_hpp

#include <ATL/StdIncludes.hpp>

namespace atl
{
    ////////////////////////////////////////////////////////////
    /// \brief Represents a slot or an avaible input attribute in
    /// a program, that can be used as an input for streaming data.
    ///
    /// VertexAttributes are created by the Program object. They are
    /// associated to a unique slot (or index). Each Attribute can then
    /// be associated to one of this attribute.
    ///
    ////////////////////////////////////////////////////////////
    class VertexAttrib
    {
        ////////////////////////////////////////////////////////////
        Atomic < uint32_t > m_slot ;     ///< Slot representing the attribute in the program object.
        Atomic < uint32_t > m_type ;     ///< [Optional] Represents the VertexComponent type expected for this slot. A Program
                                         ///  object can perform an optional type check when binding a VertexComponent to this
                                         ///  attribute by using this type.
        String              m_name ;     ///< Name given for this attribute.
        mutable Spinlock    m_spinlock ; ///< Spinlock used to access data.
        
    public:
        
        ////////////////////////////////////////////////////////////
        VertexAttrib( uint32_t slot , const String& name , uint32_t type );
        
        ////////////////////////////////////////////////////////////
        VertexAttrib( const VertexAttrib& rhs );
        
        ////////////////////////////////////////////////////////////
        ~VertexAttrib();
        
        ////////////////////////////////////////////////////////////
        uint32_t GetSlot() const ;
        
        ////////////////////////////////////////////////////////////
        uint32_t GetType() const ;
        
        ////////////////////////////////////////////////////////////
        String GetName() const ;
    };
}

#endif /* VertexAttrib_hpp */
