#ifndef HELPDIALOG_H
#define HELPDIALOG_H

#include <QDialog>

namespace Ui {
class ConnectionDialog;
}

class ConnectionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConnectionDialog(QWidget *parent = nullptr);
    ~ConnectionDialog();

signals:
   void sig_sendData(QVector<QString> dbData);

private slots:
    void on_pb_ok_clicked();

private:
    Ui::ConnectionDialog *ui;
    QVector<QString> data;
};

#endif // HELPDIALOG_H
