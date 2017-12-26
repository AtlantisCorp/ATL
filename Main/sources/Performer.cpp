//
//  Performer.cpp
//  atlresource
//
//  Created by Jacques Tronconi on 17/09/2017.
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//

#include <ATL/Performer.hpp>

namespace atl
{
    Performer::Performer()
    {
        iStarted.store( false );
        iEnded.store( true );
    }

    Performer::~Performer()
    {

    }

    bool Performer::IsFinished() const
    {
        return !iStarted.load() && iEnded.load();
    }

    bool Performer::IsActive() const
    {
        return iStarted.load() && !iEnded.load();
    }

    bool Performer::IsStarted() const
    {
        return iStarted.load();
    }

    Duration Performer::GetDuration() const
    {
        assert( IsFinished() && "Performer has not finished its task yet. Please use 'wait' before." );

        Spinlocker lck( iSpinlock );
        return iEnd - iStart ;
    }

    void Performer::Wait()
    {
        while ( !IsFinished() ) { }
    }

    Seconds Performer::GetSeconds() const
    {
        return ToSeconds( GetDuration() );
    }

    double Performer::GetMillis() const
    {
        return ToSeconds( GetDuration() ).count() * 1000.0 ;
    }

    double Performer::GetMicros() const
    {
        return ToSeconds( GetDuration() ).count() * 1000000.0 ;
    }

    double Performer::GetNanos() const
    {
        return ToSeconds( GetDuration() ).count() * 1000000000.0 ;
    }
    
    ////////////////////////////////////////////////////////////
    void Performer::StartSynced()
    {
        assert( !iStarted.load() && "Performer already started." );
        assert( iEnded.load() && "Performer not ended yet." );
        Spinlocker lck( iSpinlock );
        
        iStart = Clock::now();
        iStarted.store( true );
        iEnded.store( false );
    }
    
    ////////////////////////////////////////////////////////////
    void Performer::EndSynced()
    {
        Spinlocker lck( iSpinlock );
        iEnd = Clock::now();
        iStarted.store( false );
        iEnded.store( true );
    }
}
