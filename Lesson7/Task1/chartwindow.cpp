#include <QChart>
#include <QChartView>
#include "chartwindow.h"
#include "datachart.h"
#include "ui_chartwindow.h"


ChartWindow::ChartWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChartWindow)
{
    ui->setupUi(this);

    chart = new QChart();
    chart->legend()->setVisible(false);
    chart->setTitle("ADC data");

    dataChart = new DataChart();

    chartView = new QChartView(chart);
    layout = new QGridLayout;
    this->setLayout(layout);
    layout->addWidget(chartView);
    chartView->show();
}


ChartWindow::~ChartWindow()
{
    delete ui;
    delete chart;
    delete dataChart;
    delete chartView;
}


void ChartWindow::DisplayData(QVector<int> x, QVector<double> y)
{
    dataChart->ClearGraph(chart);
    dataChart->AddDataToGrahp(x, y);
    dataChart->UpdateGraph(chart);
    this->show();
}
