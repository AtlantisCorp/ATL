//  ========================================================================  //
//
//  File    : ATL/Mesh.hpp
//  Project : atlresource
//  Author  : Luk2010
//  Date    : 25/10/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#ifndef Mesh_hpp
#define Mesh_hpp

#include <ATL/StdIncludes.hpp>
#include <ATL/Resource.hpp>
#include <ATL/VertexCommand.hpp>
#include <ATL/CBuffer.hpp>
#include <ATL/Material.hpp>
#include <ATL/IndexType.hpp>

namespace atl
{
    ////////////////////////////////////////////////////////////
    class RenderWindow ;
    
    ////////////////////////////////////////////////////////////
    /// \brief A Mesh is, basically, a renderwindow attached object
    /// that generate VertexCommands from an externally loaded buffer
    /// file.
    ///
    /// A Mesh is always loaded from a descriptive file. This allows it
    /// to be a Resource object, constructible with Metaclass system.
    /// A Mesh constructs its buffers in the RAM, and generate its
    /// VertexCommands in the 'GenVertexCommands()'. VertexCommands
    /// are specific to the RenderWindow's Context used to generate those
    /// commands and thus, unrelated other Contextes can't use those
    /// VertexCommands to draw the mesh.
    ///
    /// A Mesh currently hold its RAM Vertex Buffers, its RAM Index
    /// Buffer, its default Material, and if applicable, its submeshes.
    /// It also own its generated VertexCommand, linked to the Context
    /// corresponding to the given RenderWindow.
    ///
    ////////////////////////////////////////////////////////////
    class Mesh : public Resource
    {
        ////////////////////////////////////////////////////////////
        Shared < VertexCommand > m_command ;   ///< Local VertexCommand of this mesh. If the mesh has submeshes,
                                               ///  it is very likely that this vertex command is null or represents
                                               ///  only debugging data like bounding boxes, etc. 'GetVertexCommands()'
                                               ///  will return sub meshes VertexCommands plus this one.
        
        Vector < VertexComponent > m_comps ;   ///< Vertex Components to bind in the VertexCommand.
        SharedVector < CBuffer > m_vbufs ;     ///< Local vertex buffers. See 'm_command'.
        Atomic < uint32_t >      m_vcount ;    ///< Number of local vertexs. See 'm_command'.
        
        Shared < CBuffer >       m_ibuf ;      ///< Local index buffer. See 'm_command'.
        Atomic < uint32_t >      m_icount ;    ///< Number of local indexes. See 'm_command'.
        IndexType                m_itype ;     ///< Type of index buffer. (default is IndexType::UI32)
        
        Weak < Material >        m_material ;  ///< Local default material. See 'm_command'.
        SharedVector < Mesh >    m_submeshes ; ///< Sub meshes. They should be created only if more than one VertexCommand
                                               ///  is needed. Generally this is the case when a structured mesh has more than
                                               ///  one material to describe itself.
        
        Atomic < bool >          m_dirty ;     ///< If true, the Mesh should recall 'GenVertexCommands()' because itself or
                                               ///  one of its submesh has been changed and thus, the VertexCommands are not
                                               ///  representative of the mesh's data.
        
        mutable Mutex            m_mutex ;     ///< Access all data.
        
    public:
        
        ////////////////////////////////////////////////////////////
        /// \brief Constructs an empty mesh.
        ///
        ////////////////////////////////////////////////////////////
        Mesh();
        
        ////////////////////////////////////////////////////////////
        virtual ~Mesh();
        
        ////////////////////////////////////////////////////////////
        /// \brief Adds a Vertex CBuffer in this mesh, along with its
        /// recommended VertexComponent description.
        ///
        /// \param buffer    A RAM owned buffer to hold the buffer data.
        /// \param component A VertexComponent describing how to use
        ///                  this buffer. When generating VertexCommands,
        ///                  this component will be added to use this buffer.
        ///
        /// \note If the buffer is already in the mesh, it is not added
        /// and the vertex component is added to the components lists.
        ///
        ////////////////////////////////////////////////////////////
        virtual void AddVertexCBuffer( const Shared < CBuffer >& buffer , const VertexComponent& component );
        
