# Created by and for Qt Creator This file was created for editing the project sources only.
# You may attempt to use it for building too, by modifying this file here.


TEMPLATE = app
TARGET = eprak
QT += widgets
QT -=gui declarative
DEPENDPATH += .
INCLUDEPATH += .

CONFIG += c++14

# Input
HEADERS += about.h \
           codeeditor.h \
           functions.h \
           mainwindow.h
FORMS += about.ui \
    mainwindow.ui
SOURCES += about.cpp \
           codeeditor.cpp \
           main.cpp \
           mainwindow.cpp
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../EwmTesting/release/ -lEwmTesting
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../EwmTesting/debug/ -lEwmTesting
macx: LIBS += -L$$OUT_PWD/../EwmTesting/ -lEwmTesting.1.0.0
unix: LIBS += -L$$OUT_PWD/../EwmTesting/ -lEwmTesting

INCLUDEPATH += $$PWD/../EwmTesting
DEPENDPATH += $$PWD/../EwmTesting

RESOURCES += \
    res.qrc
ICON = icons8-next-96.icns
