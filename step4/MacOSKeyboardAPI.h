#ifndef NSAPPLICATION_NSKEYBOARD_NSWINDOWS_CMACOSKEYBOARDAPI_H
#define NSAPPLICATION_NSKEYBOARD_NSWINDOWS_CMACOSKEYBOARDAPI_H

#include <CoreGraphics/CoreGraphics.h>
#include <Carbon/Carbon.h>

#include <QString>

#include <memory>

namespace NSApplication {
namespace NSKeyboard {
namespace NSMacOS {

class CKeyboardListenerMacImpl;
class CShifterInfo;

class CMacOSKeyboardAPI {
public:
//                                *** UniquePtr ***
// ----------------------------------------------------------------------------
  // https://fossies.org/linux/misc/llvm-12.0.0.src.tar.xz/llvm-12.0.0.src/tools/dsymutil/CFBundle.cpp
  template<typename T> struct CFDeleter {
    void operator()(T* ptr) {
      if (ptr) { ::CFRelease(ptr); }
    }
  };

  template<typename T>
  using UniquePtr = std::unique_ptr<std::remove_pointer_t<T>, CFDeleter<std::remove_pointer_t<T>>>;
// ----------------------------------------------------------------------------
  using CVKCode = int64_t;
  using CEventTapPtr = UniquePtr<CFMachPortRef>;

  static CFMachPortRef createEventTapForKeyboard(CGEventTapCallBack, CKeyboardListenerMacImpl*);
  static CFRunLoopSourceRef createRunLoopSourceForEventTap(CFMachPortRef);
  static CFRunLoopRef getCurrentRunLoop();
  static void addSourceRunLoop(CFRunLoopRef, CFRunLoopSourceRef);

  static TISInputSourceRef copyCurrentKeyboardLayoutInputSource();
  static const UCKeyboardLayout* getCurrentKeyboardLayout(TISInputSourceRef);
  static UniCharCount getUnicodeString(const UCKeyboardLayout*, CVKCode, UInt32*, UniChar[]);

  static CVKCode getVKCode(CGEventRef);
  static CGEventTimestamp getEventTimestamp(CGEventRef);
  static bool getShifterState(CVKCode VKCode);

  static bool isPressing(CGEventType, CShifterInfo&, CVKCode);
  static bool isEqual(CFTypeRef, CFTypeRef);

  static QString getLabel(const CVKCode);
  static QString getName(const CVKCode);

  static constexpr UniCharCount kMaxStringLength = 0xFF; // 255
};

} // namespace NSMacOS
} // namespace NSKeyboard
} // namespace NSApplication

#endif // NSAPPLICATION_NSKEYBOARD_NSWINDOWS_CMACOSKEYBOARDAPI_H
