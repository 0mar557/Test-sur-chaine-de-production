#-------------------------------------------------
#
# Project created by QtCreator 2025-02-07T11:34:54
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = projet_ajo
TEMPLATE = app
QT += core gui serialport sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += c++11

LIBS += -L"C:\Program Files (x86)\IVI Foundation\VISA\WinNT\lib\msc" -lvisa32
LIBS += -L"C:\Qt\Qt5.11.1\5.11.1\mingw53_32\lib"

INCLUDEPATH += "C:\Program Files (x86)\IVI Foundation\VISA\WinNT\Include"
# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    dialoglogin.cpp \
    dialogtech.cpp

HEADERS += \
        mainwindow.h \
    dialoglogin.h \
    dialogtech.h

FORMS += \
        mainwindow.ui \
    dialoglogin.ui \
    dialogtech.ui
