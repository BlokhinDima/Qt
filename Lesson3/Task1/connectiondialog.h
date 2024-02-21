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

private slots:


    void on_pb_ok_clicked();

private:
    Ui::ConnectionDialog *ui;
};

#endif // HELPDIALOG_H
