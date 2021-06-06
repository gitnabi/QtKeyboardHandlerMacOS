#include "ShifterInfo.h"

namespace NSApplication {
namespace NSKeyboard {
namespace NSMacOS {

CShifterInfo::CShifterInfo() {
  for (auto VKCode : AllShifters_) {
    ShifterState_[VKCode] = CMacOSKeyboardAPI::getShifterState(toBasicShifter(VKCode));
  }
}

void CShifterInfo::changeFlag(CVKCode VKCode) {
  ShifterState_[VKCode] = !ShifterState_[VKCode];
}

bool CShifterInfo::getState(CVKCode VKCode) const {
  return ShifterState_.at(VKCode);
}

CShifterInfo::CVKCode
CShifterInfo::toBasicShifter(CVKCode VKCode) const {
  switch(VKCode) {
    case ::kVK_RightCommand:  // 54 : 0x36
      return ::kVK_Command;
    case ::kVK_Command:       // 55 : 0x37
      return ::kVK_Command;
    case ::kVK_Shift:         // 56 : 0x38
      return ::kVK_Shift;
    case ::kVK_CapsLock:      // 57 : 0x39
      return ::kVK_CapsLock;
    case ::kVK_Option:        // 58 : 0x3A
      return ::kVK_Option;
    case ::kVK_Control:       // 59 : 0x3B
      return ::kVK_Control;
    case ::kVK_RightShift:    // 60 : 0x3C
      return ::kVK_Shift;
    case ::kVK_RightOption:   // 61 : 0x3D
      return ::kVK_Option;
    case ::kVK_RightControl:  // 62 : 0x3E
      return ::kVK_Control;
    case ::kVK_Function:      // 63 : 0x3F
      return ::kVK_Function;
    default:
      return VKCode;
  }
}

} // namespace NSMacOS
} // namespace NSKeyboard
} // namespace NSApplication
