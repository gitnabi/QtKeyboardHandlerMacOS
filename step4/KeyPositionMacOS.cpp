#include "KeyPositionMacOS.h"

namespace NSApplication {
namespace NSKeyboard {
namespace NSMacOS {

CKeyPosition CKeyPositionMacOS::make(const CVKCode VKCode) {
  switch (VKCode) {
      case ::kVK_ANSI_A:                    // 0x00
          return CKeyPosEnum::AC01;
      case ::kVK_ANSI_S:                    // 0x01
          return CKeyPosEnum::AC02;
      case ::kVK_ANSI_D:                    // 0x02
          return CKeyPosEnum::AC03;
      case ::kVK_ANSI_F:                    // 0x03
          return CKeyPosEnum::AC04;
      case ::kVK_ANSI_H:                    // 0x04
          return CKeyPosEnum::AC06;
      case ::kVK_ANSI_G:                    // 0x05
          return CKeyPosEnum::AC05;
      case ::kVK_ANSI_Z:                    // 0x06
          return CKeyPosEnum::AB01;
      case ::kVK_ANSI_X:                    // 0x07
          return CKeyPosEnum::AB02;
      case ::kVK_ANSI_C:                    // 0x08
          return CKeyPosEnum::AB03;
      case ::kVK_ANSI_V:                    // 0x09
          return CKeyPosEnum::AB04;
      case ::kVK_ISO_Section:               // 0x0A
          return CKeyPosEnum::AE00;
      case ::kVK_ANSI_B:                    // 0x0B
          return CKeyPosEnum::AB05;
      case ::kVK_ANSI_Q:                    // 0x0C
          return CKeyPosEnum::AD01;
      case ::kVK_ANSI_W:                    // 0x0D
          return CKeyPosEnum::AD02;
      case ::kVK_ANSI_E:                    // 0x0E
          return CKeyPosEnum::AD03;
      case ::kVK_ANSI_R:                    // 0x0F
          return CKeyPosEnum::AD04;
      case ::kVK_ANSI_Y:                    // 0x10
          return CKeyPosEnum::AD06;
      case ::kVK_ANSI_T:                    // 0x11
          return CKeyPosEnum::AD05;
      case ::kVK_ANSI_1:                    // 0x12
          return CKeyPosEnum::AE01;
      case ::kVK_ANSI_2:                    // 0x13
          return CKeyPosEnum::AE02;
      case ::kVK_ANSI_3:                    // 0x14
          return CKeyPosEnum::AE03;
      case ::kVK_ANSI_4:                    // 0x15
          return CKeyPosEnum::AE04;
      case ::kVK_ANSI_6:                    // 0x16
          return CKeyPosEnum::AE06;
      case ::kVK_ANSI_5:                    // 0x17
          return CKeyPosEnum::AE05;
      case ::kVK_ANSI_Equal:                // 0x18
          return CKeyPosEnum::AE12;
      case ::kVK_ANSI_9:                    // 0x19
          return CKeyPosEnum::AE09;
      case ::kVK_ANSI_7:                    // 0x1A
          return CKeyPosEnum::AE07;
      case ::kVK_ANSI_Minus:                // 0x1B
          return CKeyPosEnum::AE11;
      case ::kVK_ANSI_8:                    // 0x1C
          return CKeyPosEnum::AE08;
      case ::kVK_ANSI_0:                    // 0x1D
          return CKeyPosEnum::AE10;
      case ::kVK_ANSI_RightBracket:         // 0x1E
          return CKeyPosEnum::AD12;
      case ::kVK_ANSI_O:                    // 0x1F
          return CKeyPosEnum::AD09;
      case ::kVK_ANSI_U:                    // 0x20
          return CKeyPosEnum::AD07;
      case ::kVK_ANSI_LeftBracket:          // 0x21
          return CKeyPosEnum::AD11;
      case ::kVK_ANSI_I:                    // 0x22
          return CKeyPosEnum::AD08;
      case ::kVK_ANSI_P:                    // 0x23
          return CKeyPosEnum::AD10;
      case ::kVK_Return:                    // 0x24
          return CKeyPosEnum::RTRN;
      case ::kVK_ANSI_L:                    // 0x25
          return CKeyPosEnum::AC09;
      case ::kVK_ANSI_J:                    // 0x26
          return CKeyPosEnum::AC07;
      case ::kVK_ANSI_Quote:                // 0x27
          return CKeyPosEnum::AC11;
      case ::kVK_ANSI_K:                    // 0x28
          return CKeyPosEnum::AC08;
      case ::kVK_ANSI_Semicolon:            // 0x29
          return CKeyPosEnum::AC10;
      case ::kVK_ANSI_Backslash:            // 0x2A
          return CKeyPosEnum::BKSL;
      case ::kVK_ANSI_Comma:                // 0x2B
          return CKeyPosEnum::AB08;
      case ::kVK_ANSI_Slash:                // 0x2C
          return CKeyPosEnum::AB10;
      case ::kVK_ANSI_N:                    // 0x2D
          return CKeyPosEnum::AB06;
      case ::kVK_ANSI_M:                    // 0x2E
          return CKeyPosEnum::AB07;
      case ::kVK_ANSI_Period:               // 0x2F
          return CKeyPosEnum::AB09;
      case ::kVK_Tab:                       // 0x30
          return CKeyPosEnum::TAB;
      case ::kVK_Space:                     // 0x31
          return CKeyPosEnum::SPCE;
      case ::kVK_ANSI_Grave:                // 0x32
          return CKeyPosEnum::TLDE;
      case ::kVK_Delete:                    // 0x33
          return CKeyPosEnum::BKSP;
      case ::kVK_Escape:                    // 0x35
          return CKeyPosEnum::ESC;
      case ::kVK_RightCommand:              // 0x36
          return CKeyPosEnum::RALT;
      case ::kVK_Command:                   // 0x37
          return CKeyPosEnum::LALT;
      case ::kVK_Shift:                     // 0x38
          return CKeyPosEnum::LFSH;
      case ::kVK_CapsLock:                  // 0x39
          return CKeyPosEnum::CAPS;
      case ::kVK_Option:                    // 0x3A
          return CKeyPosEnum::LWIN;
      case ::kVK_Control:                   // 0x3B
          return CKeyPosEnum::LCTL;
      case ::kVK_RightShift:                // 0x3C
          return CKeyPosEnum::RTSH;
      case ::kVK_RightOption:               // 0x3D
          return CKeyPosEnum::RWIN;
      case ::kVK_RightControl:              // 0x3E
          return CKeyPosEnum::RCTL;
      case ::kVK_Function:                  // 0x3F // TODO (this is fn)
          return CKeyPosEnum::UNKN;
      case ::kVK_F17:                       // 0x40 // TODO
          return CKeyPosEnum::UNKN;
      case ::kVK_ANSI_KeypadDecimal:        // 0x41
          return CKeyPosEnum::kPDL; // kPDL -> KPDL
      case ::kVK_ANSI_KeypadMultiply:       // 0x43
          return CKeyPosEnum::KPSU;
      case ::kVK_ANSI_KeypadPlus:           // 0x45
          return CKeyPosEnum::KPAD;
      case ::kVK_ANSI_KeypadClear:          // 0x47
          return CKeyPosEnum::NMLK;
      case ::kVK_VolumeUp:                  // 0x48 // TODO
          return CKeyPosEnum::UNKN;
      case ::kVK_VolumeDown:                // 0x49 // TODO
          return CKeyPosEnum::UNKN;
      case ::kVK_Mute:                      // 0x4A // TODO
          return CKeyPosEnum::UNKN;
      case ::kVK_ANSI_KeypadDivide:         // 0x4B
          return CKeyPosEnum::KPMU;
      case ::kVK_ANSI_KeypadEnter:          // 0x4C
          return CKeyPosEnum::KPEN;
      case ::kVK_ANSI_KeypadMinus:          // 0x4E
          return CKeyPosEnum::KPSU;
      case ::kVK_F18:                       // 0x4F // TODO
          return CKeyPosEnum::UNKN;
      case ::kVK_F19:                       // 0x50 // TODO
          return CKeyPosEnum::UNKN;
      case ::kVK_ANSI_KeypadEquals:         // 0x51 // TODO
          return CKeyPosEnum::KPDV;
      case ::kVK_ANSI_Keypad0:              // 0x52
          return CKeyPosEnum::kP0; // kP0 -> KP0
      case ::kVK_ANSI_Keypad1:              // 0x53
          return CKeyPosEnum::KP1;
      case ::kVK_ANSI_Keypad2:              // 0x54
          return CKeyPosEnum::KP2;
      case ::kVK_ANSI_Keypad3:              // 0x55
          return CKeyPosEnum::KP3;
      case ::kVK_ANSI_Keypad4:              // 0x56
          return CKeyPosEnum::KP4;
      case ::kVK_ANSI_Keypad5:              // 0x57
          return CKeyPosEnum::KP5;
      case ::kVK_ANSI_Keypad6:              // 0x58
          return CKeyPosEnum::KP6;
      case ::kVK_ANSI_Keypad7:              // 0x59
          return CKeyPosEnum::KP7;
      case ::kVK_F20:                       // 0x5A // TODO
          return CKeyPosEnum::UNKN;
      case ::kVK_ANSI_Keypad8:              // 0x5B
          return CKeyPosEnum::KP8;
      case ::kVK_ANSI_Keypad9:              // 0x5C
          return CKeyPosEnum::KP9;
      case ::kVK_JIS_Yen:                   // 0x5D // TODO
          return CKeyPosEnum::UNKN;
      case ::kVK_JIS_Underscore:            // 0x5E // TODO
          return CKeyPosEnum::UNKN;
      case ::kVK_JIS_KeypadComma:           // 0x5F // TODO
          return CKeyPosEnum::UNKN;
      case ::kVK_F5:                        // 0x60
          return CKeyPosEnum::FK05;
      case ::kVK_F6:                        // 0x61
          return CKeyPosEnum::FK06;
      case ::kVK_F7:                        // 0x62
          return CKeyPosEnum::FK07;
      case ::kVK_F3:                        // 0x63
          return CKeyPosEnum::FK03;
      case ::kVK_F8:                        // 0x64
          return CKeyPosEnum::FK08;
      case ::kVK_F9:                        // 0x65
          return CKeyPosEnum::FK09;
      case ::kVK_JIS_Eisu:                  // 0x66 // TODO
          return CKeyPosEnum::UNKN;
      case ::kVK_F11:                       // 0x67
          return CKeyPosEnum::FK11;
      case ::kVK_JIS_Kana:                  // 0x68 // TODO
          return CKeyPosEnum::UNKN;
      case ::kVK_F13:                       // 0x69 // TODO
          return CKeyPosEnum::UNKN;
      case ::kVK_F16:                       // 0x6A // TODO
          return CKeyPosEnum::UNKN;
      case ::kVK_F14:                       // 0x6B // TODO
          return CKeyPosEnum::UNKN;
      case ::kVK_F10:                       // 0x6D
          return CKeyPosEnum::FK10;
      case ::kVK_F12:                       // 0x6F
          return CKeyPosEnum::FK12;
      case ::kVK_F15:                       // 0x71 // TODO
          return CKeyPosEnum::UNKN;
      case ::kVK_Help:                      // 0x72 // TODO
          return CKeyPosEnum::UNKN;
      case ::kVK_Home:                      // 0x73
          return CKeyPosEnum::HOME;
      case ::kVK_PageUp:                    // 0x74
          return CKeyPosEnum::PGUP;
      case ::kVK_ForwardDelete:             // 0x75
          return CKeyPosEnum::DELE;
      case ::kVK_F4:                        // 0x76
          return CKeyPosEnum::FK04;
      case ::kVK_End:                       // 0x77
          return CKeyPosEnum::END;
      case ::kVK_F2:                        // 0x78
          return CKeyPosEnum::FK02;
      case ::kVK_PageDown:                  // 0x79
          return CKeyPosEnum::PGDN;
      case ::kVK_F1:                        // 0x7A
          return CKeyPosEnum::FK01;
      case ::kVK_LeftArrow:                 // 0x7B
          return CKeyPosEnum::LEFT;
      case ::kVK_RightArrow:                // 0x7C
          return CKeyPosEnum::RGHT;
      case ::kVK_DownArrow:                 // 0x7D
          return CKeyPosEnum::DOWN;
      case ::kVK_UpArrow:                   // 0x7E
          return CKeyPosEnum::UP;
      default:
          return CKeyPosEnum::UNKN;
  }
}
} // namespace NSMacOS
} // namespace NSKeyboard
} // namespace NSApplication
