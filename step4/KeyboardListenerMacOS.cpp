#include "KeyboardHandler.h"
#include "KeyIDMacOS.h"
#include "KeyPositionMacOS.h"

namespace NSApplication {
namespace NSKeyboard {
namespace NSMacOS {

// ########################## CKeyboardListenerMacImpl
CKeyboardListenerMacImpl::CKeyboardListenerMacImpl(CKeyboardHandler* KeyboardHandler) :
        EventTap_(createEventTap()) {
  Q_ASSERT(::CGEventTapIsEnabled(EventTap_.get()));
  addEventTapToRunLoop();

  connect(this,             &CKeyboardListenerMacImpl::KeyPressing,
          KeyboardHandler,  &CKeyboardHandler::onKeyPressing);
  connect(this,             &CKeyboardListenerMacImpl::KeyReleasing,
          KeyboardHandler,  &CKeyboardHandler::onKeyReleasing);
}

// ########################## ~CKeyboardListenerMacImpl
CKeyboardListenerMacImpl::~CKeyboardListenerMacImpl() {
  disconnect(this, &CKeyboardListenerMacImpl::KeyPressing,  nullptr, nullptr);
  disconnect(this, &CKeyboardListenerMacImpl::KeyReleasing, nullptr, nullptr);
}


// ########################## createEventTap
CFMachPortRef CKeyboardListenerMacImpl::createEventTap() {
  CFMachPortRef EventTap =
          CMacOSKeyboardAPI::createEventTapForKeyboard(callbackEventTap, this);
  if (EventTap == NULL) {
    throw std::runtime_error("Failed to create EventTap");
  }
  return EventTap;
}

// ########################## addEventTapToRunLoop
void CKeyboardListenerMacImpl::addEventTapToRunLoop() {
  CMacOSKeyboardAPI::UniquePtr<CFRunLoopSourceRef> RunLoopSource(
                        CMacOSKeyboardAPI::createRunLoopSourceForEventTap(EventTap_.get()));
  if (RunLoopSource.get() == NULL) {
    throw std::runtime_error("Failed to create RunLoop");
  }

  CFRunLoopRef RunLoop = CMacOSKeyboardAPI::getCurrentRunLoop();
  if (RunLoop == NULL) {
    throw std::runtime_error("No CFRunLoop object for the current thread!");
  }
  CMacOSKeyboardAPI::addSourceRunLoop(RunLoop, RunLoopSource.get());
}

// ########################## callbackEventTap
CGEventRef CKeyboardListenerMacImpl::callbackEventTap(
                                  [[maybe_unused]]CGEventTapProxy   _,
                                  CGEventType                       Type,
                                  CGEventRef                        Event,
                                  void*                             UserInfo) {
  Q_ASSERT(UserInfo != NULL);
  CKeyboardListenerMacImpl* Listener = getListener(UserInfo);

  CVKCode VKCode = CMacOSKeyboardAPI::getVKCode(Event);
  if (CMacOSKeyboardAPI::isCapsLock(VKCode)) {
    emit Listener->KeyPressing(
          { CMacOSKeyboardAPI::getEventTimestamp(Event),
            CKeyPositionMacOS::make(VKCode),
            CKeyIDMacOS::make(VKCode),
            CMacOSKeyboardAPI::getKeyLabel(VKCode),
            Listener->KeyTextMaker_.get(VKCode) });
    emit Listener->KeyReleasing(
          { CMacOSKeyboardAPI::getEventTimestamp(Event),
            CKeyPositionMacOS::make(VKCode),
            CKeyIDMacOS::make(VKCode), } );
    return Event;
  }

  if (CMacOSKeyboardAPI::isPressing(Type, Listener->ShifterInfo_, VKCode)) {
    emit Listener->KeyPressing(
          { CMacOSKeyboardAPI::getEventTimestamp(Event),
            CKeyPositionMacOS::make(VKCode),
            CKeyIDMacOS::make(VKCode),
            CMacOSKeyboardAPI::getKeyLabel(VKCode),
            Listener->KeyTextMaker_.get(VKCode) });
  } else {
    emit Listener->KeyReleasing(
          { CMacOSKeyboardAPI::getEventTimestamp(Event),
            CKeyPositionMacOS::make(VKCode),
            CKeyIDMacOS::make(VKCode), } );
  }
  return Event;
}

// ########################## getListener
CKeyboardListenerMacImpl* CKeyboardListenerMacImpl::getListener(void* ListenerInfo) {
  return static_cast<CKeyboardListenerMacImpl*>(ListenerInfo);
}

} // namespace NSMacOS
} // namespace NSKeyboard
} // namespace NSApplication
