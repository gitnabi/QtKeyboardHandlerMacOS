#ifndef NSAPPLICATION_NSKEYBOARD_CKEYBOARDHANDLER_H
#define NSAPPLICATION_NSKEYBOARD_CKEYBOARDHANDLER_H


#include "KeyboardListenerMacOS.h"
#include "RawKeyEvent.h"

#include <QObject>
#include <QDebug>


namespace NSApplication {
namespace NSKeyboard {

struct CKeyPressing;
struct CKeyReleasing;

class CKeyboardListenerMacImpl;

class CKeyboardHandler : public QObject {
  Q_OBJECT

  using CAnyKillerPromise = std::promise<CAnyKeyboardKiller>;
  using CAnyKillerFuture = std::future<CAnyKeyboardKiller>;
  using ListenerUPtr = std::unique_ptr<NSMacOS::CKeyboardListenerMacImpl>;

public:
  CKeyboardHandler();

public slots:
  void onKeyPressing(const CKeyPressing&);
  void onKeyReleasing(const CKeyReleasing&);

private:
  ListenerUPtr Listener_;
};

} // namespace NSKeyboard
} // namespace NSApplication

#endif // NSAPPLICATION_NSKEYBOARD_CKEYBOARDHANDLER_H
