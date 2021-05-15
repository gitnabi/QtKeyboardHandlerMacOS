#include "MainWindow.h"

#include <QApplication>
#include "KeyboardHandler.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  MainWindow w;
  w.show();
  NSApplication::NSKeyboard::CKeyboardHandler Handler;
  return a.exec();
}
