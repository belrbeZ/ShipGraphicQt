#include <QApplication>
#include <QQmlApplicationEngine>
#include "ship.h"
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;
    qmlRegisterType<Ship>("Ship",1,0,"Ship");
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
