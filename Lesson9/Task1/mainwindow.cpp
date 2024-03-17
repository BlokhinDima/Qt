#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    udpWorker = new UDPworker(this);
    udpWorker->InitSocket(BIND_PORT);

    userUdpWorker = new UDPworker(this);
    userUdpWorker->InitSocket(USR_PORT);

    connect(udpWorker, &UDPworker::sig_sendTimeToGUI, this, &MainWindow::DisplayTime);
    connect(udpWorker, &UDPworker::sig_sendDatagramInfoToGUI, this, &MainWindow::DisplayDatagramInfo);

    connect(userUdpWorker, &UDPworker::sig_sendTimeToGUI, this, &MainWindow::DisplayTime);
    connect(userUdpWorker, &UDPworker::sig_sendDatagramInfoToGUI, this, &MainWindow::DisplayDatagramInfo);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [&]{

        QDateTime dateTime = QDateTime::currentDateTime();

        QByteArray dataToSend;
        QDataStream outStr(&dataToSend, QIODevice::WriteOnly);

        outStr << dateTime;

        udpWorker->SendDatagram(dataToSend);
        timer->start(TIMER_DELAY);

    });
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pb_start_clicked()
{
    timer->start(TIMER_DELAY);
}


void MainWindow::DisplayTime(QDateTime data)
{
    checkMessagesDisplayLimit();

    ui->te_result->append("Текущее время: " + data.toString() + ". "
                "Принято пакетов " + QString::number(counterPck));

}


void MainWindow::DisplayDatagramInfo(QString sender_addr, long long bytes_size)
{
    checkMessagesDisplayLimit();

    ui->te_result->append("Принято сообщение от " + sender_addr + ", размер сообщения (байт) "
                + QString::number(bytes_size));
}


void MainWindow::checkMessagesDisplayLimit()
{
    counterPck++;
    if(counterPck % 20 == 0){
        ui->te_result->clear();
    }
}


void MainWindow::on_pb_stop_clicked()
{
    timer->stop();
}


void MainWindow::on_pb_sendDatagram_clicked()
{
    auto datagram = ui->te_datagramText->toPlainText().toUtf8();
    userUdpWorker->SendDatagram(datagram);
}
