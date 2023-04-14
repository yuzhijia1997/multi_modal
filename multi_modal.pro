QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    mymenu.cpp

HEADERS += \
    mainwindow.h \
    mymenu.h

FORMS += \
    mainwindow.ui

INCLUDEPATH += \
    D:\opencv\mingw\install\include
#    $$PWD\pri

#include($$PWD\pri\opencv.pri)
#include($$PWD\pri\libtorch_debug.pri)

LIBS += \
    D:\opencv\mingw\install\x64\mingw\bin\libopencv_*.dll
    D:\opencv\mingw\lib\libopencv_*.a

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=
