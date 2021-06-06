#ifndef NSAPPLICATION_NSKEYBOARD_NSMACOS_CKEYPOSITIONMACOS_H
#define NSAPPLICATION_NSKEYBOARD_NSMACOS_CKEYPOSITIONMACOS_H

#include "MacOSKeyboardAPI.h"
#include "other_things/KeyPosition.h"

namespace NSApplication {
namespace NSKeyboard {
namespace NSMacOS {

class CKeyPositionMacOS {
  using CVKCode = CMacOSKeyboardAPI::CVKCode;

public:
  static CKeyPosition make(const CVKCode);
};

} // namespace NSMacOS
} // namespace NSKeyboard
} // namespace NSApplication

#endif // NSAPPLICATION_NSKEYBOARD_NSMACOS_CKEYPOSITIONMACOS_H
