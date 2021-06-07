#include "MacOSKeyboardAPI.h"
#include "ShifterInfo.h"

namespace NSApplication {
namespace NSKeyboard {
namespace NSMacOS {

// ########################## createEventTapForKeyboard
CFMachPortRef
CMacOSKeyboardAPI::createEventTapForKeyboard(CGEventTapCallBack         callbackEventTap,
                                             CKeyboardListenerMacImpl*  Listener) {
  return ::CGEventTapCreate(
            ::kCGHIDEventTap,
            ::kCGHeadInsertEventTap,
            ::kCGEventTapOptionListenOnly,
            CGEventMaskBit(::kCGEventKeyDown) |
            CGEventMaskBit(::kCGEventKeyUp)   |
            CGEventMaskBit(::kCGEventFlagsChanged),
            callbackEventTap,
            Listener);
}

// ########################## createRunLoopSourceForEventTap
CFRunLoopSourceRef
CMacOSKeyboardAPI::createRunLoopSourceForEventTap(CFMachPortRef MachPort) {
  return ::CFMachPortCreateRunLoopSource(::kCFAllocatorDefault, MachPort, 0);
}

// ########################## createMessagePort
CFMessagePortRef CMacOSKeyboardAPI::createMessagePort(CFMessagePortCallBack callback) {
  UniquePtr<CFStringRef> Name(
        CFStringCreateWithCString(kCFAllocatorDefault, "KeyboardKillerPort", kCFStringEncodingUTF8));
  return CFMessagePortCreateLocal(kCFAllocatorDefault, Name.get(), callback, NULL, NULL);
}

// ########################## createRunLoopSourceForMessagePort
CFRunLoopSourceRef
CMacOSKeyboardAPI::createRunLoopSourceForMessagePort(CFMessagePortRef MessagePort) {
  return CFMessagePortCreateRunLoopSource(kCFAllocatorDefault, MessagePort, 0);
}

// ########################## stopCurrentRunLoop
void CMacOSKeyboardAPI::stopCurrentRunLoop() {
  ::CFRunLoopStop(::CFRunLoopGetCurrent());
}

// ########################## sendMessage
SInt32 CMacOSKeyboardAPI::sendEmptyMessage(CFMessagePortRef MessagePort) {
  return CFMessagePortSendRequest(
        MessagePort, // The message port to which data should be sent.
        0,           // An arbitrary integer value that you can send with the message.
        NULL,        // The data to send to remote.
        0,           // The time to wait for data to be sent.
        0,           // The time to wait for a reply to be returned.
        NULL,        // The run loop mode in which the function should wait for a reply.
        NULL         // Upon return, contains a CFData object containing the reply data.
        );
}


// ########################## addSourceRunLoopТoCurrentRunLoop
void CMacOSKeyboardAPI::addSourceRunLoopТoCurrentRunLoop(CFRunLoopSourceRef RunLoopSource) {
  return ::CFRunLoopAddSource(::CFRunLoopGetCurrent(), RunLoopSource, ::kCFRunLoopCommonModes);
}


// ########################## copyCurrentKeyboardLayoutInputSource
TISInputSourceRef CMacOSKeyboardAPI::copyCurrentKeyboardLayoutInputSource() {
  Q_ASSERT(::CFEqual(::CFRunLoopGetCurrent(), ::CFRunLoopGetMain()));
  TISInputSourceRef CurrentKeyboardLayoutInputSource(TISCopyCurrentKeyboardLayoutInputSource());
  Q_ASSERT(::CFGetTypeID(CurrentKeyboardLayoutInputSource) == ::TISInputSourceGetTypeID());
  return CurrentKeyboardLayoutInputSource;
}

// ########################## getCurrentKeyboardLayout
const UCKeyboardLayout*
CMacOSKeyboardAPI::getCurrentKeyboardLayout(TISInputSourceRef CurrentKeyboardLayoutInputSource) {
  CFDataRef UnicodeKeyLayoutData =
      static_cast<CFDataRef>(::TISGetInputSourceProperty(
                                CurrentKeyboardLayoutInputSource,
                                ::kTISPropertyUnicodeKeyLayoutData));
  Q_ASSERT(CFGetTypeID(UnicodeKeyLayoutData) == CFDataGetTypeID());
  if (UnicodeKeyLayoutData == NULL) {
      return NULL;
  }
  return reinterpret_cast<const UCKeyboardLayout*>(CFDataGetBytePtr(UnicodeKeyLayoutData));
}

// ########################## getUnicodeString
UniCharCount CMacOSKeyboardAPI::getUnicodeString(
      const UCKeyboardLayout*   KeyboardLayout,
      CVKCode                   VKCode,
      UInt32*                   DeadKeyState,
      UniChar                   UnicodeString[]) {
  UInt32 ModifierKeyState = ::GetCurrentKeyModifiers();
  UniCharCount ActualStringLength;
  OSStatus Status = ::UCKeyTranslate(
          KeyboardLayout,
          VKCode,
          kUCKeyActionDown, // or kUCKeyActionDisplay
          (ModifierKeyState >> 8) & 0xFF,
          LMGetKbdType(),
          kNilOptions, // or kUCKeyTranslateNoDeadKeysMask
          DeadKeyState,
          kMaxStringLength,
          &ActualStringLength,
          UnicodeString);
  Q_ASSERT(Status == noErr && "UCKeyTranslate failed with error!");
  return ActualStringLength;
}


// ########################## getVKCode
CMacOSKeyboardAPI::CVKCode CMacOSKeyboardAPI::getVKCode(CGEventRef Event) {
  return ::CGEventGetIntegerValueField(Event, kCGKeyboardEventKeycode);
}

// ########################## getShifterState
bool CMacOSKeyboardAPI::getShifterState(CVKCode VKCode) {
  return ::CGEventSourceKeyState(::kCGEventSourceStateCombinedSessionState, VKCode);
}


// ########################## isPressing
bool CMacOSKeyboardAPI::isPressing(CGEventType Type, CShifterInfo& ShifterInfo, CVKCode VKCode) {
  if (Type == ::kCGEventFlagsChanged) {
    ShifterInfo.changeFlag(VKCode);
    return ShifterInfo.getState(VKCode);
  }
  return Type == ::kCGEventKeyDown;
}

bool CMacOSKeyboardAPI::isShifter(const CVKCode VKCode) {
  switch (VKCode) {
    case ::kVK_RightCommand:
    case ::kVK_Command:
    case ::kVK_Shift:
    case ::kVK_CapsLock:
    case ::kVK_Option:
    case ::kVK_Control:
    case ::kVK_RightShift:
    case ::kVK_RightOption:
    case ::kVK_RightControl:
    case ::kVK_Function:
      return true;
    default:
      return false;
  }
}

bool CMacOSKeyboardAPI::isCapsLock(const CVKCode VKCode) {
  return VKCode == ::kVK_CapsLock;
}

// ########################## isEqual
bool CMacOSKeyboardAPI::isEqual(CFTypeRef First, CFTypeRef Second) {
  if (First && Second) {
    return ::CFEqual(First, Second);
  }
  return !(First || Second);
}


// ########################## getKeyLabel
QString CMacOSKeyboardAPI::getKeyLabel(const CVKCode VKCode) {
  switch (VKCode) {
      //############################################# Modifier keys
      case ::kVK_RightCommand:  // 54 : 0x36
          return QString(::kCommandUnicode);  // 0x2318 /* Unicode PLACE OF INTEREST SIGN*/
      case ::kVK_Command:       // 55 : 0x37
          return QString(::kCommandUnicode);  // 0x2318 /* Unicode PLACE OF INTEREST SIGN*/
      case ::kVK_Shift:         // 56 : 0x38
          return QString(::kShiftUnicode);    // 0x21E7 /* Unicode UPWARDS WHITE ARROW*/
      case ::kVK_CapsLock:      // 57 : 0x39
          return QString(0x21EA);
      case ::kVK_Option:        // 58 : 0x3A
          return QString(::kOptionUnicode);   // 0x2325 /* Unicode OPTION KEY*/
      case ::kVK_Control:       // 59 : 0x3B
          return QString(::kControlUnicode);  // 0x2303 /* Unicode UP ARROWHEAD*/
      case ::kVK_RightShift:    // 60 : 0x3C
          return QString(::kShiftUnicode);    // 0x21E7 /* Unicode UPWARDS WHITE ARROW*/
      case ::kVK_RightOption:   // 61 : 0x3D
          return QString(::kOptionUnicode);   // 0x2325 /* Unicode OPTION KEY*/
      case ::kVK_RightControl:  // 62 : 0x3E
          return QString(::kControlUnicode);  // 0x2303 /* Unicode UP ARROWHEAD*/
      case ::kVK_Function:      // 63 : 0x3F
          return "fn";
      //############################################# Controls and symbols
      case ::kVK_Return:                  // 0x24
          return  QString(0x21A9);
      case ::kVK_Escape:                  // 0x35
          return "esc";
      case ::kVK_Delete:                  // 0x33
          return QString(0x232B);
      case ::kVK_ForwardDelete:           // 0x75
          return QString(0x2326);
      case ::kVK_Tab:                     // 0x30
          return QString(0x21E5);
      case ::kVK_Space:                   // 0x31
          return "";
      case ::kVK_ANSI_Minus:              // 0x1B
          return "-";
      case ::kVK_ANSI_Equal:              // 0x18
          return "=";
      case ::kVK_ANSI_LeftBracket:        // 0x21
          return "[";
      case ::kVK_ANSI_RightBracket:       // 0x1E
          return "]";
      case ::kVK_ANSI_Backslash:          // 0x2A
          return "\\";
      case ::kVK_ANSI_Semicolon:          // 0x29
          return ";";
      case ::kVK_ANSI_Quote:              // 0x27
          return "'";
      case ::kVK_ANSI_Grave:              // 0x32
          return "`";
      case ::kVK_ANSI_Comma:              // 0x2B
          return ",";
      case ::kVK_ANSI_Period:             // 0x2F
          return ".";
      case ::kVK_ANSI_Slash:              // 0x2C
          return "/";
      case ::kVK_ISO_Section:             // 0x0A
          return "§";
      //############################################# Arrow keys
      case ::kVK_UpArrow:                 // 0x7E
          return QString(0x2191);
      case ::kVK_DownArrow:               // 0x7D
          return QString(0x2193);
      case ::kVK_LeftArrow:               // 0x7B
          return QString(0x2190);
      case ::kVK_RightArrow:              // 0x7C
          return QString(0x2192);
      case ::kVK_PageUp:                  // 0x74
          return QString(0x21DE);
      case ::kVK_PageDown:                // 0x79
          return QString(0x21DF);
      case ::kVK_Home:                    // 0x79
          return QString(0x2196);
      case ::kVK_End:                     // 0x77
          return QString(0x2198);
      //############################################# Letter keys
      case ::kVK_ANSI_A:                  // 0x00
          return "A";
      case ::kVK_ANSI_B:                  // 0x0B
          return "B";
      case ::kVK_ANSI_C:                  // 0x08
          return "C";
      case ::kVK_ANSI_D:                  // 0x02
          return "D";
      case ::kVK_ANSI_E:                  // 0x0E
          return "E";
      case ::kVK_ANSI_F:                  // 0x03
          return "F";
      case ::kVK_ANSI_G:                  // 0x05
          return "G";
      case ::kVK_ANSI_H:                  // 0x04
          return "H";
      case ::kVK_ANSI_I:                  // 0x22
          return "I";
      case ::kVK_ANSI_J:                  // 0x26
          return "J";
      case ::kVK_ANSI_K:                  // 0x28
          return "K";
      case ::kVK_ANSI_L:                  // 0x25
          return "L";
      case ::kVK_ANSI_M:                  // 0x2E
          return "M";
      case ::kVK_ANSI_N:                  // 0x2D
          return "N";
      case ::kVK_ANSI_O:                  // 0x1F
          return "O";
      case ::kVK_ANSI_P:                  // 0x23
          return "P";
      case ::kVK_ANSI_Q:                  // 0x0C
          return "Q";
      case ::kVK_ANSI_R:                  // 0x0F
          return "R";
      case ::kVK_ANSI_S:                  // 0x01
          return "S";
      case ::kVK_ANSI_T:                  // 0x11
          return "T";
      case ::kVK_ANSI_U:                  // 0x20
          return "U";
      case ::kVK_ANSI_V:                  // 0x09
          return "V";
      case ::kVK_ANSI_W:                  // 0x0D
          return "W";
      case ::kVK_ANSI_X:                  // 0x07
          return "X";
      case ::kVK_ANSI_Y:                  // 0x10
          return "Y";
      case ::kVK_ANSI_Z:                  // 0x06
          return "Z";
      //############################################# Number keys
      case ::kVK_ANSI_1:                  // 0x12
          return "1";
      case ::kVK_ANSI_2:                  // 0x13
          return "2";
      case ::kVK_ANSI_3:                  // 0x14
          return "3";
      case ::kVK_ANSI_4:                  // 0x15
          return "4";
      case ::kVK_ANSI_5:                  // 0x17
          return "5";
      case ::kVK_ANSI_6:                  // 0x16
          return "6";
      case ::kVK_ANSI_7:                  // 0x1A
          return "7";
      case ::kVK_ANSI_8:                  // 0x1C
          return "8";
      case ::kVK_ANSI_9:                  // 0x19
          return "9";
      case ::kVK_ANSI_0:                  // 0x1D
          return "0";
      //############################################# Functions keys
      case ::kVK_F1:                      // 0x7A
          return "f1";
      case ::kVK_F2:                      // 0x78
          return "f2";
      case ::kVK_F3:                      // 0x63
          return "f3";
      case ::kVK_F4:                      // 0x76
          return "f4";
      case ::kVK_F5:                      // 0x60
          return "f5";
      case ::kVK_F6:                      // 0x61
          return "f6";
      case ::kVK_F7:                      // 0x62
          return "f7";
      case ::kVK_F8:                      // 0x64
          return "f8";
      case ::kVK_F9:                      // 0x65
          return "f9";
      case ::kVK_F10:                     // 0x6D
          return "f10";
      case ::kVK_F11:                     // 0x67
          return "f11";
      case ::kVK_F12:                     // 0x6F
          return "f12";
      case ::kVK_F13:                     // 0x69
          return "f13";
      case ::kVK_F14:                     // 0x6B
          return "f14";
      case ::kVK_F15:                     // 0x71
          return "f15";
      case ::kVK_F16:                     // 0x6A
          return "f16";
      case ::kVK_F17:                     // 0x40
          return "f17";
      case ::kVK_F18:                     // 0x4F
          return "f18";
      case ::kVK_F19:                     // 0x50
          return "f19";
      case ::kVK_F20:                     // 0x5A
          return "f20";
      //############################################# Keypad keys
      case ::kVK_ANSI_KeypadClear:        // 0x47
          return QString(0x2327);
      case ::kVK_ANSI_KeypadDivide:       // 0x4B
          return "/";
      case ::kVK_ANSI_KeypadMultiply:     // 0x43
          return "*";
      case ::kVK_ANSI_KeypadMinus:        // 0x4E
          return "-";
      case ::kVK_ANSI_KeypadPlus:         // 0x45
          return "+";
      case ::kVK_ANSI_KeypadEnter:        // 0x4C
          return QString(0x2324);
      case ::kVK_ANSI_Keypad1:            // 0x53
          return "1";
      case ::kVK_ANSI_Keypad2:            // 0x54
          return "2";
      case ::kVK_ANSI_Keypad3:            // 0x55
          return "3";
      case ::kVK_ANSI_Keypad4:            // 0x56
          return "4";
      case ::kVK_ANSI_Keypad5:            // 0x57
          return "5";
      case ::kVK_ANSI_Keypad6:            // 0x58
          return "6";
      case ::kVK_ANSI_Keypad7:            // 0x59
          return "7";
      case ::kVK_ANSI_Keypad8:            // 0x5B
          return "8";
      case ::kVK_ANSI_Keypad9:            // 0x5C
          return "9";
      case ::kVK_ANSI_Keypad0:            // 0x52
          return "0";
      case ::kVK_ANSI_KeypadDecimal:      // 0x41
          return ".";
      case ::kVK_ANSI_KeypadEquals:       // 0x51
          return "=";
      case ::kVK_JIS_KeypadComma:         // 0x5F
          return ",";
      //############################################# Keys in pc keyboards
      case ::kVK_Help:                    // 0x72
          return "help";
      //############################################# International keys
      case ::kVK_JIS_Underscore:          // 0x5E
          return "_";
      case ::kVK_JIS_Yen:                 // 0x5D
          return "¥";
      case ::kVK_JIS_Kana:                // 0x68
          return "Kana";
      case ::kVK_JIS_Eisu:                // 0x66
          return "Eisu";
      //############################################# Other
      default:
          return "";
  }
}

// ########################## getKeyName
QString CMacOSKeyboardAPI::getKeyName(const CVKCode VKCode) {
    switch (VKCode) {
        //############################################# Modifier keys
        case ::kVK_RightCommand:            // 54 : 0x36
            return "RightCommand";
        case ::kVK_Command:                 // 55 : 0x37
            return "LeftCommand";
        case ::kVK_Shift:                   // 56 : 0x38
            return "LeftShift";
        case ::kVK_CapsLock:                // 57 : 0x39
            return "CapsLock";
        case ::kVK_Option:                  // 58 : 0x3A
            return "LeftOption";
        case ::kVK_Control:                 // 59 : 0x3B
            return "LeftControl";
        case ::kVK_RightShift:              // 60 : 0x3C
            return "RightShift";
        case ::kVK_RightOption:             // 61 : 0x3D
            return "RightOption";
        case ::kVK_RightControl:            // 62 : 0x3E
            return "RightControl";
        case ::kVK_Function:                // 63 : 0x3F
            return "fn";
        //############################################# Controls and symbols
        case ::kVK_Return:                  // 0x24
            return "Return";
        case ::kVK_Escape:                  // 0x35
            return "Escape";
        case ::kVK_Delete:                  // 0x33
            return "Delete";
        case ::kVK_ForwardDelete:           // 0x75
            return "ForwardDelete";
        case ::kVK_Tab:                     // 0x30
            return "Tab";
        case ::kVK_Space:                   // 0x31
            return "Space";
        case ::kVK_ANSI_Minus:              // 0x1B
            return "ANSI_Minus";
        case ::kVK_ANSI_Equal:              // 0x18
            return "ANSI_Equal";
        case ::kVK_ANSI_LeftBracket:        // 0x21
            return "ANSI_LeftBracket";
        case ::kVK_ANSI_RightBracket:       // 0x1E
            return "ANSI_RightBracket";
        case ::kVK_ANSI_Backslash:          // 0x2A
            return "ANSI_Backslash";
        case ::kVK_ANSI_Semicolon:          // 0x29
            return "ANSI_Semicolon";
        case ::kVK_ANSI_Quote:              // 0x27
            return "ANSI_Quote";
        case ::kVK_ANSI_Grave:              // 0x32
            return "ANSI_Grave";
        case ::kVK_ANSI_Comma:              // 0x2B
            return "ANSI_Comma";
        case ::kVK_ANSI_Period:             // 0x2F
            return "ANSI_Period";
        case ::kVK_ANSI_Slash:              // 0x2C
            return "ANSI_Slash";
        case ::kVK_ISO_Section:             // 0x0A
            return "ISO_Section";
        //############################################# Arrow keys
        case ::kVK_UpArrow:                 // 0x7E
            return "UpArrow";
        case ::kVK_DownArrow:               // 0x7D
            return "DownArrow";
        case ::kVK_LeftArrow:               // 0x7B
            return "LeftArrow";
        case ::kVK_RightArrow:              // 0x7C
            return "RightArrow";
        case ::kVK_PageUp:                  // 0x74
            return "PageUp";
        case ::kVK_PageDown:                // 0x79
            return "PageDown";
        case ::kVK_Home:                    // 0x79
            return "Home";
        case ::kVK_End:                     // 0x77
            return "End";
        //############################################# Letter keys
        case ::kVK_ANSI_A:                  // 0x00
            return "ANSI_A";
        case ::kVK_ANSI_B:                  // 0x0B
            return "ANSI_B";
        case ::kVK_ANSI_C:                  // 0x08
            return "ANSI_C";
        case ::kVK_ANSI_D:                  // 0x02
            return "ANSI_D";
        case ::kVK_ANSI_E:                  // 0x0E
            return "ANSI_E";
        case ::kVK_ANSI_F:                  // 0x03
            return "ANSI_F";
        case ::kVK_ANSI_G:                  // 0x05
            return "ANSI_G";
        case ::kVK_ANSI_H:                  // 0x04
            return "ANSI_H";
        case ::kVK_ANSI_I:                  // 0x22
            return "ANSI_I";
        case ::kVK_ANSI_J:                  // 0x26
            return "ANSI_J";
        case ::kVK_ANSI_K:                  // 0x28
            return "ANSI_K";
        case ::kVK_ANSI_L:                  // 0x25
            return "ANSI_L";
        case ::kVK_ANSI_M:                  // 0x2E
            return "ANSI_M";
        case ::kVK_ANSI_N:                  // 0x2D
            return "ANSI_N";
        case ::kVK_ANSI_O:                  // 0x1F
            return "ANSI_O";
        case ::kVK_ANSI_P:                  // 0x23
            return "ANSI_P";
        case ::kVK_ANSI_Q:                  // 0x0C
            return "ANSI_Q";
        case ::kVK_ANSI_R:                  // 0x0F
            return "ANSI_R";
        case ::kVK_ANSI_S:                  // 0x01
            return "ANSI_S";
        case ::kVK_ANSI_T:                  // 0x11
            return "ANSI_T";
        case ::kVK_ANSI_U:                  // 0x20
            return "ANSI_U";
        case ::kVK_ANSI_V:                  // 0x09
            return "ANSI_V";
        case ::kVK_ANSI_W:                  // 0x0D
            return "ANSI_W";
        case ::kVK_ANSI_X:                  // 0x07
            return "ANSI_X";
        case ::kVK_ANSI_Y:                  // 0x10
            return "ANSI_Y";
        case ::kVK_ANSI_Z:                  // 0x06
            return "ANSI_Z";
        //############################################# Number keys
        case ::kVK_ANSI_1:                  // 0x12
            return "ANSI_1";
        case ::kVK_ANSI_2:                  // 0x13
            return "ANSI_2";
        case ::kVK_ANSI_3:                  // 0x14
            return "ANSI_3";
        case ::kVK_ANSI_4:                  // 0x15
            return "ANSI_4";
        case ::kVK_ANSI_5:                  // 0x17
            return "ANSI_5";
        case ::kVK_ANSI_6:                  // 0x16
            return "ANSI_6";
        case ::kVK_ANSI_7:                  // 0x1A
            return "ANSI_7";
        case ::kVK_ANSI_8:                  // 0x1C
            return "ANSI_8";
        case ::kVK_ANSI_9:                  // 0x19
            return "ANSI_9";
        case ::kVK_ANSI_0:                  // 0x1D
            return "ANSI_0";
        //############################################# Functions keys
        case ::kVK_F1:                      // 0x7A
            return "F1";
        case ::kVK_F2:                      // 0x78
            return "F2";
        case ::kVK_F3:                      // 0x63
            return "F3";
        case ::kVK_F4:                      // 0x76
            return "F4";
        case ::kVK_F5:                      // 0x60
            return "F5";
        case ::kVK_F6:                      // 0x61
            return "F6";
        case ::kVK_F7:                      // 0x62
            return "F7";
        case ::kVK_F8:                      // 0x64
            return "F8";
        case ::kVK_F9:                      // 0x65
            return "F9";
        case ::kVK_F10:                     // 0x6D
            return "F10";
        case ::kVK_F11:                     // 0x67
            return "F11";
        case ::kVK_F12:                     // 0x6F
            return "F12";
        case ::kVK_F13:                     // 0x69
            return "F13";
        case ::kVK_F14:                     // 0x6B
            return "F14";
        case ::kVK_F15:                     // 0x71
            return "F15";
        case ::kVK_F16:                     // 0x6A
            return "F16";
        case ::kVK_F17:                     // 0x40
            return "F17";
        case ::kVK_F18:                     // 0x4F
            return "F18";
        case ::kVK_F19:                     // 0x50
            return "F19";
        case ::kVK_F20:                     // 0x5A
            return "F20";
        //############################################# Keypad keys
        case ::kVK_ANSI_KeypadClear:        // 0x47
            return "ANSI_KeypadClear";
        case ::kVK_ANSI_KeypadDivide:       // 0x4B
            return "ANSI_KeypadDivide";
        case ::kVK_ANSI_KeypadMultiply:     // 0x43
            return "ANSI_KeypadMultiply";
        case ::kVK_ANSI_KeypadMinus:        // 0x4E
            return "ANSI_KeypadMinus";
        case ::kVK_ANSI_KeypadPlus:         // 0x45
            return "ANSI_KeypadPlus";
        case ::kVK_ANSI_KeypadEnter:        // 0x4C
            return "ANSI_KeypadEnter";
        case ::kVK_ANSI_Keypad1:            // 0x53
            return "ANSI_Keypad1";
        case ::kVK_ANSI_Keypad2:            // 0x54
            return "ANSI_Keypad2";
        case ::kVK_ANSI_Keypad3:            // 0x55
            return "ANSI_Keypad3";
        case ::kVK_ANSI_Keypad4:            // 0x56
            return "ANSI_Keypad4";
        case ::kVK_ANSI_Keypad5:            // 0x57
            return "ANSI_Keypad5";
        case ::kVK_ANSI_Keypad6:            // 0x58
            return "ANSI_Keypad6";
        case ::kVK_ANSI_Keypad7:            // 0x59
            return "ANSI_Keypad7";
        case ::kVK_ANSI_Keypad8:            // 0x5B
            return "ANSI_Keypad8";
        case ::kVK_ANSI_Keypad9:            // 0x5C
            return "ANSI_Keypad9";
        case ::kVK_ANSI_Keypad0:            // 0x52
            return "ANSI_Keypad0";
        case ::kVK_ANSI_KeypadDecimal:      // 0x41
            return "ANSI_KeypadDecimal";
        case ::kVK_ANSI_KeypadEquals:       // 0x51
            return "ANSI_KeypadEquals";
        case ::kVK_JIS_KeypadComma:         // 0x5F
            return "JIS_KeypadComma";
        //############################################# Keys in pc keyboards
        case ::kVK_Help:                    // 0x72
            return "Help";
        //############################################# International keys
        case ::kVK_JIS_Underscore:          // 0x5E
            return "JIS_Underscore";
        case ::kVK_JIS_Yen:                 // 0x5D
            return "JIS_Yen";
        case ::kVK_JIS_Kana:                // 0x68
            return "JIS_Kana";
        case ::kVK_JIS_Eisu:                // 0x66
            return "JIS_Eisu";
        //############################################# Other
        default:
            return "unknow";
    }
}

} // namespace NSMacOS
} // namespace NSKeyboard
} // namespace NSApplication
