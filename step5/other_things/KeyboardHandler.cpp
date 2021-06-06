#include "KeyboardHandler.h"

namespace NSApplication {
namespace NSKeyboard {


CKeyboardHandler::CKeyboardHandler() : Listener_(this) {}

void CKeyboardHandler::onKeyPressing(const CKeyPressing& KeyPressing) {
  qDebug() << "KeyID =" << KeyPressing.KeyID
           << "KeyPos =" << KeyPressing.KeyPosition
           << "symb =" << KeyPressing.KeyText << "lbl =" << KeyPressing.KeyLabel
           << "time =" << KeyPressing.PressingTime.toMilliSecondsF() << "ms";
//    qDebug() << "KeyDown: \tKeyCode =" << KeyPressing.KeyCode
//            << "\ttime =" << KeyPressing.PressingTime.toMilliSecondsF() << "ms"
//            << "\tKeyText =" << KeyPressing.KeyText
//            << "\tKeyLabel =" << KeyPressing.KeyLabel;
//  qDebug().noquote() << KeyPressing.KeyText;
}

void CKeyboardHandler::onKeyReleasing(const CKeyReleasing& KeyReleasing) {
  qDebug() << "KeyID =" << KeyReleasing.KeyID
           << "KeyPos =" << KeyReleasing.KeyPosition
           << "time =" << KeyReleasing.ReleasingTime.toMilliSecondsF() << "ms";
//    qDebug() << "KeyUp:   \tKeyCode =" << KeyReleasing.KeyCode
//            << "\ttime =" << KeyReleasing.ReleasingTime.toMilliSecondsF() << "ms";
}

} // namespace NSKeyboard
} // namespace NSApplication
