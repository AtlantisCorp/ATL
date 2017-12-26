//
//  StdIncludes.h
//  atlresource
//
//  Created by Jacques Tronconi on 16/09/2017.
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//

#ifndef StdIncludes_h
#define StdIncludes_h

#define ATL_VERSION_MAJOR 0
#define ATL_VERSION_MINOR 1
#define ATL_VERSION_BUILD 1

#include <iostream>
#include <memory>
#include <vector>
#include <cassert>
#include <atomic>
#include <mutex>
#include <list>
#include <chrono>
#include <future>
#include <map>
#include <fstream>
#include <dirent.h>
#include <queue>
#include <sstream>
#include <cstdarg>
#include <type_traits>
#include <exception>

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#define ATL_PLATFORM_UNKNOWN 1
#define ATL_PLATFORM_DARWIN  1 << 1
#define ATL_PLATFORM_WINDOWS 1 << 2
#define ATL_PLATFORM_LINUX   1 << 3

#if defined(__OSX__) || defined(__APPLE__)
#   define ATL_PLATFORM ATL_PLATFORM_DARWIN
#
#elif defined(__WINDOWS__)
#   define ATL_PLATFORM ATL_PLATFORM_WINDOWS
#
#else
#   define ATL_PLATFORM ATL_PLATFORM_LINUX
#
#endif

namespace atl
{
    template < typename Class >
    using remref = typename std::remove_reference < Class >::type ;
    
    template < class Class >
    using Unique = std::unique_ptr < Class > ;
    
#ifndef __cpp_lib_make_unique
    
    template<typename T, typename ...Args>
    std::unique_ptr<T> make_unique( Args&& ...args )
    {
        return std::unique_ptr<T>( new T( std::forward<Args>(args)... ) );
    }
    
#else
    
    template < typename T , typename ... Args >
    std::unique_ptr < T > make_unique( Args&&... args )
    {
        return std::make_unique < T >( std::forward < Args >( args )... );
    }
    
#endif
    
    template < class Class >
    using UniqueVector = std::vector < Unique < Class > > ;
    
    template < class Class >
    using UniqueList = std::list < Unique < Class > > ;
    
    template < class Class >
    using Shared = std::shared_ptr < Class > ;

    template < class Class >
    using SharedVector = std::vector < Shared < Class > > ;

    template < class Class >
    using Weak = std::weak_ptr < Class > ;

    template < class Class >
    using WeakVector = std::vector < Weak < Class > > ;
    
    template < class Class >
    using WeakList = std::list < Weak < Class > > ;

    template < class Class >
    using Atomic = std::atomic < Class > ;

    template < class Class >
    using Lock = std::lock_guard < Class > ;

    template < class Class >
    using Vector = std::vector < Class > ;

    template < class Key , class Value >
    using Map = std::map < Key , Value > ;

    template < class C1 , class C2 >
    using Pair = std::pair < C1 , C2 > ;

    template < class Class >
    using Queue = std::queue < Class > ;
    
    template < class Class >
    using WeakQueue = std::queue < Weak < Class > > ;

    template < class Class >
    using SharedQueue = Queue < Shared < Class > > ;

    typedef std::mutex Mutex ;
    typedef Lock < Mutex > MutexLocker ;

    class Spinlock
    {
        std::atomic_flag flag = ATOMIC_FLAG_INIT ;

    public:

        void lock()     { while ( flag.test_and_set( std::memory_order_acquire ) ); }
        bool try_lock() { return !flag.test_and_set( std::memory_order_acquire ); }
        void unlock()   { flag.clear( std::memory_order_release ); }
    };

    typedef Lock < Spinlock >               Spinlocker ;
    
    ////////////////////////////////////////////////////////////
    /// \brief Return a copy of something by locking and unlocking
    /// this lockable.
    ///
    ////////////////////////////////////////////////////////////
    template < typename Class , typename Lockable >
    Class locked( const Class& obj , Lockable& l ) { Lock < Lockable > lck( l ); return obj ; }

    typedef std::string                     String ;
    typedef std::vector < String >          StringVector ;
    typedef std::list < String >            StringList ;
    typedef std::map < String , String >    StringMap ;

    template < class Class >
    class Singleton
    {
        static Shared < Class > iInstance ;

    public:

        Singleton()
        {

        }

        virtual ~Singleton()
        {

        }

        static Class& Get()
        {
            if ( !iInstance )
            {
                iInstance = std::make_shared < Class > ();
            }
            
            return *iInstance;
        }

        static Shared < Class > GetPtr()
        {
            return iInstance;
        }
        
        static void Destroy()
        {
            if ( iInstance ) iInstance = nullptr ;
        }

    protected:

        Singleton( const Singleton& ) = delete ;
        Singleton( Singleton&& ) = delete ;
    };

    template < class Class >
    Shared < Class > Singleton < Class > ::iInstance = Shared < Class >();

    typedef std::chrono::high_resolution_clock Clock ;
    typedef Clock::duration Duration ;
    typedef Clock::time_point Timepoint ;

    typedef std::chrono::duration < double > Seconds ;

    inline Seconds ToSeconds( const Duration& d )
    {
        return std::chrono::duration_cast < Seconds >( d );
    }

    inline StringList Split( const String& src , const String& delimiters )
    {
        StringList tokens ;
        String cpy = src ;

        char* pch = strtok(&(cpy.at(0)), delimiters.data());

        while ( pch != NULL )
        {
            tokens.push_back( pch );
            pch = strtok( NULL , delimiters.data() );
        }

        return tokens ;
    }

    typedef uint32_t Priority ;

    template < class Container >
    void Sort( Container& c )
    {
        std::sort( c.begin() , c.end() , [](const typename Container::value_type& c1 ,
                                            const typename Container::value_type& c2 )
        {
            return c1.GetPriority() > c2.GetPriority() ;
        });
    }
    
    ////////////////////////////////////////////////////////////
    inline String LoadFileContent( const String& filename )
    {
        std::ifstream ifs( filename , std::ifstream::binary );
        if ( !ifs ) return String();
        
        String result ;
        int length = 0 ;
        
        ifs.seekg( 0 , ifs.end );
        length = ifs.tellg();
        ifs.seekg( 0 , ifs.beg );
        
        if ( length )
        {
            char* buffer = new char [length+1];
            memset( buffer , 0 , length+1 );
            ifs.read( buffer , length );
            
            result = String( buffer , length );
            
            delete[] buffer ;
        }
        
        ifs.close();
        return result ;
    }
}

#include <ATL/Platform.hpp>

#endif /* StdIncludes_h */
