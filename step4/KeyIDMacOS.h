#ifndef NSAPPLICATION_NSKEYBOARD_NSMACOS_CKEYIDMACOS_H
#define NSAPPLICATION_NSKEYBOARD_NSMACOS_CKEYIDMACOS_H

#include "MacOSKeyboardAPI.h"
#include "other_things/KeyID.h"

namespace NSApplication {
namespace NSKeyboard {
namespace NSMacOS {

class CKeyIDMacOS {
  using CVKCode = CMacOSKeyboardAPI::CVKCode;

public:
  static CKeyID make(const CVKCode VKey);
};

} // namespace NSMacOS
} // namespace NSKeyboard
} // namespace NSApplication

#endif // NSAPPLICATION_NSKEYBOARD_NSMACOS_CKEYIDMACOS_H
