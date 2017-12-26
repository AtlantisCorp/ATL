//  ========================================================================  //
//
//  File    : ATL/VertexComponent.hpp
//  Project : atlresource
//  Author  : Luk2010
//  Date    : 29/10/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#ifndef VertexComponent_hpp
#define VertexComponent_hpp

#include <ATL/StdIncludes.hpp>
#include <ATL/Attribute.hpp>

namespace atl
{
    ////////////////////////////////////////////////////////////
    class Buffer ;
    class CBuffer ;
    
    ////////////////////////////////////////////////////////////
    /// \brief Defines a Vertex Component.
    ///
    /// A VertexCommand is composed of one or more VertexComponent
    /// objects, that describe how the command must be bound to the
    /// current program. Each VertexComponent is linked to a buffer,
    /// and an Attribute which will be used by the Program's VertexLayout
    /// to bind the buffer to the correct slot.
    ///
    /// When a VertexComponent is added to a Mesh, 'm_cbuffer' field
    /// is used to know which CBuffer is related to this VertexComponent.
    /// When generating VertexCommands, the VertexComponent will pass the
    /// corresponding generated Buffer from the CBuffer previously given.
    /// This also implies the VertexComponent in the VertexCommand holds its
    /// own Buffers, but never own the CBuffers related to it.
    ///
    ////////////////////////////////////////////////////////////
    class VertexComponent
    {
        
    public:
        
        ////////////////////////////////////////////////////////////
        /// \brief Often used type for those components.
        ///
        ////////////////////////////////////////////////////////////
        enum
        {
            Unknown             = 0 ,
            
            R32Float ,
            R32G32Float ,
            R32G32B32Float ,
            R32G32B32A32Float ,
            
            R32Uint ,
            R32G32Uint ,
            R32G32B32Uint ,
            R32G32B32A32Uint ,
            
            R32Sint ,
            R32G32Sint ,
            R32G32B32Sint ,
            R32G32B32A32Sint ,
            
            Position4           = R32G32B32A32Float ,
            Position3           = R32G32B32Float ,
            Normal4             = R32G32B32A32Float ,
            Normal3             = R32G32B32Float ,
            Texture2            = R32G32Float ,
            Bitangent3          = R32G32B32Float ,
            Bitangent4          = R32G32B32A32Float ,
            Color3              = R32G32B32Float ,
            Color4              = R32G32B32A32Float 
        };
        
        ////////////////////////////////////////////////////////////
        /// \brief Return the number of element for the given component
        /// type.
        ///
        ////////////////////////////////////////////////////////////
        static size_t GetElementCountFor( uint32_t type );
        
    private:
        
        ////////////////////////////////////////////////////////////
        Atomic < Attribute > m_attrib ;  ///< Attribute linked for this component.
        Atomic < uint32_t >  m_type ;    ///< Type from above enumeration.
        Atomic < size_t >    m_elcount ; ///< Number of elements in the component. This parameter is deduced from
                                         ///  the static 'GetElementCountFor()' function.
        Atomic < uintptr_t > m_stride ;  ///< Stride between two elements (size of the Vertex structure).
        Atomic < uintptr_t > m_offset ;  ///< Offset pointing to the begining of the elements.
        Shared < Buffer >    m_buffer ;  ///< Buffer associated to this component. (in VertexCommand)
        Weak < CBuffer >     m_cbuffer ; ///< CBuffer associated to this component. (in Mesh or any not used by VertexCommand)
        
    public:
        
        ////////////////////////////////////////////////////////////
        VertexComponent( Attribute attrib , uint32_t type ,
                         uintptr_t stride , uintptr_t offset ,
                         const Shared < Buffer >& buffer );
        
        ////////////////////////////////////////////////////////////
        VertexComponent( Attribute attrib , uint32_t type ,
                         uintptr_t stride , uintptr_t offset ,
                         const Weak < CBuffer >& cbuffer );
        
        ////////////////////////////////////////////////////////////
        VertexComponent( const VertexComponent& component );
        
        ////////////////////////////////////////////////////////////
        VertexComponent& operator = ( const VertexComponent& rhs );
        
        ////////////////////////////////////////////////////////////
        virtual ~VertexComponent();
        
        ////////////////////////////////////////////////////////////
        Attribute GetAttribute() const ;
        
        ////////////////////////////////////////////////////////////
        uint32_t GetType() const ;
        
        ////////////////////////////////////////////////////////////
        size_t GetElementCount() const ;
        
        ////////////////////////////////////////////////////////////
        uintptr_t GetStride() const ;
        
        ////////////////////////////////////////////////////////////
        uintptr_t GetOffset() const ;
        
        ////////////////////////////////////////////////////////////
        const Weak < Buffer > GetBuffer() const ;
        
        ////////////////////////////////////////////////////////////
        void SetBuffer( const Shared < Buffer >& buffer );
        
        ////////////////////////////////////////////////////////////
        const Weak < CBuffer > GetCBuffer() const ;
    };
}

#endif /* VertexComponent_hpp */
