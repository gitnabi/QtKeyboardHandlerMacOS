#include "KeyboardHandler.h"

namespace NSApplication {
namespace NSKeyboard {


CKeyboardHandler::CKeyboardHandler() {
  CAnyKillerPromise killerPromise;
  CAnyKillerFuture killerFuture = killerPromise.get_future();
  Listener_ = std::make_unique<NSMacOS::CKeyboardListenerMacImpl>(std::move(killerPromise), this);
}

void CKeyboardHandler::onKeyPressing(const CKeyPressing& KeyPressing) {
  qDebug() << "KeyID =" << KeyPressing.KeyID
           << "KeyPos =" << KeyPressing.KeyPosition
           << "symb =" << KeyPressing.KeyText << "lbl =" << KeyPressing.KeyLabel
           << "time =" << KeyPressing.PressingTime.toMilliSecondsF() << "ms";
}

void CKeyboardHandler::onKeyReleasing(const CKeyReleasing& KeyReleasing) {
  qDebug() << "KeyID =" << KeyReleasing.KeyID
           << "KeyPos =" << KeyReleasing.KeyPosition
           << "time =" << KeyReleasing.ReleasingTime.toMilliSecondsF() << "ms";
}

} // namespace NSKeyboard
} // namespace NSApplication
