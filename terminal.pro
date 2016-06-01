#-------------------------------------------------
#
# Project created by QtCreator 2016-04-06T16:07:21
#
#-------------------------------------------------

QT       += core gui
QT += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = terminal
TEMPLATE = app


SOURCES += main.cpp\
        terminal.cpp

HEADERS  += terminal.h

FORMS    += terminal.ui

target.path += /home/root
INSTALLS += target

RESOURCES += \
    myimages.qrc \
    myimages.qrc
