#-------------------------------------------------
#
# Project created by QtCreator 2016-08-03T07:40:38
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ViewShipsWidget
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    ship.cpp \
    way.cpp

HEADERS  += mainwindow.h \
    ship.h \
    way.h

FORMS    += mainwindow.ui
win32-msvc*{
    LIBS += -luser32
}

RESOURCES += \
    res.qrc
