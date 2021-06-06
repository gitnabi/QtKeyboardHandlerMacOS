#include "KeyboardHandler.h"

namespace NSApplication {
namespace NSKeyboard {

CKeyboardHandler::CKeyboardHandler() : Listener_(this) {}

void CKeyboardHandler::onKeyPressing(const CKeyPressing& KeyPressing) {
    qDebug()  << "KeyDown: \tKeyID =" << KeyPressing.KeyID
              << "  \tKeyPos =" << KeyPressing.KeyPosition
              << " \ttime =" << KeyPressing.PressingTime << "ns"
              << "KeyLabel =" << KeyPressing.KeyLabel
              << "KeyText =" << KeyPressing.KeyText;
//  qDebug().noquote() << KeyPressing.KeyText;
}

void CKeyboardHandler::onKeyReleasing(const CKeyReleasing& KeyReleasing) {
  qDebug()  << "KeyUp: \tKeyID =" << KeyReleasing.KeyID
            << "   \tKeyPos =" << KeyReleasing.KeyPosition
            << " \ttime =" << KeyReleasing.ReleasingTime << "ns";
}

} // namespace NSKeyboard
} // namespace NSApplication
