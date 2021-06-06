#ifndef NSAPPLICATION_NSKEYBOARD_CRAWKEYEVENT_H
#define NSAPPLICATION_NSKEYBOARD_CRAWKEYEVENT_H

#include "other_things/KeyID.h"
#include "other_things/KeyPosition.h"

#include <QString>

#include <CoreGraphics/CoreGraphics.h>
using CTime = CGEventTimestamp;

namespace NSApplication {
namespace NSKeyboard {

struct CKeyPressing {
  CTime PressingTime;
  CKeyPosition KeyPosition;
  CKeyID KeyID;
  QString KeyLabel;
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
