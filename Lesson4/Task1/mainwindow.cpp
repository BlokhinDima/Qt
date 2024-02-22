#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->rb_dial_select->toggle();

    ui->cb_progressbar_color->addItem("green");
    ui->cb_progressbar_color->addItem("red");
    ui->cb_progressbar_color->addItem("yellow");
    ui->cb_progressbar_color->addItem("blue");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pb_increment_progress_clicked()
{
    qint64 current_progress = ui->pbar_progress->value();

    if (current_progress >= 10)
    {
        ui->pbar_progress->setValue(0);
    }
    else
    {
        ui->pbar_progress->setValue(current_progress + 1);
    }
}


void MainWindow::on_hs_progressbar_control_sliderMoved(int position)
{
    ui->pbar_progress->setValue(position);
}


void MainWindow::on_pbar_progress_valueChanged(int value)
{
    ui->hs_progressbar_control->setValue(value);
    ui->dl_progressbar_control->setValue(value);
}


void MainWindow::on_dl_progressbar_control_sliderMoved(int position)
{
    ui->pbar_progress->setValue(position);
}


void MainWindow::on_hs_progressbar_control_actionTriggered(int action)
{
    qint64 slider_value = ui->hs_progressbar_control->value();
    ui->pbar_progress->setValue(slider_value);
}

void MainWindow::on_rb_dial_select_toggled(bool checked)
{
    ui->dl_progressbar_control->setDisabled(false);
    ui->hs_progressbar_control->setDisabled(true);
    ui->pb_increment_progress->setDisabled(true);
}


void MainWindow::on_rb_slider_select_toggled(bool checked)
{
    ui->hs_progressbar_control->setDisabled(false);
    ui->pb_increment_progress->setDisabled(true);
    ui->dl_progressbar_control->setDisabled(true);
}


void MainWindow::on_rb_button_select_toggled(bool checked)
{
    ui->pb_increment_progress->setDisabled(false);
    ui->dl_progressbar_control->setDisabled(true);
    ui->hs_progressbar_control->setDisabled(true);
}


void MainWindow::on_cb_progressbar_color_currentTextChanged(const QString &arg1)
{
    ui->pbar_progress->setStyleSheet("QProgressBar::chunk { background-color: " + arg1 + "}");
}

