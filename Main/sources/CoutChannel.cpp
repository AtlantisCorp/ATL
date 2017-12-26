//
//  CoutChannel.cpp
//  atlresource
//
//  Created by Jacques Tronconi on 17/09/2017.
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//

#include <ATL/CoutChannel.hpp>

namespace atl
{
    CoutChannel::CoutChannel()
    {
        
    }
    
    CoutChannel::~CoutChannel()
    {
        
    }
    
    void CoutChannel::Write(const char *str)
    {
        std::cout << str ;
    }
    
    void CoutChannel::Endl()
    {
        std::cout << std::endl ;
    }
    
    void CoutChannel::PrepareWriting()
    {
        
    }
    
    void CoutChannel::EndWriting()
    {
        
    }
    
    ThreadedCoutChannel::ThreadedCoutChannel()
    {
        
    }
    
    ThreadedCoutChannel::~ThreadedCoutChannel()
    {
        
    }
    
    void ThreadedCoutChannel::PrepareWriting()
    {
        iSpinlock.lock();
    }
    
    void ThreadedCoutChannel::EndWriting()
    {
        iSpinlock.unlock();
    }
}
