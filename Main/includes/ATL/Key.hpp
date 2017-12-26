//  ========================================================================  //
//
//  File    : ATL/Key.hpp
//  Project : atlresource
//  Author  : Luk2010
//  Date    : 13/10/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#ifndef Key_hpp
#define Key_hpp

#include <ATL/StdIncludes.hpp>

namespace atl
{
    ////////////////////////////////////////////////////////////
    /// \brief Defines some Keys constants values.
    ///
    /// As those key constants are String, you can compare them
    /// directly with the return value of 'SurfaceKeyDownEvent::GetKey()'
    /// to know if your pressed key is one of the special keys below.
    /// You can also use 'Key::IsSpecialKey()'. Also are in this table
    /// Control keys. You can use 'Key::IsControlKey()' to assert a key is
    /// of Control keys. Their value is based on the ASCII values.
    ///
    /// Those values are arbitrary but are copied from NSEvent macOS
    /// file.
    ///
    ////////////////////////////////////////////////////////////
    namespace Key
    {
        ////////////////////////////////////////////////////////////
        // Special keys.
        //
        ////////////////////////////////////////////////////////////
        
        static String UpArrow       = "\xF7\x01" ;
        static String DownArrow     = "\xF7\x02" ;
        static String LeftArrow     = "\xF7\x03" ;
        static String RightArrow    = "\xF7\x04" ;
        static String F1            = "\xF7\x05" ;
        static String F2            = "\xF7\x06" ;
        static String F3            = "\xF7\x07" ;
        static String F4            = "\xF7\x08" ;
        static String F5            = "\xF7\x09" ;
        static String F6            = "\xF7\x0A" ;
        static String F7            = "\xF7\x0B" ;
        static String F8            = "\xF7\x0C" ;
        static String F9            = "\xF7\x0D" ;
        static String F10           = "\xF7\x0E" ;
        static String F11           = "\xF7\x0F" ;
        static String F12           = "\xF7\x10" ;
        static String F13           = "\xF7\x11" ;
        static String F14           = "\xF7\x12" ;
        static String F15           = "\xF7\x13" ;
        static String F16           = "\xF7\x14" ;
        static String F17           = "\xF7\x15" ;
        static String F18           = "\xF7\x16" ;
        static String F19           = "\xF7\x17" ;
        static String F20           = "\xF7\x18" ;
        static String F21           = "\xF7\x19" ;
        static String F22           = "\xF7\x1A" ;
        static String F23           = "\xF7\x1B" ;
        static String F24           = "\xF7\x1C" ;
        static String F25           = "\xF7\x1D" ;
        static String F26           = "\xF7\x1E" ;
        static String F27           = "\xF7\x1F" ;
        static String F28           = "\xF7\x20" ;
        static String F29           = "\xF7\x21" ;
        static String F30           = "\xF7\x22" ;
        static String F31           = "\xF7\x23" ;
        static String F32           = "\xF7\x24" ;
        static String F33           = "\xF7\x25" ;
        static String F34           = "\xF7\x26" ;
        static String F35           = "\xF7\x27" ;
        static String Insert        = "\xF7\x28" ;
        static String ForwardDelete = "\xF7\x29" ;
        static String Home          = "\xF7\x2A" ;
        static String Begin         = "\xF7\x2B" ;
        static String End           = "\xF7\x2C" ;
        static String PageUp        = "\xF7\x2D" ;
        static String PageDown      = "\xF7\x2E" ;
        static String PrintScreen   = "\xF7\x2F" ;
        static String ScrollLock    = "\xF7\x30" ;
        static String Pause         = "\xF7\x31" ;
        static String Break         = "\xF7\x32" ;
        static String Reset         = "\xF7\x33" ;
        static String Stop          = "\xF7\x34" ;
        static String Menu          = "\xF7\x35" ;
        static String User          = "\xF7\x36" ;
        static String System        = "\xF7\x37" ;
        static String Print         = "\xF7\x38" ;
        static String Previous      = "\xF7\x39" ;
        static String Next          = "\xF7\x3A" ;
        static String Select        = "\xF7\x3B" ;
        static String Execute       = "\xF7\x3C" ;
        static String Undo          = "\xF7\x3D" ;
        static String Redo          = "\xF7\x3E" ;
        static String Find          = "\xF7\x3F" ;
        static String Help          = "\xF7\x40" ;
        static String ModeSwitch    = "\xF7\x41" ;
        
        static String Unsupported   = "\xF7\x42" ;
        
        ////////////////////////////////////////////////////////////
        /// \brief Determines if the given String is a special character.
        ///
        ////////////////////////////////////////////////////////////
        bool IsSpecialKey( const String& key );
        
        ////////////////////////////////////////////////////////////
        // Control keys base on ASCII escape sequences.
        //
        ////////////////////////////////////////////////////////////
        
        static String Null          = "\x00" ;
        static String HeadStart     = "\x01" ;
        static String TextStart     = "\x02" ;
        static String TextEnd       = "\x03" ;
        static String TransmEnd     = "\x04" ;
        static String Enquiry       = "\x05" ;
        static String Acknowledge   = "\x06" ;
        static String Bell          = "\x07" ;
        static String Backspace     = "\x08" ;
        static String HorzTab       = "\x09" ;
        static String LineFeed      = "\x0A" ;
        static String VertTab       = "\x0B" ;
        static String FormFeed      = "\x0C" ;
        static String Return        = "\x0D" ;
        static String ShiftOut      = "\x0E" ;
        static String ShiftIn       = "\x0F" ;
        static String Cancel        = "\x18" ;
        static String Escape        = "\x1B" ;
        static String Delete        = "\x7F" ;
        
        // [...] Some of ASCII controls are not written here because never used.
        // Anyway, you can test them for their values using "\xXX" notation.
        
        ////////////////////////////////////////////////////////////
        /// \brief Returns true if the given key is a control key.
        ///
        ////////////////////////////////////////////////////////////
        bool IsControlKey( const String& key );
    }
}

#endif /* Key_hpp */
