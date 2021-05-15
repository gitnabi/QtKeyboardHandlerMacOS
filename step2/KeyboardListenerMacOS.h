#ifndef KEYBOARDLISTENERMACOS_H
#define KEYBOARDLISTENERMACOS_H

#include <QDebug>

#include <memory>

#include <CoreGraphics/CoreGraphics.h>
#include <CoreFoundation/CoreFoundation.h>

class CKeyboardListenerMacImpl {
    // https://fossies.org/linux/misc/llvm-12.0.0.src.tar.xz/llvm-12.0.0.src/tools/dsymutil/CFBundle.cpp
    template<typename T> struct CFDeleter {
        void operator()(T* ptr) {
            if (ptr) { ::CFRelease(ptr); }
        }
    };

    template<typename T>
    using UniquePtr = std::unique_ptr<std::remove_pointer_t<T>,
                                      CFDeleter<std::remove_pointer_t<T>>>;

    UniquePtr<CFMachPortRef> EventTap_;

public:
    CKeyboardListenerMacImpl();

private:
    static CGEventRef callbackEventTap(CGEventTapProxy, CGEventType, CGEventRef, void*);
    static CFMachPortRef makeEventTap();
    static void addMachPortToRunLoop(CFMachPortRef);
};

#endif // KEYBOARDLISTENERMACOS_H
