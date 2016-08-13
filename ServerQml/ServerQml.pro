TEMPLATE = app

QT += qml quick
QT += core network

CONFIG += c++11
CONFIG += console

TEMPLATE = app

SOURCES += main.cpp \
    server.cpp \
    ship.cpp \
    randomvaluegenerator.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    server.h \
    ship.h \
    randomvaluegenerator.h
