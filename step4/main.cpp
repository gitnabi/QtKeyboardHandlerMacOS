#include "MainWindow.h"

#include "KeyboardHandler.h"

#include <QApplication>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  MainWindow w;
  w.show();
  NSApplication::NSKeyboard::CKeyboardHandler Handler;
  return a.exec();
}
