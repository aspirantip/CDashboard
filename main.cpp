#include <QCoreApplication>

#include <QtSerialPort/QSerialPort>
#include <QSerialPortInfo>

#include <QDebug>

void handlerError(QSerialPort::SerialPortError error)
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

void settingsPort()
{

}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // information about system
    // ==========================================
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
    // ==========================================

    // open and setting port
    // ==========================================
    QString nameComPort = "/dev/ttyUSB0";
    QSerialPort srPort;
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

        return 0;
    }
    // ==========================================




    // read data
    // ==========================================
    srPort.clear(QSerialPort::AllDirections);
    srPort.clearError();


    int numRead = 0, numReadTotal = 0;
    const uint size_buff = 1;
    uint8_t bufIn[size_buff];
    memset(bufIn, 1, sizeof(uint8_t)*size_buff);


    char val;
    forever {
        numRead = srPort.read(&val, 1);
        //qDebug() << "Number of data read = " << numRead;
        if ( numRead != 0)
            qDebug() << "value =" << (uchar)val;



        numReadTotal += numRead;

        // stop read data from com-port
        //if (numReadTotal == 50)
        //    break;

        numRead = 0;
        val = 0;
        srPort.waitForReadyRead( 100 );
    }



    // ==========================================


    srPort.close();

    return a.exec();
}
