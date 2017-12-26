//  ========================================================================  //
//
//  File    : OSXWindow/Unicode.mm
//  Project : ATL/OSXWindow
//  Author  : Luk2010
//  Date    : 14/10/2017
//
//  Copyright :
//  Copyright © 2017 Atlanti's Corporation. All rights reserved.
//
//  ========================================================================  //
#include <ATL/Key.hpp>
#include <OSXWindow/Unicode.h>
#include <OSXWindow/Scaling.h>

#import <Foundation/Foundation.h>
#import <Carbon/Carbon.h>

//-------------------------------------------------------------------------
//  translate keyDown to true unichar via inputlayout
//  https://stackoverflow.com/questions/40088837/cocoa-objective-c-on-macos-handle-accented-characters-via-keydown
//-------------------------------------------------------------------------
NSString * translateInputForKeyDown(NSEvent *event, UInt32 *deadKeyState)
{
    // http://stackoverflow.com/questions/12547007/convert-key-code-into-key-equivalent-string
    // http://stackoverflow.com/questions/8263618/convert-virtual-key-code-to-unicode-string
    
    const size_t unicodeStringLength = 4;
    UniChar unicodeString[unicodeStringLength]= { 0, };
    UniCharCount reallength= 0;
    NSString *nsstring= nil;
    
    TISInputSourceRef fkis= TISCopyCurrentKeyboardInputSource();
    if (fkis) {
        CFDataRef cflayoutdata= (CFDataRef)TISGetInputSourceProperty(fkis, kTISPropertyUnicodeKeyLayoutData);
        const UCKeyboardLayout *keyboardlayout= (const UCKeyboardLayout *)CFDataGetBytePtr(cflayoutdata);
        CGEventFlags flags = [event modifierFlags];
        UInt32 keymodifiers = (flags >> 16) & 0xFF;
        
        UCKeyTranslate(keyboardlayout,
                       [event keyCode], kUCKeyActionDown, keymodifiers,
                       LMGetKbdType(), 0,
                       deadKeyState,
                       unicodeStringLength, &reallength, unicodeString);
        ::CFRelease(fkis);
    }
    
    if (reallength>0) {
        nsstring= (NSString *)CFStringCreateWithCharacters(kCFAllocatorDefault, unicodeString, reallength);
    }
    
    return nsstring;
}

////////////////////////////////////////////////////////////
atl::String AtlDetectKeyFromNSString( NSString* str )
{
    if ( [str length] == 1 )
    {
        unichar keyChar = [str characterAtIndex:0];
    
        switch (keyChar)
        {
            case NSUpArrowFunctionKey:      return atl::Key::UpArrow ;
            case NSDownArrowFunctionKey:    return atl::Key::DownArrow ;
            case NSLeftArrowFunctionKey:    return atl::Key::LeftArrow ;
            case NSRightArrowFunctionKey:   return atl::Key::RightArrow ;
            
            case NSF1FunctionKey:           return atl::Key::F1 ;
            case NSF2FunctionKey:           return atl::Key::F2 ;
            case NSF3FunctionKey:           return atl::Key::F3 ;
            case NSF4FunctionKey:           return atl::Key::F4 ;
            case NSF5FunctionKey:           return atl::Key::F5 ;
            case NSF6FunctionKey:           return atl::Key::F6 ;
            case NSF7FunctionKey:           return atl::Key::F7 ;
            case NSF8FunctionKey:           return atl::Key::F8 ;
            case NSF9FunctionKey:           return atl::Key::F9 ;
            
            case NSF10FunctionKey:          return atl::Key::F10 ;
            case NSF11FunctionKey:          return atl::Key::F11 ;
            case NSF12FunctionKey:          return atl::Key::F12 ;
            case NSF13FunctionKey:          return atl::Key::F13 ;
            case NSF14FunctionKey:          return atl::Key::F14 ;
            case NSF15FunctionKey:          return atl::Key::F15 ;
            case NSF16FunctionKey:          return atl::Key::F16 ;
            case NSF17FunctionKey:          return atl::Key::F17 ;
            case NSF18FunctionKey:          return atl::Key::F18 ;
            case NSF19FunctionKey:          return atl::Key::F19 ;
            
            case NSF20FunctionKey:          return atl::Key::F20 ;
            case NSF21FunctionKey:          return atl::Key::F21 ;
            case NSF22FunctionKey:          return atl::Key::F22 ;
            case NSF23FunctionKey:          return atl::Key::F23 ;
            case NSF24FunctionKey:          return atl::Key::F24 ;
            case NSF25FunctionKey:          return atl::Key::F25 ;
            case NSF26FunctionKey:          return atl::Key::F26 ;
            case NSF27FunctionKey:          return atl::Key::F27 ;
            case NSF28FunctionKey:          return atl::Key::F28 ;
            case NSF29FunctionKey:          return atl::Key::F29 ;
            
            case NSF30FunctionKey:          return atl::Key::F30 ;
            case NSF31FunctionKey:          return atl::Key::F31 ;
            case NSF32FunctionKey:          return atl::Key::F32 ;
            case NSF33FunctionKey:          return atl::Key::F33 ;
            case NSF34FunctionKey:          return atl::Key::F34 ;
            case NSF35FunctionKey:          return atl::Key::F35 ;
                
            case NSInsertFunctionKey:       return atl::Key::Insert ;
            case NSDeleteFunctionKey:       return atl::Key::ForwardDelete ;
            case NSHomeFunctionKey:         return atl::Key::Home ;
            case NSBeginFunctionKey:        return atl::Key::Begin ;
            case NSEndFunctionKey:          return atl::Key::End ;
            case NSPageUpFunctionKey:       return atl::Key::PageUp ;
            case NSPageDownFunctionKey:     return atl::Key::PageDown ;
            case NSPrintScreenFunctionKey:  return atl::Key::PrintScreen ;
            case NSScrollLockFunctionKey:   return atl::Key::ScrollLock ;
            case NSPauseFunctionKey:        return atl::Key::Pause ;
            case NSBreakFunctionKey:        return atl::Key::Break ;
            case NSResetFunctionKey:        return atl::Key::Reset ;
            case NSStopFunctionKey:         return atl::Key::Stop ;
            case NSMenuFunctionKey:         return atl::Key::Menu ;
            case NSUserFunctionKey:         return atl::Key::User ;
            case NSSystemFunctionKey:       return atl::Key::System ;
            case NSPrintFunctionKey:        return atl::Key::Print ;
            case NSPrevFunctionKey:         return atl::Key::Previous ;
            case NSNextFunctionKey:         return atl::Key::Next ;
            case NSSelectFunctionKey:       return atl::Key::Select ;
            case NSExecuteFunctionKey:      return atl::Key::Execute ;
            case NSUndoFunctionKey:         return atl::Key::Undo ;
            case NSRedoFunctionKey:         return atl::Key::Redo ;
            case NSFindFunctionKey:         return atl::Key::Find ;
            case NSHelpFunctionKey:         return atl::Key::Help ;
            case NSModeSwitchFunctionKey:   return atl::Key::ModeSwitch ;
                
            case NSSysReqFunctionKey:
            case NSClearLineFunctionKey:
            case NSClearDisplayFunctionKey:
            case NSInsertLineFunctionKey:
            case NSDeleteLineFunctionKey:
            case NSInsertCharFunctionKey:
            case NSDeleteCharFunctionKey:
                return atl::Key::Unsupported ;
        }
    }
    
    return AtlStringFromNSString( str );
}
