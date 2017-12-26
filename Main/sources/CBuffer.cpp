//
//  CBuffer.cpp
//  atlresource
//
//  Created by Jacques Tronconi on 24/09/2017.
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//

#include <ATL/CBuffer.hpp>

namespace atl
{
    ////////////////////////////////////////////////////////////
    CBuffer::CBuffer()
    {
        iBufSize = 0 ;
        iBufData = nullptr ;
    }
    
    ////////////////////////////////////////////////////////////
    CBuffer::CBuffer( const CBuffer & rhs )
    {
        iBufSize = rhs.iBufSize ;
        iBufData = nullptr ;
        
        if ( iBufSize )
        {
            iBufData = malloc( iBufSize );
            assert( iBufData && "Can't allocate data." );
            
            memcpy( iBufData , rhs.iBufData , iBufSize );
        }
    }
    
    ////////////////////////////////////////////////////////////
    CBuffer::CBuffer( CBuffer&& rhs )
    {
        iBufSize = rhs.iBufSize ;
        iBufData = rhs.iBufData ;
        
        rhs.iBufSize = 0 ;
        rhs.iBufData = nullptr ;
    }
    
    ////////////////////////////////////////////////////////////
    CBuffer::CBuffer( const void* rd , size_t rs )
    {
        iBufSize = rs ;
        iBufData = nullptr ;
        
        if ( iBufSize )
        {
            iBufData = malloc( iBufSize );
            assert( iBufData && "Can't allocate data." );
            
            memcpy( iBufData , rd , iBufSize );
        }
    }
    
    ////////////////////////////////////////////////////////////
    CBuffer::~CBuffer()
    {
        if ( iBufSize )
        {
            assert( iBufData && "Invalid buffer." );
            free( iBufData );
        }
    }
    
    ////////////////////////////////////////////////////////////
    void CBuffer::Swap( CBuffer& rhs )
    {
        std::swap( iBufSize , rhs.iBufSize );
        std::swap( iBufData , rhs.iBufData );
    }
    
    ////////////////////////////////////////////////////////////
    void CBuffer::Set( const CBuffer& rhs )
    {
        Clear();
        
        iBufSize = rhs.iBufSize ;
        iBufData = nullptr ;
        
        if ( iBufSize )
        {
            iBufData = malloc( iBufSize );
            assert( iBufData && "Can't allocate data." );
            
            memcpy( iBufData , rhs.iBufData , iBufSize );
        }
    }
    
    ////////////////////////////////////////////////////////////
    void CBuffer::Clear()
    {
        if ( iBufSize )
        {
            assert( iBufData && "Invalid buffer." );
            free( iBufData );
        }
        
        iBufSize = 0 ;
        iBufData = nullptr ;
    }
    
    ////////////////////////////////////////////////////////////
    void CBuffer::Assign( void* data , size_t sz )
    {
        Clear();
        iBufSize = sz ;
        iBufData = data ;
    }
    
    ////////////////////////////////////////////////////////////
    void* CBuffer::GetData() { return iBufData ; }
    
    ////////////////////////////////////////////////////////////
    const void* CBuffer::GetData() const { return iBufData ; }
    
    ////////////////////////////////////////////////////////////
    char* CBuffer::begin() { return static_cast < char* >( iBufData ); }
    
    ////////////////////////////////////////////////////////////
    const char* CBuffer::begin() const { return static_cast < const char* >( iBufData ); }
    
    ////////////////////////////////////////////////////////////
    const char* CBuffer::end() const { return static_cast < const char* >( iBufData ) + iBufSize ; }
    
    ////////////////////////////////////////////////////////////
    size_t CBuffer::GetSize() const { return iBufSize ; }
    
    ////////////////////////////////////////////////////////////
    bool CBuffer::Empty() const { return iBufSize == 0 ; }
    
    ////////////////////////////////////////////////////////////
    CBuffer& CBuffer::operator = ( const CBuffer& rhs )
    {
        Set( rhs );
        return *this ;
    }
    
    ////////////////////////////////////////////////////////////
    bool CBuffer::operator == ( const CBuffer& rhs ) const { return iBufData == rhs.iBufData ; }
    
    ////////////////////////////////////////////////////////////
    bool CBuffer::operator != ( const CBuffer& rhs ) const { return iBufData != rhs.iBufData ; }
}
