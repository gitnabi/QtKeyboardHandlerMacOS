#ifndef NSAPPLICATION_NSKEYBOARD_NSMACOS_CKEYTEXTMAKER_H
#define NSAPPLICATION_NSKEYBOARD_NSMACOS_CKEYTEXTMAKER_H

#include "MacOSKeyboardAPI.h"

namespace NSApplication {
namespace NSKeyboard {
namespace NSMacOS {

class CKeyTextMaker {
  using CVKCode = CMacOSKeyboardAPI::CVKCode;
  using CInputSourcePtr = CMacOSKeyboardAPI::UniquePtr<TISInputSourceRef>;

public:
  QString get(const CVKCode);

private:
  QString getPrintableText(QString&&) const;

  UInt32 DeadKeyState_ = 0;
  CInputSourcePtr KeyboardLayoutInputSource_ = nullptr;

  UniChar Text_[CMacOSKeyboardAPI::kMaxStringLength];
};

} // namespace NSMacOS
} // namespace NSKeyboard
} // namespace NSApplication

#endif // NSAPPLICATION_NSKEYBOARD_NSMACOS_CKEYTEXTMAKER_H
