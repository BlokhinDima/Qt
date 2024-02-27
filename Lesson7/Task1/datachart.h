#ifndef DATACHART_H
#define DATACHART_H

#include <QObject>
#include <QChart>
#include <QLineSeries>
#include <QValueAxis>


class DataChart : public QObject
{
    Q_OBJECT
public:
    explicit DataChart(QObject *parent = nullptr);
    void AddDataToGrahp(QVector<int> x, QVector<double> y);
    void ClearGraph(QChart* chart);
    void UpdateGraph(QChart* chart);

private:
    QLineSeries* graph;
    QValueAxis* xAxis;
    QValueAxis* yAxis;
    void UpdateYAxisRange(QVector<double> y);
};

#endif // DATACHART_H
