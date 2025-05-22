#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <spdlog/spdlog.h>
#include <QQuickStyle>
#include "SensorModel.h"

int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);
    
    // Quick Controls 2 style
    QQuickStyle::setStyle("Basic");
    
    // Initialize logging
    spdlog::set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%^%l%$] %v");
    spdlog::set_level(spdlog::level::debug);
    
    // Create and register the sensor model
    SensorModel sensorModel;
    
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("sensorModel", &sensorModel);
    
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(
        &engine, &QQmlApplicationEngine::objectCreated,
        &app, [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);
    
    engine.load(url);
    return app.exec();
} 