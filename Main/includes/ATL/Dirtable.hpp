//  ========================================================================  //
//
//  File    : ATL/Dirtable.hpp
//  Project : atlresource
//  Author  : Luk2010
//  Date    : 05/12/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#ifndef Dirtable_hpp
#define Dirtable_hpp

#include <ATL/StdIncludes.hpp>

namespace atl
{
    namespace Detail
    {
        ////////////////////////////////////////////////////////////
        /// \brief Makes an object that derives from this class, able
        /// to handle a 'dirty' flag.
        ///
        ////////////////////////////////////////////////////////////
        class Dirtable
        {
            ////////////////////////////////////////////////////////////
            mutable Atomic < bool > m_dirty ;
            
        public:
            
            ////////////////////////////////////////////////////////////
            Dirtable();
            
            ////////////////////////////////////////////////////////////
            virtual ~Dirtable();
            
            ////////////////////////////////////////////////////////////
            virtual bool IsDirty() const ;
            
        protected:
            
            ////////////////////////////////////////////////////////////
            virtual void SetDirty( bool dirty ) const ;
        };
        
        ////////////////////////////////////////////////////////////
        /// \brief Makes any weak pointer hold a dirty flag when changed.
        ///
        ////////////////////////////////////////////////////////////
        template < typename Class >
        class WeakDirtable : public Dirtable
        {
            ////////////////////////////////////////////////////////////
            Weak < Class > m_holded ;
            
        public:
            
            ////////////////////////////////////////////////////////////
            WeakDirtable( const Weak < Class >& holded ) : m_holded( holded )
            {
                
            }
            
            ////////////////////////////////////////////////////////////
            ~WeakDirtable()
            {
                
            }
            
            ////////////////////////////////////////////////////////////
            void Set( const Weak < Class >& holded )
            {
                if ( holded.lock() != m_holded.lock() )
                {
                    m_holded = holded ;
                    Dirtable::SetDirty( true );
                }
            }
            
            ////////////////////////////////////////////////////////////
            Weak < Class > Get() const
            {
                return m_holded ;
            }
            
            ////////////////////////////////////////////////////////////
            void Clean() const
            {
                Dirtable::SetDirty( false );
            }
        };
    }
}

#endif /* Dirtable_hpp */
