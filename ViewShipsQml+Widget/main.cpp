#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "gamearea.h"
int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    qmlRegisterType<GameArea>("GameArea", 1, 0, "GameArea");
    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
