#ifndef NSAPPLICATION_NSKEYBOARD_CRAWKEYEVENT_H
#define NSAPPLICATION_NSKEYBOARD_CRAWKEYEVENT_H

#include <QString>

#include <CoreGraphics/CoreGraphics.h>

namespace NSApplication {
namespace NSKeyboard {

struct CKeyPressing {
  CGEventTimestamp PressingTime;
  int64_t KeyCode;
  QString KeyText;
};

struct CKeyReleasing {
  CGEventTimestamp ReleasingTime;
  int64_t KeyCode;
};

} // namespace NSKeyboard
} // namespace NSApplication

#endif // NSAPPLICATION_NSKEYBOARD_CRAWKEYEVENT_H
