#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "helpdialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pb_ok_clicked()
{
    ui->statusbar->showMessage("Connected!");
}

void MainWindow::on_pb_help_clicked()
{
    help_dialog = new HelpDialog(this);
    help_dialog->show();
}
