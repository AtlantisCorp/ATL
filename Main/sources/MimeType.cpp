//  ========================================================================  //
//
//  File    : ATL/MimeType.cpp
//  Project : atlresource
//  Author  : Luk2010
//  Date    : 16/09/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#include <ATL/MimeType.hpp>

namespace atl
{
    ////////////////////////////////////////////////////////////
    MimeType::MimeType()
    {
        iPriority = 1 ;
    }
    
    ////////////////////////////////////////////////////////////
    MimeType::MimeType( const String& complete )
    {
        Parse( complete );
        iPriority = 1 ;
    }
    
    ////////////////////////////////////////////////////////////
    MimeType::MimeType( const String& complete , const StringList& exts )
    {
        Parse( complete );
        iExtensions = exts ;
        iPriority = 1 ;
    }
    
    ////////////////////////////////////////////////////////////
    MimeType::MimeType( const MimeType& parent , const String& subtype , const StringMap& options )
    {
        iTopLevelCat    = parent.GetTopLevel();
        iSublevelTree   = subtype.empty() ? parent.GetCompleteTree() : parent.GetCompleteTree() + "." + subtype ;
        iSuffix         = parent.GetSuffix();
        iExtensions     = parent.GetExtensions();
        iOptionals      = options ;
        iHeader         = parent.iHeader ;
        iPriority       = parent.iPriority + 1 ;
    }
    
    ////////////////////////////////////////////////////////////
    MimeType::MimeType( const MimeType& rhs )
    {
        iTopLevelCat    = rhs.iTopLevelCat ;
        iSublevelTree   = rhs.iSublevelTree ;
        iSuffix         = rhs.iSuffix ;
        iExtensions     = rhs.iExtensions ;
        iOptionals      = rhs.iOptionals ;
        iHeader         = rhs.iHeader ;
        iPriority       = rhs.iPriority ;
    }
    
    ////////////////////////////////////////////////////////////
    MimeType::~MimeType()
    {
        
    }
    
    ////////////////////////////////////////////////////////////
    MimeType& MimeType::operator=(const atl::MimeType &rhs)
    {
        iTopLevelCat    = rhs.iTopLevelCat ;
        iSublevelTree   = rhs.iSublevelTree ;
        iSuffix         = rhs.iSuffix ;
        iExtensions     = rhs.iExtensions ;
        iOptionals      = rhs.iOptionals ;
        iHeader         = rhs.iHeader ;
        iPriority       = rhs.iPriority ;
        return *this ;
    }
    
    ////////////////////////////////////////////////////////////
    bool MimeType::operator==(const atl::MimeType &rhs) const
    {
        return iTopLevelCat == rhs.iTopLevelCat
            && iSublevelTree == rhs.iSublevelTree
            && iSuffix == rhs.iSuffix
            && iOptionals == rhs.iOptionals ;
    }
    
    ////////////////////////////////////////////////////////////
    bool MimeType::operator!=(const atl::MimeType &rhs) const
    {
        return !(*this == rhs);
    }
    
    ////////////////////////////////////////////////////////////
    bool MimeType::operator < ( const MimeType& rhs ) const
    {
        return GetCompleteTree() < rhs.GetCompleteTree();
    }
    
    ////////////////////////////////////////////////////////////
    bool MimeType::IsEmpty() const
    {
        return iTopLevelCat.empty() || iSublevelTree.empty();
    }
    
    ////////////////////////////////////////////////////////////
    bool MimeType::IsParent(const atl::MimeType &parent) const
    {
        return GetCompleteTree().find_first_of( parent.GetCompleteTree() ) == 0 ;
    }
    
    ////////////////////////////////////////////////////////////
    bool MimeType::IsSubtype(const atl::MimeType &sub) const
    {
        return sub.IsParent( *this );
    }
    
    ////////////////////////////////////////////////////////////
    String MimeType::GetTopLevel() const
    {
        return iTopLevelCat ;
    }
    
    ////////////////////////////////////////////////////////////
    String MimeType::GetSubType() const
    {
        return iSublevelTree ;
    }
    
    ////////////////////////////////////////////////////////////
    String MimeType::GetTreeName() const
    {
        size_t i = iSublevelTree.find_first_of(".");
        
        if ( i != std::string::npos )
        return iSublevelTree.substr( 0 , i );
        
        return String();
    }
    
    ////////////////////////////////////////////////////////////
    String MimeType::GetSuffix() const
    {
        return iSuffix ;
    }
    
    ////////////////////////////////////////////////////////////
    String MimeType::GetCompleteTree() const
    {
        return iTopLevelCat + "/" + iSublevelTree ;
    }
    
    ////////////////////////////////////////////////////////////
    StringList MimeType::GetExtensions() const
    {
        return iExtensions ;
    }
    
    ////////////////////////////////////////////////////////////
    String MimeType::GetHeader() const 
    {
        return iHeader ;
    }
    
    ////////////////////////////////////////////////////////////
    void MimeType::SetHeader( const String& header )
    {
        iHeader = header ;
    }
    
    ////////////////////////////////////////////////////////////
    uint32_t MimeType::GetPriority() const 
    {
        return iPriority ;
    }
    
    ////////////////////////////////////////////////////////////
    void MimeType::SetPriority( const uint32_t& p )
    {
        iPriority = p ;
    }
    
    ////////////////////////////////////////////////////////////
    void MimeType::Parse(const String &mime)
    {
        auto endcat = mime.find_first_of( "/" );
        auto endsubtype = mime.find_first_of( "+" );
        if ( endsubtype == std::string::npos ) endsubtype = mime.size();
        assert( endsubtype > endcat && "Invalid sub-type ending." );
        
        iTopLevelCat = mime.substr( 0 , endcat );
        iSublevelTree = mime.substr( endcat + 1 , endsubtype );
        
        if ( endsubtype < mime.size() )
        iSuffix = mime.substr( endsubtype + 1 );
    }
    
    ////////////////////////////////////////////////////////////
    void MimeType::SetExtensions(const StringList &exts)
    {
        iExtensions = exts ;
    }
}
