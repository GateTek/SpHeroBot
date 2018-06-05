#ifndef SERIAL_H
#define SERIAL_H

#include <QtSerialPort/QSerialPort>
#include <windows.h>


class Serial {
public:
    Serial(QString port);
signals:
    void yawChanged();
    void pitChanged();
    void rollChanged();

private:
    QSerialPort serialPort;

    float getData(QString id);
};

#endif // SERIAL_H
