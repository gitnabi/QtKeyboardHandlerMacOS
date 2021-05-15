#include "MainWindow.h"

#include <QApplication>
#include "KeyboardListenerMacOS.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    CKeyboardListenerMacImpl listener;
    return a.exec();
}
