//  ========================================================================  //
//
//  File    : ATL/VertexCommand.hpp
//  Project : atlresource
//  Author  : Luk2010
//  Date    : 17/10/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#ifndef VertexCommand_hpp
#define VertexCommand_hpp

#include <ATL/StdIncludes.hpp>
#include <ATL/IDGenerator.hpp>
#include <ATL/Buffer.hpp>
#include <ATL/IndexType.hpp>
#include <ATL/VertexComponent.hpp>

namespace atl
{
    ////////////////////////////////////////////////////////////
    class VertexCommandVisitor ;
    
    ////////////////////////////////////////////////////////////
    /// \brief Local unique identifier.
    ///
    ////////////////////////////////////////////////////////////
    typedef unsigned long long VertexCommandId ;
    
    ////////////////////////////////////////////////////////////
    /// \brief Simple structure to describe how a batch of vertexs
    /// should be drawed by a driver.
    ///
    /// A VertexCommand does know the number of vertexes, and the
    /// data that point to the vertex (and the indexes if needed).
    /// However, it does not know the layout structure for those
    /// vertex, because the vertex layout (or known as the input
    /// layout) is linked to the program it refers to. The layout
    /// is bound by the program when drawing the vertex command.
    ///
    /// A vertex command must match the program's layout. If it does
    /// not match, behaviour is undefined as partial data is sent to
    /// the program.
    ///
    /// \note Multithreaded access is performed by using only atomic
    /// operations on every VertexCommand's data. Atomic operations
    /// are faster than mutex locking/unlocking, and permits multiple
    /// threads to access different VertexCommand's data at the same
    /// time. However, atomic operations on weak pointers might not
    /// be lock-free. Furthermore, as a VertexCommand might have more
    /// than one buffer, a spinlock is used to access the vector.
    ///
    /// \note VertexCommand owns its buffers. As VertexCommands are
    /// created with a RenderWindow but by, for example, a Mesh, the
    /// VertexCommand holds the created renderwindow's specific buffers
    /// and the Mesh holds the CBuffer used to generate this command.
    ///
    ////////////////////////////////////////////////////////////
    class VertexCommand
    {
        ////////////////////////////////////////////////////////////
        friend class VertexCommandVisitor ;
        
        ////////////////////////////////////////////////////////////
        static IDGenerator < VertexCommandId > s_generator ;
        
        ////////////////////////////////////////////////////////////
        Atomic < VertexCommandId > m_id ;       ///< Local identifier.
        Vector < VertexComponent > m_comps ;    ///< VertexComponents for this command.
        Atomic < uint32_t >        m_count ;    ///< Number of Vertexes to draw. 
        Atomic < uint32_t >        m_icount ;   ///< Number of indexes (optional).
        Atomic < IndexType >       m_itype ;    ///< Type of indexes (optional).
        Shared < Buffer >          m_ibuffer ;  ///< Index buffer (optional).
        mutable Spinlock           m_spinlock ; ///< Access to vector of vertex components.
        mutable void*              m_ctxtdata ; ///< External data allocated by the Context with a VertexCommandVisitor.
                                                ///  VertexCommand's data are specific from the Context it is used with.
                                                ///  Contextes must uses Visitors to modify this field, which is always
                                                ///  nullptr at creation.
        
    public:
        
        ////////////////////////////////////////////////////////////
        VertexCommand();
        
        ////////////////////////////////////////////////////////////
        /// \brief Creates a VertexCommand initializing its parameters.
        ///
        ////////////////////////////////////////////////////////////
        VertexCommand( uint32_t count , const VertexComponent& buffer ,
                       uint32_t icount = 0 , const Shared < Buffer >& ibuf = nullptr ,
                       IndexType itype = IndexType::Unknown );
        
        ////////////////////////////////////////////////////////////
        /// \brief Creates a VertexCommand with more than one vertex buffer.
        ///
        ////////////////////////////////////////////////////////////
        VertexCommand( uint32_t count , const Vector < VertexComponent >& buffers ,
                       uint32_t icount = 0 , const Shared < Buffer >& ibuf = nullptr ,
                       IndexType itype = IndexType::Unknown );
        
        ////////////////////////////////////////////////////////////
        virtual ~VertexCommand();
        
        ////////////////////////////////////////////////////////////
        virtual VertexCommandId GetId() const ;
        
        ////////////////////////////////////////////////////////////
        /// \brief Return the number of Vertex.
        ///
        ////////////////////////////////////////////////////////////
        uint32_t GetVertexCount() const ;
        
        ////////////////////////////////////////////////////////////
        /// \brief Changes the number of Vertex in this command.
        ///
        ////////////////////////////////////////////////////////////
        void SetVertexCount( uint32_t count );
        
        ////////////////////////////////////////////////////////////
        /// \brief Return the vertex components.
        ///
        ////////////////////////////////////////////////////////////
        Vector < VertexComponent > GetVertexComponents() const ;
        
        ////////////////////////////////////////////////////////////
        /// \brief Change the vertex components.
        ///
        ////////////////////////////////////////////////////////////
        void SetVertexComponents( const Vector < VertexComponent >& components );
        
        ////////////////////////////////////////////////////////////
        void AddVertexComponent( const VertexComponent& component );
        
        ////////////////////////////////////////////////////////////
        /// \brief Return the number of indexes.
        ///
        ////////////////////////////////////////////////////////////
        uint32_t GetIndexCount() const ;
        
        ////////////////////////////////////////////////////////////
        /// \brief Changes the number of Indexes in this command.
        ///
        ////////////////////////////////////////////////////////////
        void SetIndexCount( uint32_t count );
        
        ////////////////////////////////////////////////////////////
        /// \brief Return the index buffer.
        ///
        ////////////////////////////////////////////////////////////
        Weak < Buffer > GetIndexBuffer() const ;
        
        ////////////////////////////////////////////////////////////
        /// \brief Change the index buffer.
        ///
        ////////////////////////////////////////////////////////////
        void SetIndexBuffer( const Shared < Buffer >& buffer );
        
        ////////////////////////////////////////////////////////////
        /// \brief Return the index type.
        ///
        ////////////////////////////////////////////////////////////
        IndexType GetIndexType() const ;
        
        ////////////////////////////////////////////////////////////
        /// \brief Change the index's type.
        ///
        ////////////////////////////////////////////////////////////
        void SetIndexType( IndexType type );
        
        ////////////////////////////////////////////////////////////
        /// \brief Accepts the Context's created visitor to read/write
        /// 'm_ctxtdata' field.
        ///
        /// During this operation the command's mutex is locked and the
        /// visitor is free to access the internal data.
        ///
        ////////////////////////////////////////////////////////////
        void AcceptVisitor( VertexCommandVisitor& visitor ) const ;
    };
}

#endif /* VertexCommand_hpp */
