#include "KeyboardListenerMacOS.h"

CGEventRef CKeyboardListenerMacImpl::callbackEventTap(
                                    [[maybe_unused]]CGEventTapProxy  proxy,
                                    CGEventType type,
                                    CGEventRef  event,
                                    [[maybe_unused]]void * userInfo) {
    int64_t keyCode = CGEventGetIntegerValueField(event, kCGKeyboardEventKeycode);
    if (type == kCGEventKeyDown) {
        std::cout << "KeyDown, keyCode:\t" << keyCode << "\n";
    } else if (type == kCGEventKeyUp) {
        std::cout << "KeyUp, keyCode:\t" << keyCode << "\n";
    } else if (type == kCGEventFlagsChanged) {
        if (CGEventSourceKeyState(kCGEventSourceStateCombinedSessionState, keyCode)) {
            std::cout << "FlagsChanged(KeyDown), keyCode:\t" << keyCode << "\n";;
        } else {
            std::cout << "FlagsChanged(KeyUp), keyCode:\t" << keyCode << "\n";;
        }
    } else {
        assert(false && "Unknown key type.");
    }
    return event;
}

CFMachPortRef
CKeyboardListenerMacImpl::makeEventTap() {
    CFMachPortRef EventTap = CGEventTapCreate(
                                kCGHIDEventTap,
                                kCGHeadInsertEventTap,
                                kCGEventTapOptionListenOnly,
                                CGEventMaskBit(kCGEventKeyDown) |
                                CGEventMaskBit(kCGEventKeyUp) |
                                CGEventMaskBit(kCGEventFlagsChanged),
                                callbackEventTap,
                                NULL);
    if (EventTap == NULL) {
        throw std::runtime_error("Failed to create EventTap");
    }
    return EventTap;
}

void
CKeyboardListenerMacImpl::addMachPortToRunLoop(CFMachPortRef EventTap) {
    UniquePtr<CFRunLoopSourceRef> RunLoopSource(
            CFMachPortCreateRunLoopSource(kCFAllocatorDefault, EventTap, 0));
    if (RunLoopSource.get() == NULL) {
        throw std::runtime_error("Failed to create RunLoop");
    }

    CFRunLoopRef RunLoop = CFRunLoopGetCurrent();
    if (RunLoop == NULL) {
        throw std::runtime_error("No CFRunLoop object for the current thread!");
    }
    CFRunLoopAddSource(RunLoop, RunLoopSource.get(), kCFRunLoopCommonModes);
}

CKeyboardListenerMacImpl::CKeyboardListenerMacImpl() :
            EventTap_(makeEventTap()) {
    assert(CGEventTapIsEnabled(EventTap_.get()));
    addMachPortToRunLoop(EventTap_.get());
}
