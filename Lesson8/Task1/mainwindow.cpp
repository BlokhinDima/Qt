#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    //Исходное состояние виджетов
    ui->setupUi(this);
    ui->lb_statusConnect->setStyleSheet("color:red");
    ui->pb_request->setEnabled(false);

    /*
     * Выделим память под необходимые объекты. Все они наследники
     * QObject, поэтому воспользуемся иерархией.
    */

    connetion_dialog = new ConnectionDialog(this);
    dataBase = new DataBase(this);
    msg = new QMessageBox(this);

    //Установим размер вектора данных для подключения к БД
    dataForConnect.resize(NUM_DATA_FOR_CONNECT_TO_DB);

    /*
     * Добавим БД используя стандартный драйвер PSQL и зададим имя.
    */
    dataBase->AddDataBase(POSTGRE_DRIVER, DB_NAME);

    /*
     * Устанавливаем данные для подключениея к БД.
     * Поскольку метод небольшой используем лямбда-функцию.
     */
    connect(connetion_dialog, &ConnectionDialog::sig_sendData, this, [&](QVector<QString> receivData){
        dataForConnect = receivData;
    });

    /*
     * Соединяем сигнал, который передает ответ от БД с методом, который отображает ответ в ПИ
     */
     connect(dataBase, &DataBase::sig_SendDataFromDB, this, &MainWindow::ScreenDataFromDB);

    /*
     *  Сигнал для подключения к БД
     */
    connect(dataBase, &DataBase::sig_SendStatusConnection, this, &MainWindow::ReceiveStatusConnectionToDB);

    connect(dataBase, &DataBase::sig_SendStatusRequest, this, &MainWindow::ReceiveStatusRequestToDB);
}


MainWindow::~MainWindow()
{
    delete ui;
}


/*!
 * @brief Слот отображает форму для ввода данных подключения к БД
 */
void MainWindow::on_act_addData_triggered()
{
    //Отобразим диалоговое окно. Какой метод нужно использовать?
    connetion_dialog->show();
}


/*!
 * @brief Слот выполняет подключение к БД. И отображает ошибки.
 */
void MainWindow::on_act_connect_triggered()
{
    /*
     * Обработчик кнопки у нас должен подключаться и отключаться от БД.
     * Можно привязаться к надписи лейбла статуса. Если он равен
     * "Отключено" мы осуществляем подключение, если "Подключено" то
     * отключаемся
    */

    if(ui->lb_statusConnect->text() == "Отключено"){

       ui->lb_statusConnect->setText("Подключение");
       ui->lb_statusConnect->setStyleSheet("color : black");

       auto conn = [&]{dataBase->ConnectToDataBase(dataForConnect);};
       QtConcurrent::run(conn);
    }
    else{
        dataBase->DisconnectFromDataBase(DB_NAME);
        ui->lb_statusConnect->setText("Отключено");
        ui->act_connect->setText("Подключиться");
        ui->lb_statusConnect->setStyleSheet("color:red");
        ui->pb_request->setEnabled(false);
    }

}


/*!
 * \brief Обработчик кнопки "Получить"
 */
void MainWindow::on_pb_request_clicked()
{
    ///Тут должен быть код ДЗ
    QString condition;
    auto selection = ui->cb_category->currentIndex();

    switch (static_cast<requestType>(selection + 1))
    {
        case requestAllFilms:
        {
            auto req = [&]{dataBase->RequestAllFilms();};
            QtConcurrent::run(req);
            return;
        }
        case requestComedy:
        {
            condition = "'Comedy'";
            break;
        }
        case requestHorrors:
        {
            condition = "'Horror'";
            break;
        }
    }

    auto req = [&]{dataBase->RequestToDB(request + condition);};
    QtConcurrent::run(req);
}


/*!
 * \brief Обработчик кнопки "Очистить"
 */
void MainWindow::on_pb_clear_clicked()
{
    dataBase->ClearModels();
}


/*!
 * \brief Слот отображает значение в QTableWidget
 * \param widget
 * \param typeRequest
 */
void MainWindow::ScreenDataFromDB(QSqlQueryModel *query_model)
{
    ui->tv_result->setModel(query_model);
    ui->tv_result->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    int cols_num = query_model->columnCount();
    if (cols_num != 2)
    {
        for (int i = 0; i < cols_num; i++)
        {
            if (!(i == 1 || i == 2))
            {
                ui->tv_result->hideColumn(i);
            }
        }
    }
    else
    {
        ui->tv_result->showColumn(0);
        ui->tv_result->showColumn(1);
    }
}


/*!
 * \brief Метод изменяет стотояние формы в зависимости от статуса подключения к БД
 * \param status
 */
void MainWindow::ReceiveStatusConnectionToDB(bool status)
{
    if(status){
        ui->act_connect->setText("Отключиться");
        ui->lb_statusConnect->setText("Подключено к БД");
        ui->lb_statusConnect->setStyleSheet("color:green");
        ui->pb_request->setEnabled(true);
    }
    else{
        dataBase->DisconnectFromDataBase(DB_NAME);
        msg->setIcon(QMessageBox::Critical);
        msg->setText(dataBase->GetLastError().text());
        ui->lb_statusConnect->setText("Отключено");
        ui->lb_statusConnect->setStyleSheet("color:red");
        msg->exec();
    }

}


/*!
 * \brief Метод обрабатывает ответ БД на поступивший запрос
 * \param err
 */
void MainWindow::ReceiveStatusRequestToDB(QSqlError err)
{
    if(err.type() != QSqlError::NoError){
        msg->setText(err.text());
        msg->exec();
    }
    else{
        auto selection = ui->cb_category->currentIndex();
        dataBase->ReadAnswerFromDB(static_cast<requestType>(selection + 1));
    }
}