        ////////////////////////////////////////////////////////////
        /// \brief Adds a Vertex CBuffer.
        ///
        /// \param buffer A RAM owned buffer to hold the data.
        ///
        /// \note Given buffer is not usable because no Vertex Component
        /// is provided to use it. A VertexComponent must be added to the
        /// Mesh by using 'AddVertexComponent', with the previously added
        /// cbuffer.
        ///
        ////////////////////////////////////////////////////////////
        virtual void AddVertexCBuffer( const Shared < CBuffer >& buffer );
        
        ////////////////////////////////////////////////////////////
        /// \brief Adds a VertexComponent related to a CBuffer.
        ///
        /// \param component A CBuffer related VertexComponent. You can
        ///                  add more than one component for the same buffer,
        ///                  as the buffer will be associated to a slot in the
        ///                  future program's VertexLayout.
        ///
        /// \note component's CBuffer must have been added to the mesh in
        /// order to generate Buffer's related VertexComponents in the final
        /// VertexCommand.
        ///
        ////////////////////////////////////////////////////////////
        virtual void AddVertexComponent( const VertexComponent& component );
        
        ////////////////////////////////////////////////////////////
        /// \brief Sets the number of Vertexes to be drawed by the related
        /// VertexCommand.
        ///
        /// \param count Number of Vertexes to draw. If this number is superior
        ///              to the real number of Vertexes in the different CBuffers,
        ///              related to their VertexComponents description, the behaviour
        ///              is undefined.
        ///
        ////////////////////////////////////////////////////////////
        virtual void SetVertexCount( uint32_t count );
        
        ////////////////////////////////////////////////////////////
        /// \brief Changes the Index CBuffer related to this Mesh.
        ///
        /// \param buffer Buffer with indexes data.
        /// \param count  Number of indexes to draw using this buffer.
        /// \param type   Indexes' type.
        ///
        /// \see IndexType
        ///
        ////////////////////////////////////////////////////////////
        virtual void SetIndexCBuffer( const Shared < CBuffer >& buffer , uint32_t count , IndexType type );
        
        ////////////////////////////////////////////////////////////
        /// \brief Changes the Mesh's default Material.
        ///
        /// \note If the whole Mesh has more than one Material, consider
        /// using submeshes with, for each, a different Material.
        ///
        ////////////////////////////////////////////////////////////
        virtual void SetMaterial( const Weak < Material >& material );
        
        ////////////////////////////////////////////////////////////
        /// \brief Generates VertexCommands for this mesh and its
        /// submeshes, if applicable.
        ///
        /// \param renderwindow As creating VertexCommands is dependent
        /// from the main renderwindow, generation take a main renderwindow
        /// to create the vertex commands recursively. Generally only the
        /// buffers are created here and then they are modified.
        /// \param includesubs  Flag to indicate wether to include submeshes's
        /// VertexCommands (value 'true') or not (value 'false', default).
        ///
        /// Generating a VertexCommand is generally done in a LoadingQueue
        /// task. This task is done between 'RenderTarget::Begin()' and
        /// 'RenderTarget::End()'. It is separated from the mesh's constructing
        /// tasks, which are done by mesh's loaders in another (or the same)
        /// LoadingQueue.
        ///
        /// \note Generating VertexCommands will set 'm_dirty' flag to false
        /// and further calls to this function will immediatly return, except if
        /// 'm_dirty' is reset to true.
        ///
        ////////////////////////////////////////////////////////////
        virtual void GenVertexCommands( const Weak < RenderWindow >& window );
        
        ////////////////////////////////////////////////////////////
        /// \brief Adds a submesh to this mesh.
        ///
        ////////////////////////////////////////////////////////////
        virtual void AddSubmesh( const Shared < Mesh >& submesh );
        
        ////////////////////////////////////////////////////////////
        /// \brief Returns generated vertex command for this mesh
        /// and its submeshes.
        ///
        ////////////////////////////////////////////////////////////
        virtual SharedVector < VertexCommand > GetVertexCommands() const ;
        
        ////////////////////////////////////////////////////////////
        /// \brief Return the vertex command for this mesh.
        ///
        ////////////////////////////////////////////////////////////
        virtual Shared < VertexCommand > GetVertexCommand() const ;
    };
}

#endif /* Mesh_hpp */
