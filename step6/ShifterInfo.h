#ifndef NSAPPLICATION_NSKEYBOARD_NSMACOS_SHIFTERINFO_H
#define NSAPPLICATION_NSKEYBOARD_NSMACOS_SHIFTERINFO_H

#include "MacOSKeyboardAPI.h"

#include <Carbon/Carbon.h>

#include <unordered_map>

namespace NSApplication {
namespace NSKeyboard {
namespace NSMacOS {

class CShifterInfo {
  using CVKCode = CMacOSKeyboardAPI::CVKCode;
  using CShifterState = std::unordered_map<CVKCode, bool>;

public:
  CShifterInfo();

  void changeFlag(const CVKCode);
  bool getState(const CVKCode) const;

private:
  CVKCode toBasicShifter(const CVKCode) const;

  CShifterState ShifterState_;
};
} // namespace NSMacOS
} // namespace NSKeyboard
} // namespace NSApplication

#endif // NSAPPLICATION_NSKEYBOARD_NSMACOS_SHIFTERINFO_H
