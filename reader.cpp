#include "reader.h"

reader::reader(QObject *parent) : QObject(parent)
{
    speedValue = 0;
    fNeedleUp = true;
    connect(&timer, &QTimer::timeout, this, &reader::timeOut);
    timer.start(70);
    qDebug() << "Timer started;";
}

void reader::timeOut()
{
    QObject* speedometer = this->parent()->findChild<QObject*>("speedometer");
    QObject* speedText = this->parent()->findChild<QObject*>("speedText");

    if (fNeedleUp)
    {

        if (speedValue <= 200)
        {
            speedometer->setProperty("value", speedValue);
            speedText->setProperty("text", QString::number(speedValue));
            //speedValue += qrand() % 10;
            speedValue++;
        }
        else
        {
            speedometer->setProperty("value", 200);
            speedText->setProperty("text", "200");
            //timer.stop();
            qDebug() << "Timer stoped;";
            fNeedleUp = false;
        }
    }

    else
    {
        if (speedValue > 0)
        {
            speedometer->setProperty("value", speedValue);
            speedText->setProperty("text", QString::number(speedValue));
            speedValue--;
            timer.stop();
            timer.start(5);
        }
        else
        {
            speedometer->setProperty("value", 0);
            speedText->setProperty("text", "0");
            timer.stop();
            fNeedleUp = true;
            timer.start(70);
        }
    }

}
