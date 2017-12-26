//
//  CoutChannel.hpp
//  atlresource
//
//  Created by Jacques Tronconi on 17/09/2017.
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//

#ifndef CoutChannel_hpp
#define CoutChannel_hpp

#include <ATL/Logger.hpp>

namespace atl
{
    class CoutChannel : public Channel
    {
    public:
        
        CoutChannel();
        virtual ~CoutChannel();
        
        virtual void Write( const char* str );
        virtual void Endl();
        
        virtual void PrepareWriting();
        virtual void EndWriting();
    };
    
    class ThreadedCoutChannel : public CoutChannel
    {
        Spinlock iSpinlock ;
        
    public:
        
        ThreadedCoutChannel();
        virtual ~ThreadedCoutChannel();
        
        virtual void PrepareWriting();
        virtual void EndWriting();
    };
}

#endif /* CoutChannel_hpp */
