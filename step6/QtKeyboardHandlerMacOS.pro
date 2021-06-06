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
    KeyboardListenerMacOS.cpp \
    MacOSKeyboardAPI.cpp \
    ShifterInfo.cpp \
    main.cpp \
    MainWindow.cpp \
    other_things/TimeApp.cpp \
    other_things/Timer.cpp \
    other_things/KeyboardHandler.cpp

HEADERS += \
    KeyIDMacOS.h \
    KeyPositionMacOS.h \
    KeyTextMaker.h \
    KeyboardListenerMacOS.h \
    MacOSKeyboardAPI.h \
    MainWindow.h \
    ShifterInfo.h \
    other_things/AnyGlobalAccess.h \
    other_things/TimeApp.h \
    other_things/Timer.h \
    other_things/TimerAccess.h \
    other_things/KeyID.h \
    other_things/KeyPosition.h \
    other_things/KeyboardHandler.h \
    other_things/RawKeyEvent.h \
    other_things/AnyMovable.h \
    other_things/AnyKeyboardKiller.h

FORMS += \
    MainWindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
