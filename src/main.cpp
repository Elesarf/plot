#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <vm.h>

int main(int argc, char** argv)
{
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    qmlRegisterType<vm>("com.ass.plot", 1, 0, "Vm");

    engine.load(QUrl("qrc:/main.qml"));

    QObject::connect(&engine, &QQmlApplicationEngine::quit, &app, &QGuiApplication::quit);
    return app.exec();
}
