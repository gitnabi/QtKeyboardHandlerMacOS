#include "other_things/TimerAccess.h"
#include "other_things/KeyboardHandler.h"
#include "KeyIDMacOS.h"
#include "KeyPositionMacOS.h"

namespace NSApplication {
namespace NSKeyboard {
namespace NSMacOS {

// ########################## CKeyboardListenerMacImpl
CKeyboardListenerMacImpl::CKeyboardListenerMacImpl(
    CAnyKillerPromise KillerPromise, CKeyboardHandler* KeyboardHandler)
          : EventTap_(createEventTap()), MessagePort_(createMessagePort()) {
  Q_ASSERT(::CGEventTapIsEnabled(EventTap_.get()));
  addEventTapToRunLoop();

  Q_ASSERT(::CFMessagePortIsValid(MessagePort_.get()));
  addMessagePortToRunLoop();

  KillerPromise.set_value(CKiller(MessagePort_.get()));

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
    throw std::runtime_error("Failed to create RunLoopSource for EventTap");
  }

  CMacOSKeyboardAPI::addSourceRunLoopТoCurrentRunLoop(RunLoopSource.get());
}

// ########################## callbackEventTap
CGEventRef CKeyboardListenerMacImpl::callbackEventTap(
                                  [[maybe_unused]]CGEventTapProxy   _,
                                  CGEventType                       Type,
                                  CGEventRef                        Event,
                                  void*                             UserInfo) {
  CTimerAccess Timer;
  auto Time = Timer->get();

  Q_ASSERT(UserInfo != NULL);
  CKeyboardListenerMacImpl* Listener = getListener(UserInfo);

  CVKCode VKCode = CMacOSKeyboardAPI::getVKCode(Event);
  if (CMacOSKeyboardAPI::isCapsLock(VKCode)) {
    emit Listener->KeyPressing(
          { Time,
            CKeyPositionMacOS::make(VKCode),
            CKeyIDMacOS::make(VKCode),
            getKeyLabel(VKCode),
            Listener->KeyTextMaker_.get(VKCode) });
    emit Listener->KeyReleasing(
          { Time,
            CKeyPositionMacOS::make(VKCode),
            CKeyIDMacOS::make(VKCode) } );
    return Event;
  }

  if (CMacOSKeyboardAPI::isPressing(Type, Listener->ShifterInfo_, VKCode)) {
    emit Listener->KeyPressing(
          { Time,
            CKeyPositionMacOS::make(VKCode),
            CKeyIDMacOS::make(VKCode),
            getKeyLabel(VKCode),
            Listener->KeyTextMaker_.get(VKCode) });
  } else {
    emit Listener->KeyReleasing(
          { Time,
            CKeyPositionMacOS::make(VKCode),
            CKeyIDMacOS::make(VKCode) } );
  }
  return Event;
}


// ########################## createMessagePort
CFMessagePortRef CKeyboardListenerMacImpl::createMessagePort() {
  CFMessagePortRef MessagePort = CMacOSKeyboardAPI::createMessagePort(callbackMessagePort);
  if (MessagePort == NULL) {
    throw std::runtime_error("Failed to create MessagePort");
  }
  return MessagePort;
}

// ########################## addMessagePortToRunLoop
void CKeyboardListenerMacImpl::addMessagePortToRunLoop() {
  CMacOSKeyboardAPI::UniquePtr<CFRunLoopSourceRef> RunLoopSource(
                        CMacOSKeyboardAPI::createRunLoopSourceForMessagePort(MessagePort_.get()));
  if (RunLoopSource.get() == NULL) {
    throw std::runtime_error("Failed to create RunLoopSource for MessagePort");
  }

  CMacOSKeyboardAPI::addSourceRunLoopТoCurrentRunLoop(RunLoopSource.get());
}

// ########################## callbackMessagePort
CFDataRef
CKeyboardListenerMacImpl::callbackMessagePort(CFMessagePortRef, SInt32, CFDataRef, void*) {
  CMacOSKeyboardAPI::stopCurrentRunLoop();
  return NULL;
}

// ########################## getKeyLabel
QChar CKeyboardListenerMacImpl::getKeyLabel(CVKCode VKCode) {
  QString KeyLabel = CMacOSKeyboardAPI::getKeyLabel(VKCode);
  if (KeyLabel.size() > 0 && KeyLabel.front().isPrint()) {
    return KeyLabel.front();
  }
  return QChar(0);
}

// ########################## getListener
CKeyboardListenerMacImpl* CKeyboardListenerMacImpl::getListener(void* ListenerInfo) {
  return static_cast<CKeyboardListenerMacImpl*>(ListenerInfo);
}


//#####################################
/*              CKiller              */
//#####################################

CKiller::CKiller(CFMessagePortRef KillerPort) : KillerPort_(KillerPort) {}
void CKiller::stopListener() const {
  if (CMacOSKeyboardAPI::sendEmptyMessage(KillerPort_) != kCFMessagePortSuccess) {
    throw std::runtime_error("Failed to send message via CKiller");
  }
}


} // namespace NSMacOS
} // namespace NSKeyboard
} // namespace NSApplication
