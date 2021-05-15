#include "KeyboardListenerMacOS.h"

int main() {
    CKeyboardListenerMacImpl listener;
    CFRunLoopRun();
    return 0;
}