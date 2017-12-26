//  ========================================================================  //
//
//  File    : ATL/MimeDatabase.cpp
//  Project : atlresource
//  Author  : Luk2010
//  Date    : 14/11/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#include <ATL/MimeDatabase.hpp>

namespace atl
{
    ////////////////////////////////////////////////////////////
    MimeDatabase::MimeDatabase()
    {
        
    }
    
    ////////////////////////////////////////////////////////////
    MimeDatabase::~MimeDatabase()
    {
        
    }
    
    ////////////////////////////////////////////////////////////
    void MimeDatabase::AddType(const atl::MimeType &type)
    {
        Spinlocker lck( iSpinlock );
        iMimes.push_back( type );
    }
    
    ////////////////////////////////////////////////////////////
    void MimeDatabase::AddTypes(const Vector<atl::MimeType> &type)
    {
        Spinlocker lck( iSpinlock );
        
        for ( auto mime : type )
        {
            iMimes.push_back( mime );
        }
    }
    
    ////////////////////////////////////////////////////////////
    Vector < MimeType > MimeDatabase::FindAllForFile( const Filename& filename ) const
    {
        auto result = FindCompleteMatchForFile( filename );
        
        auto byhead = FindHeaderMatchForFile( filename );
        result.insert( result.end() , byhead.begin() , byhead.end() );
        
        auto byexts = FindExtensionMatchForFile( filename );
        result.insert( result.end() , byexts.begin() , byexts.end() );
        
        return result ;
    }
    
    ////////////////////////////////////////////////////////////
    MimeType MimeDatabase::FindHigherForFile( const Filename& filename ) const
    {
        auto byall = FindAllForFile( filename );
        return byall.size() > 0 ? byall.at(0) : MimeType() ;
    }
    
    ////////////////////////////////////////////////////////////
    Vector < MimeType > MimeDatabase::FindCompleteMatchForFile( const Filename& filename ) const
    {
        std::ifstream ifs( filename.GetPath() , std::ifstream::binary );
        if ( !ifs ) return Vector < MimeType >();
        auto extension = filename.GetExtension();
        
        Vector < MimeType > result ;
        {
            Spinlocker lck( iSpinlock );
            
            for ( auto const& mime : iMimes )
            {
                const String& header = mime.GetHeader();
                if ( header.empty() )
                    continue ;
                
                char headbuf [ header.size() ];
                memset( headbuf , 0 , header.size() );
                ifs.get( headbuf , header.size() );
                ifs.seekg( 0 , ifs.beg );
                
                if ( header != headbuf )
                    continue ;
                
                auto const& exts = mime.GetExtensions();
                auto it = std::find( exts.begin() , exts.end() , extension );
                
                if ( it == exts.end() )
                    continue ;
                
                result.push_back( mime );
            }
        }
        
        ifs.close();
        
        Sort( result );
        return result ;
    }
    
    ////////////////////////////////////////////////////////////
    Vector < MimeType > MimeDatabase::FindHeaderMatchForFile( const Filename& filename ) const
    {
        std::ifstream ifs( filename.GetPath() , std::ifstream::binary );
        if ( !ifs ) return Vector < MimeType >();
        
        Vector < MimeType > result ;
        {
            Spinlocker lck( iSpinlock );
            
            for ( auto const& mime : iMimes )
            {
                const String& header = mime.GetHeader();
                if ( header.empty() )
                    continue ;
                
                char headbuf [ header.size()+1 ];
                memset( headbuf , 0 , header.size()+1 );
                ifs.get( headbuf , header.size() );
                ifs.seekg( 0 , ifs.beg );
                
                if ( header != headbuf )
                    continue ;
                
                result.push_back( mime );
            }
        }
        
        ifs.close();
        
        Sort( result );
        return result ;
    }
    
    ////////////////////////////////////////////////////////////
    Vector < MimeType > MimeDatabase::FindExtensionMatchForFile( const Filename& filename ) const
    {
        auto extension = filename.GetExtension();
        Vector < MimeType > result ;
        {
            Spinlocker lck( iSpinlock );
            
            for ( auto const& mime : iMimes )
            {
                auto const& exts = mime.GetExtensions();
                auto it = std::find( exts.begin() , exts.end() , extension );
                
                if ( it == exts.end() )
                    continue ;
                
                result.push_back( mime );
            }
        }
        
        Sort( result );
        return result ;
    }
    
    ////////////////////////////////////////////////////////////
    const MimeType MimeDatabase::Find(const String &complete) const
    {
        Spinlocker lck( iSpinlock );
        
        for ( auto mime : iMimes )
        {
            if ( mime.GetCompleteTree() == complete )
                return mime ;
        }
        
        return MimeType();
    }
    
    ////////////////////////////////////////////////////////////
    const MimeType MimeDatabase::FindFirstChild(const atl::MimeType &parent) const
    {
        Spinlocker lck( iSpinlock );
        
        for ( auto mime : iMimes )
        {
            if ( mime.IsParent( parent ) )
                return mime ;
        }
        
        return MimeType();
    }
    
    ////////////////////////////////////////////////////////////
    void MimeDatabase::RemoveType(const atl::MimeType &type)
    {
        Spinlocker lck( iSpinlock );
        
        auto it = std::find( iMimes.begin() , iMimes.end() , type );
        
        if ( it != iMimes.end() )
            iMimes.erase( it );
    }
    
    ////////////////////////////////////////////////////////////
    void MimeDatabase::RemoveTypes(const Vector<atl::MimeType> &types)
    {
        for ( auto mime : types )
            RemoveType( mime );
    }
    
    ////////////////////////////////////////////////////////////
    void MimeDatabase::Reset()
    {
        Spinlocker lck( iSpinlock );
        iMimes.clear();
    }
    
    ////////////////////////////////////////////////////////////
    uint32_t MimeDatabase::LoadSimpleMimeDatabase(const atl::Filename &filename)
    {
        uint32_t retvalue = 0 ;
        
        std::ifstream file( filename.GetPath() , std::ios::in );
        assert( file && ( String( "Invalid filename given: " ) + filename.GetPath() ).size() );
        
        MimeType currmime ;
        String currword ;
        
        while( file >> currword )
        {
            if ( currword == "mime" )
            {
                file >> currword ;
                assert( currword == "=" );
                file >> currword ;
                
                if ( !currmime.IsEmpty() )
                {
                    AddType( currmime );
                    retvalue ++ ;
                }
                
                currmime = MimeType();
                currmime.Parse( currword );
                
                file >> currword ;
                assert( currword == ";" );
            }
            
            else if ( currword == "mime-exts" )
            {
                file >> currword ;
                assert( currword == "=" );
                
                StringList exts ;
                file >> currword ;
                
                while ( currword != ";" )
                {
                    exts.push_back( currword );
                    file >> currword ;
                }
                
                currmime.SetExtensions( exts );
            }
            
            else if ( currword == "mime-priority" )
            {
                file >> currword ;
                assert( currword == "=" );
                file >> currword ;
                
                auto p = strtoul(currword.data(), NULL, 10);
                currmime.SetPriority( (uint32_t) p );
                
                file >> currword ;
                assert( currword == ";" );
            }
            
            else if ( currword == "mime-header" )
            {
                file >> currword ;
                assert( currword == "=" );
                
                file >> currword ;
                currmime.SetHeader( currword );
                
                file >> currword ;
                assert( currword == ";" );
            }
        }
        
        if ( !currmime.IsEmpty() )
        {
            AddType( currmime );
            retvalue ++ ;
        }
        
        return retvalue ;
    }
}
