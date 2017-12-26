//
//  Dynlib.cpp
//  atlresource
//
//  Created by Jacques Tronconi on 23/09/2017.
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//

#include <ATL/Dynlib.hpp>

namespace atl
{
    Dynlib::Dynlib( const Filename & filename ) : iFilename( filename ) , iHandle( nullptr )
    {
        iHandle = DYNLIB_LOAD( filename.GetPath().data() );
    }

    Dynlib::~Dynlib()
    {
        if ( iHandle )
        DYNLIB_UNLOAD( iHandle );
    }

    DYNLIB_HANDLE Dynlib::GetHandle() const
    {
        return iHandle ;
    }

    void Dynlib::Start()
    {
        assert( iHandle && "Invalid dynlib handle." );
        typedef void (*StartFunc) ( void ) ;
        StartFunc fn = (StartFunc) DYNLIB_GETSYM( iHandle , "StartPlugin" );
        assert( fn && "Invalid dynlib 'StartPlugin' function." );
        fn();
    }

    Filename Dynlib::GetFilename() const
    {
        return iFilename ;
    }
    
    bool Dynlib::IsStartable() const
    {
        assert( iHandle && "Invalid dynlib handle." );
        return DYNLIB_GETSYM( iHandle , "StartPlugin" ) != NULL ;
    }
}
