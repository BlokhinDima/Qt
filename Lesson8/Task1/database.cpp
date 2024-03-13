#include "database.h"

DataBase::DataBase(QObject *parent)
    : QObject{parent}
{
    dataBase = new QSqlDatabase();
    queryModel = new QSqlQueryModel(this);

    connect(this, &DataBase::sig_SendStatusConnection, this, &DataBase::sl_CreateDataBaseTableModel);
}


DataBase::~DataBase()
{
    delete dataBase;
}


/*!
 * \brief Метод добавляет БД к экземпляру класса QSqlDataBase
 * \param driver драйвер БД
 * \param nameDB имя БД (Если отсутствует Qt задает имя по умолчанию)
 */
void DataBase::AddDataBase(QString driver, QString nameDB)
{
    *dataBase = QSqlDatabase::addDatabase(driver, nameDB);
}


/*!
 * \brief Метод подключается к БД
 * \param для удобства передаем контейнер с данными необходимыми для подключения
 * \return возвращает тип ошибки
 */
void DataBase::ConnectToDataBase(QVector<QString> data)
{
    dataBase->setHostName(data[hostName]);
    dataBase->setDatabaseName(data[dbName]);
    dataBase->setUserName(data[login]);
    dataBase->setPassword(data[pass]);
    dataBase->setPort(data[port].toInt());

    ///Тут должен быть код ДЗ
    bool status;
    status = dataBase->open();
    emit sig_SendStatusConnection(status);
}


/*!
 * \brief Метод производит отключение от БД
 * \param Имя БД
 */
void DataBase::DisconnectFromDataBase(QString nameDb)
{
    *dataBase = QSqlDatabase::database(nameDb);
    dataBase->close();
}


/*!
 * \brief Метод формирует запрос к БД.
 * \param request - SQL запрос
 * \return
 */
void DataBase::RequestToDB(QString request)
{
    ///Тут должен быть код ДЗ
    QSqlError err;
    queryModel->setQuery(request, *dataBase);

    if (queryModel->lastError().isValid())
        err = queryModel->lastError();

    emit sig_SendStatusRequest(err);
}


void DataBase::RequestAllFilms()
{
    QSqlError err;
    tableModel->setTable("film");
    tableModel->select();

    if (tableModel->lastError().isValid())
        err = tableModel->lastError();

    emit sig_SendStatusRequest(err);
}


void DataBase::ReadAnswerFromDB(int requestType)
{
    /*
     * Используем оператор switch для разделения запросов
    */
    switch (requestType)
    {
        case requestAllFilms:
        {
            emit sig_SendDataFromDB(tableModel);
            break;
        }
        case requestComedy:
        {
            emit sig_SendDataFromDB(queryModel);
            break;
        }
        case requestHorrors:
        {
            emit sig_SendDataFromDB(queryModel);
            break;
        }
        default:
            break;
    }
}


/*!
 * @brief Метод возвращает последнюю ошибку БД
 */
QSqlError DataBase::GetLastError()
{
    return dataBase->lastError();
}


void DataBase::ClearModels()
{
    queryModel->clear();
    tableModel->clear();
}


void DataBase::sl_CreateDataBaseTableModel(bool conncetion_status)
{
    if (conncetion_status)
        tableModel = new QSqlTableModel(this, *dataBase);
}
