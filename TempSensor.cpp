#include "TempSensor.h"
#include <QTimer>
#include <iostream>
#include <QFile>
#include <QTextStream>
#include <QString>

TempSensor::TempSensor(QObject* parent)
    : QObject(parent)
{

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(1000);    
}

TempSensor::~TempSensor() {
    delete timer;
}

void TempSensor::update() {

    QFile inputFile("/sys/class/thermal/thermal_zone0/temp");
    if (inputFile.open(QIODevice::ReadOnly))
    {
        QTextStream in(&inputFile);
        QString line = in.readLine();
        int val = line.toInt();
        float tempval = ((float)val) / 1000.0f;
        emit temperatureChanged(tempval);
        inputFile.close();
    }
}
