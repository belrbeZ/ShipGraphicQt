TEMPLATE = app
QT += quick
QT += qml quick
QT += qml quickwidget
QT += core gui declarative
CONFIG += c++11

SOURCES += main.cpp \
    randomvaluegenerator.cpp \
    ship.cpp \
    gamearea.cpp \
    triangle.cpp

RESOURCES += qml.qrc \
    res.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    randomvaluegenerator.h \
    ship.h \
    gamearea.h \
    triangle.h
