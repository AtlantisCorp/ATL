//  ========================================================================  //
//
//  File    : ATL/MimeType.hpp
//  Project : atlresource
//  Author  : Luk2010
//  Date    : 16/09/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#ifndef MimeType_hpp
#define MimeType_hpp

#include <ATL/StdIncludes.hpp>
#include <ATL/Filename.hpp>

namespace atl
{
    ////////////////////////////////////////////////////////////
    /// \brief Basic implementation of what can be a MIME type.
    ///
    /// A MIME type is an interpretation of what represent a file,
    /// using some parameters to determine for what purpose is this
    /// file.
    ///
    /// For every loadable file, a MIME type must be available to select
    /// the corresponding Metaclass object to create the appropriate
    /// object.
    ///
    /// A MIME type follows the pattern:
    /// [ Category ] / [ Level1 . Level2 . (...) ] + Suffix
    ///
    /// Extensions can be added to add more customization to the MIME
    /// type. Generally a Plugin will add its custom MIME type by using
    /// the simple pattern (for plugin Gl3Driver to add the Vertex Shader
    /// Metaclass): 'Gl3Driver/Shader.Vertex'. The producted resource
    /// will thus have this MIME type that can be checked by any other
    /// API to know if the resource is, for example, compatible with their
    /// underlying behaviour.
    ///
    ////////////////////////////////////////////////////////////
    class MimeType
    {
        ////////////////////////////////////////////////////////////
        String      iTopLevelCat ;  ///< Category.
        String      iSublevelTree ; ///< Sub levels tree (after the Category and the '/').
        String      iSuffix ;       ///< Suffix (after the '+').
        StringList  iExtensions ;   ///< Extensions (for now manually given).
        StringMap   iOptionals ;    ///< Options to the MIME type (manually given).
        String      iHeader ;       ///< Header normally encountered at the beginning of the file.
        uint32_t    iPriority ;     ///< Priority of this MIME type over others.
        
    public:
        
        MimeType();
        MimeType( const String& complete );
        MimeType( const String& complete , const StringList& exts );
        MimeType( const MimeType& parent , const String& subtype , const StringMap& options );
        MimeType( const MimeType& rhs );
        virtual ~MimeType();
        
        MimeType& operator = ( const MimeType& rhs );
        bool operator == ( const MimeType& rhs ) const ;
        bool operator != ( const MimeType& rhs ) const ;
        bool operator <  ( const MimeType& rhs ) const ;
        
        bool IsEmpty() const ;
        bool IsParent( const MimeType& parent ) const ;
        bool IsSubtype( const MimeType& sub ) const ;
        
        String GetTopLevel() const ;
        String GetSubLevel() const ;
        String GetTreeName() const ;
        String GetSuffix() const ;
        String GetSubType() const ;
        String GetCompleteTree() const ;
        StringList GetExtensions() const ;
        
        String GetHeader() const ;
        void SetHeader( const String& header );
        
        uint32_t GetPriority() const ;
        void SetPriority( const uint32_t& p );
        
        void Parse( const String & mime );
        
        void SetExtensions( const StringList& exts );
    };
}

#endif /* MimeType_hpp */
