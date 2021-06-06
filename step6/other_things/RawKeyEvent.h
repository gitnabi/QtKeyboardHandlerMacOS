#ifndef NSAPPLICATION_NSKEYBOARD_CRAWKEYEVENT_H
#define NSAPPLICATION_NSKEYBOARD_CRAWKEYEVENT_H

#include "other_things/TimeApp.h"
#include "other_things/KeyID.h"
#include "other_things/KeyPosition.h"

#include <QString>

namespace NSApplication {
namespace NSKeyboard {

struct CKeyPressing {
  CTime PressingTime;
  CKeyPosition KeyPosition;
  CKeyID KeyID;
  QChar KeyLabel;
  QString KeyText;
};

struct CKeyReleasing {
  CTime ReleasingTime;
  CKeyPosition KeyPosition;
  CKeyID KeyID;
};

} // namespace NSKeyboard
} // namespace NSApplication

#endif // NSAPPLICATION_NSKEYBOARD_CRAWKEYEVENT_H
