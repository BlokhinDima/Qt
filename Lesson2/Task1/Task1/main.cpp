#include <QCoreApplication>
#include <QtNetwork/QTcpSocket>
#include <QtSql/QSqlDatabase>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QSqlDatabase database;
    QTcpSocket socket;
    return a.exec();
}
