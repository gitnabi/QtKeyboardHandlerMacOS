#include "KeyboardHandler.h"

namespace NSApplication {
namespace NSKeyboard {


CKeyboardHandler::CKeyboardHandler() : Listener_(this) {}

void CKeyboardHandler::onKeyPressing(const CKeyPressing& KeyPressing) {
    qDebug() << "KeyDown: \tKeyCode =" << KeyPressing.KeyCode
            << "\ttime =" << KeyPressing.PressingTime << "ns"
            << "\tsymb =" << KeyPressing.KeyText;
}

void CKeyboardHandler::onKeyReleasing(const CKeyReleasing& KeyReleasing) {
    qDebug() << "KeyUp:   \tKeyCode =" << KeyReleasing.KeyCode
            << "\ttime =" << KeyReleasing.ReleasingTime << "ns";
}

} // namespace NSKeyboard
} // namespace NSApplication
