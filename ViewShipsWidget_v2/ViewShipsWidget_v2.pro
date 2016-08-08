#-------------------------------------------------
#
# Project created by QtCreator 2016-08-05T16:34:04
#
#-------------------------------------------------

QT       += core gui
QT += core network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ViewShipsWidget_v2
CONFIG += console
CONFIG -= app_bundle
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    ship.cpp \
    way.cpp \
    randomvaluegenerator.cpp \
    client.cpp

HEADERS  += mainwindow.h \
    ship.h \
    way.h \
    randomvaluegenerator.h \
    client.h

FORMS    += mainwindow.ui
win32-msvc*{
    LIBS += -luser32
}

RESOURCES += \
    res.qrc
