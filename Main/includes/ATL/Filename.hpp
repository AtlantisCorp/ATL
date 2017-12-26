//
//  Filename.hpp
//  atlresource
//
//  Created by Jacques Tronconi on 21/09/2017.
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//

#ifndef Filename_hpp
#define Filename_hpp

#include <ATL/StdIncludes.hpp>

namespace atl
{
    class Filename
    {
        String iFilepath ;
        
    public:
        
        Filename( const String& path );
        Filename( const Filename & rhs );
        virtual ~Filename();
        
        bool operator == ( const Filename& filename ) const ;
        bool operator != ( const Filename& filename ) const ;
        
        String GetExtension() const ;
        bool CheckHeader( const String& header ) const ;
        
        String GetPath() const ;
        
        ////////////////////////////////////////////////////////////
        /// \brief Changes the Filename's path.
        ///
        ////////////////////////////////////////////////////////////
        void SetPath( const String& path );
    };
}

#endif /* Filename_hpp */
