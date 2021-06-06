#ifndef NSAPPLICATION_NSKEYBOARD_CKEYBOARDLISTENERMACOS_H
#define NSAPPLICATION_NSKEYBOARD_CKEYBOARDLISTENERMACOS_H

#include "KeyTextMaker.h"
#include "MacOSKeyboardAPI.h"
#include "ShifterInfo.h"

#include <CoreFoundation/CoreFoundation.h>
#include <CoreGraphics/CoreGraphics.h>

#include <QObject>

namespace NSApplication {
namespace NSKeyboard {

struct CKeyPressing;
struct CKeyReleasing;

class CKeyboardHandler;

namespace NSMacOS {

class CKeyboardListenerMacImpl : public QObject {
  Q_OBJECT

  using CVKCode = CMacOSKeyboardAPI::CVKCode;
  using CEventTapPtr = CMacOSKeyboardAPI::CEventTapPtr;

public:
  CKeyboardListenerMacImpl(CKeyboardHandler*);
  ~CKeyboardListenerMacImpl();

signals:
  void KeyPressing(const CKeyPressing&);
  void KeyReleasing(const CKeyReleasing&);

private:
  CFMachPortRef createEventTap();
  void addEventTapToRunLoop();
  static CGEventRef callbackEventTap(CGEventTapProxy, CGEventType, CGEventRef, void*);
  static CKeyboardListenerMacImpl* getListener(void*);

  CEventTapPtr EventTap_;
  CShifterInfo ShifterInfo_;
  CKeyTextMaker KeyTextMaker_;
};

} // namespace NSMacOS
} // namespace NSKeyboard
} // namespace NSApplication

#endif // NSAPPLICATION_NSKEYBOARD_CKEYBOARDLISTENERMACOS_H
