#include <QApplication>
#include <QQmlApplicationEngine>
#include "TempSensor.h"
#include "setuptouchscreen.h"


int main(int argc, char *argv[])
{
    setupTouchScreen();

    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));

    if (qEnvironmentVariableIsEmpty("QTGLESSTREAM_DISPLAY")) {
        qputenv("QT_QPA_EGLFS_PHYSICAL_WIDTH", QByteArray("213"));
        qputenv("QT_QPA_EGLFS_PHYSICAL_HEIGHT", QByteArray("120"));

        QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    }

    QApplication app(argc, argv);


    QQmlApplicationEngine engine;
    TempSensor* tempSensor = new TempSensor(&engine);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated, [=]( QObject* obj, const QUrl& url) {

        QObject::connect(tempSensor, &TempSensor::temperatureChanged, [=](float val) {
            obj->setProperty("temperatureSensor", QString::number(val));
        });
        qDebug("Connected sensor value output to main window property 'temperatureSensor'!");
    } );

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    engine.load(url);

    return app.exec();
}
