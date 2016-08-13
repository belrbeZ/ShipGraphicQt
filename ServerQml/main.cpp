#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QCoreApplication>
#include <QQmlContext>
#include "server.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    Server server;
    QQmlContext *context = engine.rootContext();
    context->setContextProperty("server", &server);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));


    return app.exec();
}
