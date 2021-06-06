#ifndef NSAPPLICATION_NSKEYBOARD_CKEYBOARDLISTENERMACOS_H
#define NSAPPLICATION_NSKEYBOARD_CKEYBOARDLISTENERMACOS_H

#include "KeyTextMaker.h"
#include "MacOSKeyboardAPI.h"
#include "ShifterInfo.h"

#include <CoreFoundation/CoreFoundation.h>
#include <CoreGraphics/CoreGraphics.h>

#include <QObject>

#include <future>

namespace NSApplication {
namespace NSKeyboard {

struct CKeyPressing;
struct CKeyReleasing;

class CKeyboardHandler;

namespace NSMacOS {

class CKeyboardListenerMacImpl : public QObject {
  Q_OBJECT

  using CVKCode = CMacOSKeyboardAPI::CVKCode;
  using CEventTapUPtr = CMacOSKeyboardAPI::CEventTapUPtr;

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
  static QChar getKeyLabel(CVKCode);
  static CKeyboardListenerMacImpl* getListener(void*);

  CEventTapUPtr EventTap_;
  CShifterInfo ShifterInfo_;
  CKeyTextMaker KeyTextMaker_;
};

} // namespace NSMacOS
} // namespace NSKeyboard
} // namespace NSApplication

#endif // NSAPPLICATION_NSKEYBOARD_CKEYBOARDLISTENERMACOS_H
