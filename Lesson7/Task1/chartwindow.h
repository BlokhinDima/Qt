#ifndef CHARTWINDOW_H
#define CHARTWINDOW_H

#include <QLineSeries>
#include <QtCharts>
#include <QChartView>
#include "datachart.h"


namespace Ui {
class ChartWindow;
}


class ChartWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ChartWindow(QWidget *parent = nullptr);
    ~ChartWindow();
    void DisplayData(QVector<int> x, QVector<double> y);

private:
    Ui::ChartWindow *ui;
    DataChart* dataChart;
    QChart* chart;
    QChartView* chartView;
    QGridLayout *layout;
};

#endif // CHARTWINDOW_H
