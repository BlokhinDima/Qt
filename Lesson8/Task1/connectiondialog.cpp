#include "connectiondialog.h"
#include "ui_connectiondialog.h"
#include "database.h"


ConnectionDialog::ConnectionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConnectionDialog)
{
    ui->setupUi(this);
    ui->le_host->setText("981757-ca08998.tmweb.ru");
    ui->le_database_name->setText("netology_cpp");
    ui->le_login->setText("netology_usr_cpp");
    ui->le_password->setText("CppNeto3");
    ui->sb_port->setValue(5432);

    data.resize(NUM_DATA_FOR_CONNECT_TO_DB);
}


ConnectionDialog::~ConnectionDialog()
{
    delete ui;
}


void ConnectionDialog::on_pb_ok_clicked()
{
    this->ui->pb_ok->setStyleSheet("background-color: green");

    data[hostName] = ui->le_host->text();
    data[dbName] = ui->le_database_name->text();
    data[login] = ui->le_login->text();
    data[pass] = ui->le_password->text();
    data[port] = ui->sb_port->text();

    emit sig_sendData(data);
}
