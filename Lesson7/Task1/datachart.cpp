#include <QObject>
#include <QChart>
#include <QLineSeries>
#include "datachart.h"


DataChart::DataChart(QObject *parent)
    : QObject{parent}
{
    graph = new QLineSeries(this);

    xAxis = new QValueAxis(this);
    yAxis = new QValueAxis(this);
    xAxis->setTickCount(10);
    xAxis->setLabelFormat("%.0f");
    xAxis->setTitleText("Point Number");
    yAxis->setTitleText("Point Value");
}


void DataChart::AddDataToGrahp(QVector<int> x, QVector<double> y)
{
    uint32_t size = 0;

    if(x.size() >= y.size())
    {
        size = y.size();

    }
    else
    {
        size = x.size();
    }

    for(int j = 0; j < size; j++)
    {
        graph->append(x[j], y[j]);
    }

    UpdateYAxisRange(y);
}


void DataChart::UpdateYAxisRange(QVector<double> y)
{
    yAxis->setRange(*std::min_element(y.constBegin(), y.constEnd()),
                    *std::max_element(y.constBegin(), y.constEnd()));
}


void DataChart::ClearGraph(QChart *chart)
{
    if (chart->series().isEmpty() == false)
    {
        graph->clear();
        chart->removeSeries(graph);
        chart->removeAxis(xAxis);
        chart->removeAxis(yAxis);
    }
}


void DataChart::UpdateGraph(QChart *chart)
{
    chart->addSeries(graph);
    chart->addAxis(xAxis, Qt::AlignBottom);
    chart->addAxis(yAxis, Qt::AlignLeft);
    graph->attachAxis(xAxis);
    graph->attachAxis(yAxis);
}
