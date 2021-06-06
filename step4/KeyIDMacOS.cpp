#include "KeyIDMacOS.h"

namespace NSApplication {
namespace NSKeyboard {
namespace NSMacOS {

CKeyID CKeyIDMacOS::make(const CVKCode VKCode) {
  switch (VKCode) {
      case ::kVK_ANSI_A:                    // 0x00
          return CKeyIDEnum::A;
      case ::kVK_ANSI_S:                    // 0x01
          return CKeyIDEnum::S;
      case ::kVK_ANSI_D:                    // 0x02
          return CKeyIDEnum::D;
      case ::kVK_ANSI_F:                    // 0x03
          return CKeyIDEnum::F;
      case ::kVK_ANSI_H:                    // 0x04
          return CKeyIDEnum::H;
      case ::kVK_ANSI_G:                    // 0x05
          return CKeyIDEnum::G;
      case ::kVK_ANSI_Z:                    // 0x06
          return CKeyIDEnum::Z;
      case ::kVK_ANSI_X:                    // 0x07
          return CKeyIDEnum::X;
      case ::kVK_ANSI_C:                    // 0x08
          return CKeyIDEnum::C;
      case ::kVK_ANSI_V:                    // 0x09
          return CKeyIDEnum::V;
      case ::kVK_ISO_Section:               // 0x0A // TODO
          return CKeyIDEnum::Unknown;
      case ::kVK_ANSI_B:                    // 0x0B
          return CKeyIDEnum::B;
      case ::kVK_ANSI_Q:                    // 0x0C
          return CKeyIDEnum::Q;
      case ::kVK_ANSI_W:                    // 0x0D
          return CKeyIDEnum::W;
      case ::kVK_ANSI_E:                    // 0x0E
          return CKeyIDEnum::E;
      case ::kVK_ANSI_R:                    // 0x0F
          return CKeyIDEnum::R;
      case ::kVK_ANSI_Y:                    // 0x10
          return CKeyIDEnum::Y;
      case ::kVK_ANSI_T:                    // 0x11
          return CKeyIDEnum::T;
      case ::kVK_ANSI_1:                    // 0x12
          return CKeyIDEnum::VK_1;
      case ::kVK_ANSI_2:                    // 0x13
          return CKeyIDEnum::VK_2;
      case ::kVK_ANSI_3:                    // 0x14
          return CKeyIDEnum::VK_3;
      case ::kVK_ANSI_4:                    // 0x15
          return CKeyIDEnum::VK_4;
      case ::kVK_ANSI_6:                    // 0x16
          return CKeyIDEnum::VK_6;
      case ::kVK_ANSI_5:                    // 0x17
          return CKeyIDEnum::VK_5;
      case ::kVK_ANSI_Equal:                // 0x18
          return CKeyIDEnum::Eng_Plus;
      case ::kVK_ANSI_9:                    // 0x19
          return CKeyIDEnum::VK_9;
      case ::kVK_ANSI_7:                    // 0x1A
          return CKeyIDEnum::VK_7;
      case ::kVK_ANSI_Minus:                // 0x1B
          return CKeyIDEnum::Eng_Minus;
      case ::kVK_ANSI_8:                    // 0x1C
          return CKeyIDEnum::VK_8;
      case ::kVK_ANSI_0:                    // 0x1D
          return CKeyIDEnum::VK_0;
      case ::kVK_ANSI_RightBracket:         // 0x1E
          return CKeyIDEnum::Eng_Right_Brace;
      case ::kVK_ANSI_O:                    // 0x1F
          return CKeyIDEnum::O;
      case ::kVK_ANSI_U:                    // 0x20
          return CKeyIDEnum::U;
      case ::kVK_ANSI_LeftBracket:          // 0x21
          return CKeyIDEnum::Eng_Left_Brace;
      case ::kVK_ANSI_I:                    // 0x22
          return CKeyIDEnum::I;
      case ::kVK_ANSI_P:                    // 0x23
          return CKeyIDEnum::P;
      case ::kVK_Return:                    // 0x24 // TODO
          return CKeyIDEnum::Unknown;
      case ::kVK_ANSI_L:                    // 0x25
          return CKeyIDEnum::L;
      case ::kVK_ANSI_J:                    // 0x26
          return CKeyIDEnum::J;
      case ::kVK_ANSI_Quote:                // 0x27
          return CKeyIDEnum::Eng_Quote;
      case ::kVK_ANSI_K:                    // 0x28
          return CKeyIDEnum::K;
      case ::kVK_ANSI_Semicolon:            // 0x29
          return CKeyIDEnum::Eng_Semicolon;
      case ::kVK_ANSI_Backslash:            // 0x2A
          return CKeyIDEnum::Eng_Backslash;
      case ::kVK_ANSI_Comma:                // 0x2B
          return CKeyIDEnum::Eng_Comma;
      case ::kVK_ANSI_Slash:                // 0x2C
          return CKeyIDEnum::Eng_Slash_Question;
      case ::kVK_ANSI_N:                    // 0x2D
          return CKeyIDEnum::N;
      case ::kVK_ANSI_M:                    // 0x2E
          return CKeyIDEnum::M;
      case ::kVK_ANSI_Period:               // 0x2F
          return CKeyIDEnum::Eng_Period;
      case ::kVK_Tab:                       // 0x30
          return CKeyIDEnum::Tab;
      case ::kVK_Space:                     // 0x31
          return CKeyIDEnum::Spacebar;
      case ::kVK_ANSI_Grave:                // 0x32
          return CKeyIDEnum::Eng_Tilde;
      case ::kVK_Delete:                    // 0x33
          return CKeyIDEnum::Backspace;
      case ::kVK_Escape:                    // 0x35
          return CKeyIDEnum::Esc;
      case ::kVK_RightCommand:              // 0x36 // TODO
          return CKeyIDEnum::RightWin;
      case ::kVK_Command:                   // 0x37 // TODO
          return CKeyIDEnum::LeftWin;
      case ::kVK_Shift:                     // 0x38
          return CKeyIDEnum::LeftShift;
      case ::kVK_CapsLock:                  // 0x39
          return CKeyIDEnum::Capslock;
      case ::kVK_Option:                    // 0x3A // TODO
          return CKeyIDEnum::LeftAlt;
      case ::kVK_Control:                   // 0x3B
          return CKeyIDEnum::LeftCtrl;
      case ::kVK_RightShift:                // 0x3C
          return CKeyIDEnum::RightShift;
      case ::kVK_RightOption:               // 0x3D // TODO
          return CKeyIDEnum::RightAlt;
      case ::kVK_RightControl:              // 0x3E
          return CKeyIDEnum::RightCtrl;
      case ::kVK_Function:                  // 0x3F // TODO (this is fn)
          return CKeyIDEnum::Unknown;
      case ::kVK_F17:                       // 0x40 // TODO
          return CKeyIDEnum::Unknown;
      case ::kVK_ANSI_KeypadDecimal:        // 0x41
          return CKeyIDEnum::Decimal;
      case ::kVK_ANSI_KeypadMultiply:       // 0x43
          return CKeyIDEnum::Multiply;
      case ::kVK_ANSI_KeypadPlus:           // 0x45
          return CKeyIDEnum::Add;
      case ::kVK_ANSI_KeypadClear:          // 0x47 // TODO
          return CKeyIDEnum::Numlock;
      case ::kVK_VolumeUp:                  // 0x48 // TODO
          return CKeyIDEnum::Unknown;
      case ::kVK_VolumeDown:                // 0x49 // TODO
          return CKeyIDEnum::Unknown;
      case ::kVK_Mute:                      // 0x4A // TODO
          return CKeyIDEnum::Unknown;
      case ::kVK_ANSI_KeypadDivide:         // 0x4B
          return CKeyIDEnum::Divide;
      case ::kVK_ANSI_KeypadEnter:          // 0x4C
          return CKeyIDEnum::Enter;
      case ::kVK_ANSI_KeypadMinus:          // 0x4E
          return CKeyIDEnum::Subtract;
      case ::kVK_F18:                       // 0x4F // TODO
          return CKeyIDEnum::Unknown;
      case ::kVK_F19:                       // 0x50 // TODO
          return CKeyIDEnum::Unknown;
      case ::kVK_ANSI_KeypadEquals:         // 0x51 // TODO
          return CKeyIDEnum::Unknown;
      case ::kVK_ANSI_Keypad0:              // 0x52
          return CKeyIDEnum::Numpad_0;
      case ::kVK_ANSI_Keypad1:              // 0x53
          return CKeyIDEnum::Numpad_1;
      case ::kVK_ANSI_Keypad2:              // 0x54
          return CKeyIDEnum::Numpad_2;
      case ::kVK_ANSI_Keypad3:              // 0x55
          return CKeyIDEnum::Numpad_3;
      case ::kVK_ANSI_Keypad4:              // 0x56
          return CKeyIDEnum::Numpad_4;
      case ::kVK_ANSI_Keypad5:              // 0x57
          return CKeyIDEnum::Numpad_5;
      case ::kVK_ANSI_Keypad6:              // 0x58
          return CKeyIDEnum::Numpad_6;
      case ::kVK_ANSI_Keypad7:              // 0x59
          return CKeyIDEnum::Numpad_7;
      case ::kVK_F20:                       // 0x5A // TODO
          return CKeyIDEnum::Unknown;
      case ::kVK_ANSI_Keypad8:              // 0x5B
          return CKeyIDEnum::Numpad_8;
      case ::kVK_ANSI_Keypad9:              // 0x5C
          return CKeyIDEnum::Numpad_9;
      case ::kVK_JIS_Yen:                   // 0x5D // TODO
          return CKeyIDEnum::Unknown;
      case ::kVK_JIS_Underscore:            // 0x5E // TODO
          return CKeyIDEnum::Unknown;
      case ::kVK_JIS_KeypadComma:           // 0x5F // TODO
          return CKeyIDEnum::Unknown;
      case ::kVK_F5:                        // 0x60
          return CKeyIDEnum::F5;
      case ::kVK_F6:                        // 0x61
          return CKeyIDEnum::F6;
      case ::kVK_F7:                        // 0x62
          return CKeyIDEnum::F7;
      case ::kVK_F3:                        // 0x63
          return CKeyIDEnum::F3;
      case ::kVK_F8:                        // 0x64
          return CKeyIDEnum::F8;
      case ::kVK_F9:                        // 0x65
          return CKeyIDEnum::F9;
      case ::kVK_JIS_Eisu:                  // 0x66 // TODO
          return CKeyIDEnum::Unknown;
      case ::kVK_F11:                       // 0x67
          return CKeyIDEnum::F11;
      case ::kVK_JIS_Kana:                  // 0x68 // TODO
          return CKeyIDEnum::Unknown;
      case ::kVK_F13:                       // 0x69 // TODO
          return CKeyIDEnum::Unknown;
      case ::kVK_F16:                       // 0x6A // TODO
          return CKeyIDEnum::Unknown;
      case ::kVK_F14:                       // 0x6B // TODO
          return CKeyIDEnum::Unknown;
      case ::kVK_F10:                       // 0x6D
          return CKeyIDEnum::F10;
      case ::kVK_F12:                       // 0x6F
          return CKeyIDEnum::F12;
      case ::kVK_F15:                       // 0x71 // TODO
          return CKeyIDEnum::Unknown;
      case ::kVK_Help:                      // 0x72 // TODO
          return CKeyIDEnum::Unknown;
      case ::kVK_Home:                      // 0x73
          return CKeyIDEnum::Home;
      case ::kVK_PageUp:                    // 0x74
          return CKeyIDEnum::PageUp;
      case ::kVK_ForwardDelete:             // 0x75
          return CKeyIDEnum::Delete;
      case ::kVK_F4:                        // 0x76
          return CKeyIDEnum::F4;
      case ::kVK_End:                       // 0x77
          return CKeyIDEnum::End;
      case ::kVK_F2:                        // 0x78
          return CKeyIDEnum::F2;
      case ::kVK_PageDown:                  // 0x79
          return CKeyIDEnum::PageDown;
      case ::kVK_F1:                        // 0x7A
          return CKeyIDEnum::F1;
      case ::kVK_LeftArrow:                 // 0x7B
          return CKeyIDEnum::LeftArrow;
      case ::kVK_RightArrow:                // 0x7C
          return CKeyIDEnum::RightArrow;
      case ::kVK_DownArrow:                 // 0x7D
          return CKeyIDEnum::DownArrow;
      case ::kVK_UpArrow:                   // 0x7E
          return CKeyIDEnum::UpArrow;
      default:
          return CKeyIDEnum::Unknown;
  }
}

} // namespace NSMacOS
} // namespace NSKeyboard
} // namespace NSApplication
