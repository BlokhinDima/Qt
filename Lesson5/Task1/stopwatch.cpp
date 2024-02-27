#include <QTimer>
#include "stopwatch.h"

Stopwatch::Stopwatch(QObject *parent)
    : QObject{parent}
{
    timer = new QTimer(this);
    QObject::connect(timer, &QTimer::timeout, this, &Stopwatch::sl_increment_time_counter);
}


void Stopwatch::reset()
{
    time_counter = 0;
    circle_number = 0;
    start();
}


void Stopwatch::sl_increment_time_counter()
{
    time_counter += TIMEOUT_MILLISECONDS / 1000.0;
    emit sig_time_updated(time_counter);
}
