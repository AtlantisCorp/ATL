//  ========================================================================  //
//
//  File    : ATL/MimeDatabase.hpp
//  Project : atlresource
//  Author  : Luk2010
//  Date    : 14/11/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#ifndef MimeDatabase_hpp
#define MimeDatabase_hpp

#include <ATL/Instanced.hpp>
#include <ATL/MimeType.hpp>

namespace atl
{
    ////////////////////////////////////////////////////////////
    /// \brief A Database to collect and organize MIME types.
    ///
    /// The MIME database collect MIME types added by the user or by
    /// plugins and organize them generally by priority.
    ///
    /// Selection of the correct MIME type for a file: A MIME type
    /// is selected for a file following the given steps. Then, the
    /// MIME type with the higher priority is returned.
    ///
    /// - Selection of MIME type with correct headers and extensions.
    /// - Selection of MIME type with correct header only.
    /// - Selection of MIME type with correct extension only.
    ///
    /// Those three lists are sorted by priority. Then, either a list
    /// of MIME type by priority and by compatibility is returned, or
    /// the MIME type with the higher priority score and in the higher
    /// compatibility list is returned (i.e. the first MIME type encountered).
    ///
    /// Adding MIME types manually: This can be done by using 'AddType()' or
    /// by loading an external MIME database file. This file for now must follow
    /// the ATL's MIME database format, which is as follow:
    ///
    /// mime = [ MIME complete name (Category + Levels) ] ;
    /// mime-exts = [ MIME extensions list ] ;
    /// mime-header = [ MIME header string ] ;
    /// mime-priority = [ MIME priority ] ;
    ///
    /// 'mime-header' , 'mime-exts' and 'mime-priority' are optionals
    /// and are always reported to the last 'mime' command.
    ///
    ////////////////////////////////////////////////////////////
    class MimeDatabase : public Instanced < MimeDatabase >
    {
        ////////////////////////////////////////////////////////////
        Vector < MimeType > iMimes ;    ///< MIME types collected.
        mutable Spinlock    iSpinlock ; ///< Access MIME datas.
        
    public:
        
        ////////////////////////////////////////////////////////////
        MimeDatabase();
        
        ////////////////////////////////////////////////////////////
        virtual ~MimeDatabase();
        
        ////////////////////////////////////////////////////////////
        virtual void AddType( const MimeType& type );
        
        ////////////////////////////////////////////////////////////
        virtual void AddTypes( const Vector < MimeType > & type );
        
        ////////////////////////////////////////////////////////////
        /// \brief Return the list of MIME type that could be used to
        /// load the given file, or that may match the given file.
        ///
        ////////////////////////////////////////////////////////////
        virtual Vector < MimeType > FindAllForFile( const Filename& filename ) const ;
        
        ////////////////////////////////////////////////////////////
        /// \brief Return the MIME type with the higher probability to
        /// match the given filename, i.e. the first MIME type in the
        /// returned list of 'FindAllForFile'.
        ///
        ////////////////////////////////////////////////////////////
        virtual MimeType FindHigherForFile( const Filename& filename ) const ;
        
        ////////////////////////////////////////////////////////////
        /// \brief Return a sorted by priority list of MIME types that
        /// match by header and by extension the given file.
        ///
        ////////////////////////////////////////////////////////////
        virtual Vector < MimeType > FindCompleteMatchForFile( const Filename& filename ) const ;
        
        ////////////////////////////////////////////////////////////
        /// \brief Return a sorted by priority list of MIME types that
        /// match only by their header the given file.
        ///
        ////////////////////////////////////////////////////////////
        virtual Vector < MimeType > FindHeaderMatchForFile( const Filename& filename ) const ;
        
        ////////////////////////////////////////////////////////////
        /// \brief Return a sorted by priority list of MIME types that
        /// match only by their extension the given file.
        ///
        ////////////////////////////////////////////////////////////
        virtual Vector < MimeType > FindExtensionMatchForFile( const Filename& filename ) const ;
        
        ////////////////////////////////////////////////////////////
        /// \brief Return the first MIME type corresponding to the given
        /// Category + Levels combination.
        ///
        ////////////////////////////////////////////////////////////
        virtual const MimeType Find( const String& complete ) const ;
        
        ////////////////////////////////////////////////////////////
        /// \brief Return the first MIME type that is a direct child
        /// of the given MIME type.
        ///
        ////////////////////////////////////////////////////////////
        virtual const MimeType FindFirstChild( const MimeType& parent ) const ;
        
        ////////////////////////////////////////////////////////////
        virtual void RemoveType( const MimeType& type );
        
        ////////////////////////////////////////////////////////////
        virtual void RemoveTypes( const Vector < MimeType > & types );
        
        ////////////////////////////////////////////////////////////
        virtual void Reset();
        
        ////////////////////////////////////////////////////////////
        virtual uint32_t LoadSimpleMimeDatabase( const Filename & filename );
    };
}

#endif /* MimeDatabase_hpp */
