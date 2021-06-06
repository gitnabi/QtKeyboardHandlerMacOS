#include "KeyTextMaker.h"

namespace NSApplication {
namespace NSKeyboard {
namespace NSMacOS {

QString CKeyTextMaker::get(const CVKCode VKCode) {
  if (CMacOSKeyboardAPI::isShifter(VKCode)) { return ""; }

  CInputSourcePtr CurrentKeyboardLayoutInputSource(
      CMacOSKeyboardAPI::copyCurrentKeyboardLayoutInputSource());
  if (!CurrentKeyboardLayoutInputSource.get()) {
    Q_ASSERT(false && "Unknown keyboard!");
  }

  if (CMacOSKeyboardAPI::isEqual(CurrentKeyboardLayoutInputSource.get(),
                                 KeyboardLayoutInputSource_.get())       == false) {
    DeadKeyState_ = 0;
  }
  KeyboardLayoutInputSource_ = std::move(CurrentKeyboardLayoutInputSource);

  const UCKeyboardLayout* KeyboardLayout =
      CMacOSKeyboardAPI::getCurrentKeyboardLayout(KeyboardLayoutInputSource_.get());
  if (KeyboardLayout == NULL) {
    Q_ASSERT(false && "Unknown keyboard layout!");
  }

  UniCharCount ActualStringLength = CMacOSKeyboardAPI::getUnicodeString(
                                                          KeyboardLayout,
                                                          VKCode,
                                                          &DeadKeyState_,
                                                          Text_);
  return getPrintableText(QString::fromUtf16(Text_, ActualStringLength));
}

QString CKeyTextMaker::getPrintableText(QString&& Text) const {
  if (Text.size() == 0 || CMacOSKeyboardAPI::getShifterState(::kVK_Command)) {
    return "";
  }
  if (Text.back().isPrint()) {
    return std::move(Text);
  }
  Text.resize(Text.size() - 1);
  return std::move(Text);
}

} // namespace NSMacOS
} // namespace NSKeyboard
} // namespace NSApplication
