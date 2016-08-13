#include <QApplication>
#include <QQmlApplicationEngine>
//#include <QtDeclarative>
#include <QQmlContext>
#include <QtQuickWidgets/QQuickWidget>
#include "appcore.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    //qmlRegisterType<Ship>("Ship",1,0,"Ship");

    QQmlApplicationEngine engine;

    AppCore appCore;
    QQmlContext *context = engine.rootContext();
    context->setContextProperty("appCore", &appCore);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
