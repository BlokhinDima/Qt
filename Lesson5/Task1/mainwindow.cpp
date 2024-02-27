#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "stopwatch.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->pb_circle->setDisabled(true);
    stopwatch = new Stopwatch(this);

    QObject::connect(stopwatch, &Stopwatch::sig_time_updated, this, &MainWindow::sl_update_time_label);
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pb_start_stop_clicked()
{
    if (ui->pb_start_stop->isChecked())
    {
        ui->pb_start_stop->setText("Stop");
        stopwatch->start();
        ui->pb_circle->setDisabled(false);
    }
    else
    {
        ui->pb_start_stop->setText("Start");
        stopwatch->stop();
        ui->pb_circle->setDisabled(true);
    }
}


void MainWindow::sl_update_time_label(double time_value)
{
    QString valueAsString = QString::number(time_value, 'f', 1);
    ui->lb_timedigits->setText(valueAsString);
}


void MainWindow::on_pb_clear_clicked()
{
    ui->lb_timedigits->setText("0.0");
    ui->pte_circles->clear();
    stopwatch->reset();

    if (ui->pb_start_stop->isChecked() == false)
        stopwatch->stop();
}


void MainWindow::on_pb_circle_clicked()
{
    stopwatch->increment_circle_number();

    QString message = "Circle " + QString::number(stopwatch->get_circle_number())
            + " Time: " + ui->lb_timedigits->text() + " seconds.";
    ui->pte_circles->appendPlainText(message);

    auto circle_number = stopwatch->get_circle_number();
    stopwatch->reset();
    stopwatch->set_circle_number(circle_number);
}
