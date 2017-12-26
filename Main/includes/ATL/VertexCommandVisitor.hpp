//  ========================================================================  //
//
//  File    : ATL/VertexCommandVisitor.hpp
//  Project : atlresource
//  Author  : Luk2010
//  Date    : 18/11/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#ifndef VertexCommandVisitor_hpp
#define VertexCommandVisitor_hpp

#include <ATL/StdIncludes.hpp>

namespace atl
{
    ////////////////////////////////////////////////////////////
    class Context ;
    class VertexCommand ;
    
    ////////////////////////////////////////////////////////////
    /// \brief A simple visitor to visit the VertexCommand object.
    ///
    /// Visitor for the VertexCommand can visit and modify 'm_ctxtdata'
    /// field without the VertexCommand permission ('m_ctxtdata' is
    /// mutable). However, the visitor must have been constructed by
    /// a Context (or its derived) object.
    ///
    /// Derive from this class to create visitors to set or get current
    /// custom context data from the drawable vertex command in Context::DrawVertexCommand
    /// and optimize your rendering upon this data. It may also serve to
    /// cache some little structures for each VertexCommand. 
    ///
    ////////////////////////////////////////////////////////////
    class VertexCommandVisitor
    {
        ////////////////////////////////////////////////////////////
        friend class Context ;
        
    protected:
        
        ////////////////////////////////////////////////////////////
        VertexCommandVisitor();
        
        ////////////////////////////////////////////////////////////
        void*& GetContextData( const VertexCommand& command );
        
    public:
        
        ////////////////////////////////////////////////////////////
        virtual ~VertexCommandVisitor();
        
        ////////////////////////////////////////////////////////////
        virtual void Visit( const VertexCommand& command ) = 0 ;
    };
}

#endif /* VertexCommandVisitor_hpp */
