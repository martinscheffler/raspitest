#ifndef TEMPSENSOR_H
#define TEMPSENSOR_H
#include <QObject>
#include <QTimer>

class TempSensor : public QObject
{
    Q_OBJECT

public:
    TempSensor(QObject* parent);
    virtual ~TempSensor();

signals:
    void temperatureChanged(float temp);

public slots:
    void update();

private:    
    QTimer* timer;
};

#endif // TEMPSENSOR_H
