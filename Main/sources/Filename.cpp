//
//  Filename.cpp
//  atlresource
//
//  Created by Jacques Tronconi on 21/09/2017.
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//

#include <ATL/Filename.hpp>

namespace atl
{
    Filename::Filename( const String& filepath ) : iFilepath( filepath )
    {
        
    }
    
    Filename::Filename( const Filename& rhs ) : iFilepath( rhs.iFilepath )
    {
        
    }
    
    Filename::~Filename()
    {
        
    }
    
    bool Filename::operator==(const atl::Filename &filename) const
    {
        return iFilepath == filename.iFilepath ;
    }
    
    bool Filename::operator!=(const atl::Filename &filename) const
    {
        return iFilepath != filename.iFilepath ;
    }
    
    String Filename::GetExtension() const
    {
        return iFilepath.substr( iFilepath.find_last_of(".") + 1 );
    }
    
    bool Filename::CheckHeader( const String& header ) const 
    {
        std::ifstream file( iFilepath , std::ios::in );
        assert( file && "Invalid filepath." );
        
        char buf [header.size()+1];
        memset( buf , 0 , header.size() + 1 );
        
        file.read( buf , header.size() );
        
        return header == String( buf );
    }
    
    String Filename::GetPath() const
    {
        return iFilepath ;
    }
    
    void Filename::SetPath( const String& path )
    {
        iFilepath = path ;
    }
}
