#include "serial.h"

/**
 * @brief Serial::Serial imposta le variabili necessarie per  comunicazione seriale
 * @param port QString che indica il numer odella porta a cui si collega la seriale
 */
Serial::Serial(QString port) {
    serialPort.setPortName(port);
    serialPort.setBaudRate(QSerialPort::Baud115200);
    serialPort.setDataBits(QSerialPort::Data8);
    serialPort.setParity(QSerialPort::NoParity);
    serialPort.setStopBits(QSerialPort::OneStop);
    serialPort.setFlowControl(QSerialPort::NoFlowControl);
    if (!serialPort.open(QIODevice::ReadWrite)) {
       //fare qualcosa perché errori
    }
}

/**
 * @brief Serial::getData richiede i dati dalla comunicazione seriale e li invia
 * @param id QString che indica il tipo di dato da ricevere
 * @return float che indica il dato ricevuto da inviare
 */
float Serial::getData(QString id) {
    QString data;
    do {
        serialPort.write((id+"\n").toLocal8Bit());
        serialPort.waitForReadyRead();
        data = serialPort.readLine();
    } while(data.length() < 6 || data.length()>8);
    return data.toFloat();
}
