TEMPLATE = app

QT += qml quick
QT += qml quickwidgets
QT += quickwidgets
QT += widgets
CONFIG += c++11

SOURCES += main.cpp \
    appcore.cpp \
    ship.cpp \
    randomvaluegenerator.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    appcore.h \
    ship.h \
    randomvaluegenerator.h

DISTFILES += \
    ship.jpg
