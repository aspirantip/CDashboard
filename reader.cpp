#include "reader.h"

Reader::Reader(QObject *parent) : QObject(parent)
{

    speedometer = this->parent()->findChild<QObject*>("speedometer");
    speedText = this->parent()->findChild<QObject*>("speedText");

    //gauge       = this->parent()->findChild<QObject*>("gauge");
    //txtSpeed   = this->parent()->findChild<QObject*>("objSpeedText");
    objLeftTurn = this->parent()->findChild<QObject*>("leftIndicator");
    objRightTurn= this->parent()->findChild<QObject*>("rightIndicator");

    getInfoDevices();
    connectDevice();

}

Reader::~Reader()
{
    if (srPort.isOpen())    srPort.close();

}

void Reader::getInfoDevices()
{
    foreach (const QSerialPortInfo &infoPort, QSerialPortInfo::availablePorts()) {
            qDebug() << "Name        : " << infoPort.portName();
            qDebug() << "Description : " << infoPort.description();
            qDebug() << "Manufacturer: " << infoPort.manufacturer();

            qDebug() << "ID product: " << infoPort.productIdentifier();
            qDebug() << "ID vendor: " << infoPort.vendorIdentifier() << endl;

            if (infoPort.isBusy())
                qDebug() << "Port is busy";
            else
                qDebug() << "Port is not busy";
    }
}

void Reader::connectDevice()
{
    // open and setting port
    // ==========================================
    QString nameComPort = "/dev/ttyUSB0";
    srPort.setPortName (nameComPort);

    if (srPort.open(QIODevice::ReadOnly)){
        qDebug() << "Port is open";

        //settings com-port
        // ==========================================
        if (srPort.setBaudRate( QSerialPort::Baud19200 ) /*&&
            srPort.setDataBits( QSerialPort::Data8 )     &&
            srPort.setParity  ( QSerialPort::NoParity )  &&
            srPort.setStopBits( QSerialPort::OneStop )   &&
            srPort.setFlowControl( QSerialPort::NoFlowControl)*/){
            qDebug() << "Port is configured";
        }
        else
            qDebug() << "We have a problem with the confuration com-port";
        // ==========================================

    }
    else{
        qDebug() << "Port is not opend";
        srPort.close();
        handlerError( srPort.error() );
    }
    // ==========================================

    srPort.clear();
    srPort.clearError();

    connect(&srPort, &QSerialPort::readyRead, this, &Reader::slUpdate);
}

void Reader::handlerError(QSerialPort::SerialPortError error)
{
    switch (error){
    case 0: qDebug() << "No error occurred"; break;
    case 1: qDebug() << "An error occurred while attempting to open an non-existing device"; break;
    case 2: qDebug() << "An error occurred while attempting to open an already opened device by another process or a user not having enough permission and credentials to open."; break;
    case 3: qDebug() << "An error occurred while attempting to open an already opened device in this object."; break;
    case 4: qDebug() << "Parity error detected by the hardware while reading data."; break;
    case 5: qDebug() << "Framing error detected by the hardware while reading data."; break;
    case 6: qDebug() << "Break condition detected by the hardware on the input line."; break;
    case 7: qDebug() << "An I/O error occurred while writing the data."; break;
    case 8: qDebug() << "An I/O error occurred while reading the data."; break;
    case 9: qDebug() << "An I/O error occurred when a resource becomes unavailable, e.g. when the device is unexpectedly removed from the system."; break;
    case 10: qDebug() << "The requested device operation is not supported or prohibited by the running operating system."; break;
    case 11: qDebug() << "An unidentified error occurred."; break;
    case 12: qDebug() << "A timeout error occurred. "; break;
    case 13: qDebug() << "This error occurs when an operation is executed that can only be successfully performed if the device is open."; break;
    default: qDebug() << "Unknown error"; break;
    }
}

void Reader::slUpdate()
{
    char buf[3] = {0,0,0};
    quint64 numRead = srPort.read(buf, 3);
    //qDebug() << "Number of data read = " << numRead;
    if ( numRead != 0){
        if (0){
            qDebug() << "=======================================";
            qDebug() << "speed      =" << (uchar) buf[0];
            qDebug() << "left turn  =" << (uchar) buf[1];
            qDebug() << "right turn =" << (uchar) buf[2];
            qDebug() << "=======================================\n\n";
        }


        speedometer->setProperty("value", buf[0]);
        speedText->setProperty("text", QString::number( buf[0]) );

        if (leftTurn == false && buf[1] == 1){
            leftTurn = true;
            objLeftTurn->setProperty("on", leftTurn);
        }
        else{
            if (leftTurn == true && buf[1] == 0){
                leftTurn = false;
                objLeftTurn->setProperty("on", leftTurn);
            }
        }

        if (rightTurn == false && buf[2] == 1){
            rightTurn = true;
            objRightTurn->setProperty("on", rightTurn);
        }
        else{
            if (rightTurn == true && buf[2] == 0){
                rightTurn = false;
                objRightTurn->setProperty("on", rightTurn);
            }
        }

    }

}
