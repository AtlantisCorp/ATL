//
//  Logger.hpp
//  atlresource
//
//  Created by Jacques Tronconi on 17/09/2017.
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//

#ifndef Logger_hpp
#define Logger_hpp

#include <ATL/StdIncludes.hpp>

namespace atl
{
    ////////////////////////////////////////////////////////////
    /// \brief Describes a loggable object.
    ///
    /// It can virtually represent any object where a logger can
    /// write what is passed to it.
    ///
    ////////////////////////////////////////////////////////////
    class Channel
    {
    public:
        
        ////////////////////////////////////////////////////////////
        virtual ~Channel() { }
        
        ////////////////////////////////////////////////////////////
        /// \brief Writes the given string to the channel.
        ///
        ////////////////////////////////////////////////////////////
        virtual void Write( const char* str ) = 0 ;
        
        ////////////////////////////////////////////////////////////
        /// \brief Puts the end-line character and flushes the channel
        /// if needed.
        ///
        ////////////////////////////////////////////////////////////
        virtual void Endl() = 0 ;
        
        ////////////////////////////////////////////////////////////
        /// \brief Prepare the channel for writing operations.
        ///
        /// In a multithreaded context, this can result of locking
        /// a channel mutex to prevent other threads of writing to it.
        ///
        ////////////////////////////////////////////////////////////
        virtual void PrepareWriting() = 0 ;
        
        ////////////////////////////////////////////////////////////
        /// \brief Unlock the channel for further writing operations.
        ///
        ////////////////////////////////////////////////////////////
        virtual void EndWriting() = 0 ;
        
        ////////////////////////////////////////////////////////////
        friend Channel& operator << ( Channel& channel , const char* str )
        {
            channel.Write( str );
            return channel ;
        }
        
        ////////////////////////////////////////////////////////////
        friend Channel& operator << ( Channel& channel , const String& str )
        {
            channel.Write( str.c_str() );
            return channel ;
        }
        
        ////////////////////////////////////////////////////////////
        template < class Convertible >
        friend Channel& operator << ( Channel& channel , const Convertible& rand )
        {
            channel.Write( std::to_string(rand).c_str() );
            return channel ;
        }
    };
    
    ////////////////////////////////////////////////////////////
    class Logger
    {
        Shared < Channel > iChannel ;
        
    public:
        
        Logger( const Shared < Channel > & channel )
        {
            iChannel = channel ;
        }
        
        template < class... Class >
        Logger& info( Class&&... args )
        {
            return log( "[INFO] " , std::forward < Class >( args )... );
        }
        
        template < class... Class >
        Logger& warn( Class&&... args )
        {
            return log( "[WARN] " , std::forward < Class >( args )... );
        }
        
        template < class First , class... Class >
        Logger& log( const First& arg , Class&&... args )
        {
            assert( iChannel );
            
            iChannel -> PrepareWriting();
            
            *iChannel << arg ;
            logImpl( std::forward < Class >( args )... );
            iChannel -> Endl();
            
            iChannel -> EndWriting();
            
            return *this ;
        }
        
    private:
        
        template < class First , class... Class >
        void logImpl( const First& arg , Class&&... args )
        {
            *iChannel << arg ;
            logImpl( std::forward < Class >( args )... );
        }
        
        template < class Last >
        void logImpl( const Last& last )
        {
            *iChannel << last ;
        }
        
        void logImpl()
        {
            
        }
    };
}

#endif /* Logger_hpp */
