//
//  Pipeline.hpp
//  atlresource
//
//  Created by Jacques Tronconi on 25/09/2017.
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//

#ifndef Pipeline_hpp
#define Pipeline_hpp

#include <ATL/StdIncludes.hpp>

namespace atl
{

    class Pipeline : public std::enable_shared_from_this < Pipeline >
    {

    public:

        Pipeline();
        virtual ~Pipeline();
    };
}

#endif // Pipeline_hpp
