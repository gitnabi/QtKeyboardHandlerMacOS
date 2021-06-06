#ifndef NSAPPLICATION_NSKEYBOARD_NSMACOS_SHIFTERINFO_H
#define NSAPPLICATION_NSKEYBOARD_NSMACOS_SHIFTERINFO_H

#include "MacOSKeyboardAPI.h"

#include <Carbon/Carbon.h>

#include <unordered_map>
#include <vector>

namespace NSApplication {
namespace NSKeyboard {
namespace NSMacOS {

class CShifterInfo {
  using CVKCode = CMacOSKeyboardAPI::CVKCode;
  using CShifterState = std::unordered_map<CVKCode, bool>;
  using CAllShifters = std::vector<CVKCode>;

public:
  CShifterInfo();

  void changeFlag(CVKCode);
  bool getState(CVKCode) const;

private:
  CVKCode toBasicShifter(CVKCode) const;

  CAllShifters AllShifters_{
    ::kVK_RightCommand,
    ::kVK_Command,
    ::kVK_Shift,
    ::kVK_CapsLock,
    ::kVK_Option,
    ::kVK_Control,
    ::kVK_RightShift,
    ::kVK_RightOption,
    ::kVK_RightControl,
    ::kVK_Function,
  };

  CShifterState ShifterState_;
};
} // namespace NSMacOS
} // namespace NSKeyboard
} // namespace NSApplication

#endif // NSAPPLICATION_NSKEYBOARD_NSMACOS_SHIFTERINFO_H
