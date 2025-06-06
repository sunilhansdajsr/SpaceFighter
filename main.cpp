#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <Controller.h>
#include "class1.h"
#include "class2.h"
#include "QObject"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    Controller control;

    engine.rootContext()->setContextProperty("control", &control);

    class1 classOne;
    class2 classTwo;

    QObject::connect(&classOne, &class1::printIt, &classTwo, &class2::print);

    classOne.printIt();

    const QUrl url(QStringLiteral("qrc:/untitled3/main.qml"));
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreated,
        &app,
        [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
