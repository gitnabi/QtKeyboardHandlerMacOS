#include "MainWindow.h"

#include "other_things/TimerAccess.h"
#include "other_things/KeyboardHandler.h"

#include <QApplication>


int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  MainWindow w;
  w.show();
  NSApplication::CTimerInit MainTimer;
  NSApplication::NSKeyboard::CKeyboardHandler Handler;
  return a.exec();
}
