#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <QObject>
#include <QTimer>

class Stopwatch : public QObject
{
    static const int TIMEOUT_MILLISECONDS = 100;

    Q_OBJECT
public:
    explicit Stopwatch(QObject *parent = nullptr);
    void start() { timer->start(TIMEOUT_MILLISECONDS); }
    void stop() { timer->stop(); }
    void reset();
    qint64 get_circle_number() { return circle_number; }
    void set_circle_number(qint64 value) { circle_number = value; }
    void increment_circle_number() { circle_number++; }

signals:
    emit void sig_time_updated(double new_time);

private slots:
    void sl_increment_time_counter();

private:
    QTimer* timer;
    double time_counter = 0;
    qint64 circle_number = 0;

};

#endif // STOPWATCH_H
