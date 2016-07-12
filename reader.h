#ifndef READER_H
#define READER_H

#include <QObject>
#include <QDebug>
#include <QTimer>

class reader : public QObject
{
    Q_OBJECT
public:
    explicit reader(QObject *parent = 0);

    QTimer timer;
    uint16_t speedValue;
    bool fNeedleUp;

private slots:
    void timeOut();
};

#endif // READER_H
