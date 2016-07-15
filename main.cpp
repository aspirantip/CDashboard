#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "reader.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    QObject* root = engine.rootObjects()[0];
    Reader* reader = new Reader( root );

    return app.exec();
}
