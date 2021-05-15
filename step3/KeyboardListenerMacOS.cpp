#include "KeyboardHandler.h"

namespace NSApplication {
namespace NSKeyboard {

CKeyboardListenerMacImpl::CKeyboardListenerMacImpl(CKeyboardHandler* KeyboardHandler) :
        EventTap_(makeEventTap(this)) {
  assert(::CGEventTapIsEnabled(EventTap_.get()));
  addMachPortToRunLoop(EventTap_.get());

  connect(this, &CKeyboardListenerMacImpl::KeyPressing,
          KeyboardHandler, &CKeyboardHandler::onKeyPressing);
  connect(this, &CKeyboardListenerMacImpl::KeyReleasing,
          KeyboardHandler, &CKeyboardHandler::onKeyReleasing);
}

CKeyboardListenerMacImpl::~CKeyboardListenerMacImpl() {
  disconnect(this, &CKeyboardListenerMacImpl::KeyPressing, nullptr, nullptr);
  disconnect(this, &CKeyboardListenerMacImpl::KeyReleasing, nullptr, nullptr);
}

CFMachPortRef
CKeyboardListenerMacImpl::makeEventTap(CKeyboardListenerMacImpl* KeyboardListener) {
    CFMachPortRef EventTap = ::CGEventTapCreate(
                                kCGHIDEventTap,
                                kCGHeadInsertEventTap,
                                kCGEventTapOptionListenOnly,
                                CGEventMaskBit(kCGEventKeyDown) |
                                CGEventMaskBit(kCGEventKeyUp) |
                                CGEventMaskBit(kCGEventFlagsChanged),
                                callbackEventTap,
                                KeyboardListener);
  if (EventTap == NULL) {
    throw std::runtime_error("Failed to create EventTap");
  }
  return EventTap;
}

CGEventRef CKeyboardListenerMacImpl::callbackEventTap(
                                    [[maybe_unused]]CGEventTapProxy  proxy,
                                    CGEventType type,
                                    CGEventRef  event,
                                    void * userInfo) {
  int64_t KeyCode = ::CGEventGetIntegerValueField(event, kCGKeyboardEventKeycode);
  CKeyboardListenerMacImpl* Listener = getListener(userInfo);
  if (type == kCGEventKeyDown) {
    emit Listener->KeyPressing(
                                {
                                    ::CGEventGetTimestamp(event),
                                    KeyCode,
                                    getKeyText(event),
                                }
                              );
  } else if (type == kCGEventKeyUp) {
    emit Listener->KeyReleasing(
                                {
                                    ::CGEventGetTimestamp(event),
                                    KeyCode,
                                }
                              );
  } else if (type == kCGEventFlagsChanged) {
    if (::CGEventSourceKeyState(kCGEventSourceStateCombinedSessionState, KeyCode)) {
      emit Listener->KeyPressing(
                                  {
                                      ::CGEventGetTimestamp(event),
                                      KeyCode,
                                      getKeyText(event),
                                  }
                                );
    } else {
      emit Listener->KeyReleasing(
                                  {
                                      ::CGEventGetTimestamp(event),
                                      KeyCode,
                                  }
                                );
    }
  } else {
    assert(false && "Unknown key type.");
  }
  return event;
}

QString CKeyboardListenerMacImpl::getKeyText(const CGEventRef event) {
  UniCharCount strLength = 10;
  UniChar str[strLength];
  ::CGEventKeyboardGetUnicodeString(event, strLength, &strLength, str);
  return QString::fromUtf16(str, strLength);
}

CKeyboardListenerMacImpl* CKeyboardListenerMacImpl::getListener(void* data) {
  return static_cast<CKeyboardListenerMacImpl*>(data);
}


void
CKeyboardListenerMacImpl::addMachPortToRunLoop(const CFMachPortRef EventTap) {
  UniquePtr<CFRunLoopSourceRef> RunLoopSource(
                      ::CFMachPortCreateRunLoopSource(kCFAllocatorDefault, EventTap, 0));
  if (RunLoopSource.get() == NULL) {
    throw std::runtime_error("Failed to create RunLoop");
  }

  CFRunLoopRef RunLoop = ::CFRunLoopGetCurrent();
  if (RunLoop == NULL) {
    throw std::runtime_error("No CFRunLoop object for the current thread!");
  }
  ::CFRunLoopAddSource(RunLoop, RunLoopSource.get(), kCFRunLoopCommonModes);
}


} // namespace NSKeyboard
} // namespace NSApplication
