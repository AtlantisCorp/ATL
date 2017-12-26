//  ========================================================================  //
//
//  File    : ATL/CBuffer.hpp
//  Project : atlresource
//  Author  : Luk2010
//  Date    : 24/09/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //

#ifndef CBuffer_hpp
#define CBuffer_hpp

#include <ATL/StdIncludes.hpp>

namespace atl
{
    ////////////////////////////////////////////////////////////
    /// \brief Defines a buffer with a generic data type.
    ///
    /// CBuffer size is allocated and deallocated using a simple
    /// malloc/free process. Only data that doesn't need to be
    /// constructed can be allocated this way.
    ///
    ////////////////////////////////////////////////////////////
    class CBuffer
    {
        size_t iBufSize ; ///< Size of the buffer, in bytes.
        void*  iBufData ; ///< Pointer to the buffer's data.
        
    public:
        
        ////////////////////////////////////////////////////////////
        CBuffer();
        
        ////////////////////////////////////////////////////////////
        CBuffer( const CBuffer & rhs );
        
        ////////////////////////////////////////////////////////////
        CBuffer( CBuffer&& rhs );
        
        ////////////////////////////////////////////////////////////
        CBuffer( const void* rd , size_t rs );
        
        ////////////////////////////////////////////////////////////
        virtual ~CBuffer();
        
        ////////////////////////////////////////////////////////////
        virtual void Swap( CBuffer& rhs );
        
        ////////////////////////////////////////////////////////////
        virtual void Set( const CBuffer& rhs );
        
        ////////////////////////////////////////////////////////////
        virtual void Clear();
        
        ////////////////////////////////////////////////////////////
        virtual void Assign( void* data , size_t sz );
        
        ////////////////////////////////////////////////////////////
        virtual void* GetData();
        
        ////////////////////////////////////////////////////////////
        virtual const void* GetData() const ;
        
        ////////////////////////////////////////////////////////////
        virtual char* begin();
        
        ////////////////////////////////////////////////////////////
        virtual const char* begin() const ;
        
        ////////////////////////////////////////////////////////////
        virtual const char* end() const ;
        
        ////////////////////////////////////////////////////////////
        virtual size_t GetSize() const ;
        
        ////////////////////////////////////////////////////////////
        virtual bool Empty() const ;
        
        ////////////////////////////////////////////////////////////
        CBuffer& operator = ( const CBuffer& rhs );
        
        ////////////////////////////////////////////////////////////
        bool operator == ( const CBuffer& rhs ) const ;
        
        ////////////////////////////////////////////////////////////
        bool operator != ( const CBuffer& rhs ) const ;
    };
}

#endif /* CBuffer_hpp */
