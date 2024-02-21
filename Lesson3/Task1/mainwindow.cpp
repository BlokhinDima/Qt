#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "connectiondialog.h"

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

void MainWindow::on_pb_connection_menu_clicked()
{
    connection_dialog = new ConnectionDialog(this);
    connection_dialog->show();
}

