//
//  Dynlib.hpp
//  atlresource
//
//  Created by Jacques Tronconi on 23/09/2017.
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//

#ifndef Dynlib_hpp
#define Dynlib_hpp

#include <ATL/StdIncludes.hpp>
#include <ATL/Performer.hpp>
#include <ATL/Filename.hpp>

#if defined(__WINDOWS__)
#   define DYNLIB_HANDLE hInstance
#   define DYNLIB_GETSYM( a, b ) GetProcAddress( a, b )
#   define DYNLIB_LOAD( a ) LoadLibraryEx( a, NULL, LOAD_WITH_ALTERED_SEARCH_PATH )
#   define DYNLIB_UNLOAD( a ) FreeLibrary( a )
#   define DYNLIB_EXTENSION "dll"
#   define DYNLIB_LASTERROR dlerror

    struct HINSTANCE__;
    typedef struct HINSTANCE__ * hInstance;

    /* We provide custom dlerror for Windows(tm).
     * https://mail.python.org/pipermail//pypy-commit/2012-October/066804.html
     */
    static const char *dlerror(void)
    {
        static char buf[32];
        DWORD dw = GetLastError();
        if (dw == 0)
            return NULL;
        sprintf(buf, "error 0x%x", (unsigned int)dw);
        return buf;
    }

#else
#  if defined(__OSX__) || defined (__APPLE__)
#   define DYNLIB_HANDLE void*
#   define DYNLIB_GETSYM( a, b ) dlsym( a, b )
#   define DYNLIB_LOAD( a ) dlopen( a , RTLD_LAZY | RTLD_GLOBAL)
#   define DYNLIB_UNLOAD( a ) !dlclose( a )
#   define DYNLIB_EXTENSION "dylib"
#   define DYNLIB_LASTERROR dlerror
#   include <dlfcn.h>
#
#  else
#
#   define DYNLIB_HANDLE void*
#   define DYNLIB_GETSYM( a, b ) dlsym( a, b )
#   define DYNLIB_LOAD( a ) dlopen( a , RTLD_LAZY | RTLD_GLOBAL)
#   define DYNLIB_UNLOAD( a ) !dlclose( a )
#   define DYNLIB_EXTENSION "so"
#   define DYNLIB_LASTERROR dlerror
#   include <dlfcn.h>
#
#  endif

#endif

namespace atl
{
    class Dynlib : public Performable
    {
        Filename iFilename ;
        DYNLIB_HANDLE iHandle ;

    public:

        Dynlib( const Filename & filename );
        virtual ~Dynlib();

        DYNLIB_HANDLE GetHandle() const ;
        void Start();
        Filename GetFilename() const ;

        bool IsStartable() const ;
    };
}

#endif /* Dynlib_hpp */
