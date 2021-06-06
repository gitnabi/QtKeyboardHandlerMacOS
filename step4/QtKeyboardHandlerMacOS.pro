QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += \
    c++17 \
    rtti_off \
    warn_on \
    sdk_no_version_check

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

macx{
    LIBS += -framework Carbon
    LIBS += -framework CoreFoundation
    LIBS += -framework CoreGraphics
}


SOURCES += \
    KeyIDMacOS.cpp \
    KeyPositionMacOS.cpp \
    KeyTextMaker.cpp \
    KeyboardHandler.cpp \
    KeyboardListenerMacOS.cpp \
    MacOSKeyboardAPI.cpp \
    ShifterInfo.cpp \
    main.cpp \
    MainWindow.cpp

HEADERS += \
    KeyIDMacOS.h \
    KeyPositionMacOS.h \
    other_things/AnyGlobalAccess.h \
    KeyTextMaker.h \
    KeyboardHandler.h \
    KeyboardListenerMacOS.h \
    MacOSKeyboardAPI.h \
    MainWindow.h \
    RawKeyEvent.h \
    ShifterInfo.h \
    other_things/KeyID.h \
    other_things/KeyPosition.h

FORMS += \
    MainWindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
