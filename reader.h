#ifndef READER_H
#define READER_H

#include <QObject>
#include <QDebug>

#include <QtSerialPort/QSerialPort>
#include <QSerialPortInfo>

class Reader : public QObject
{
    Q_OBJECT
public:
    explicit Reader(QObject *parent = 0);
    ~Reader();

private:
    void getInfoDevices();      // получаем информацию об устройствах подключенных к системе
    void connectDevice();
    void handlerError(QSerialPort::SerialPortError error);


    QObject* speedometer;
    QObject* speedText;
    QObject* objLeftTurn;
    QObject* objRightTurn;

    QSerialPort srPort;

    uint8_t valSpeed;
    bool leftTurn;
    bool rightTurn;


signals:

public slots:

private slots:
    void slUpdate();
};

#endif // READER_H
