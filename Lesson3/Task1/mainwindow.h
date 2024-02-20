#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "helpdialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pb_ok_clicked();

    void on_pb_help_clicked();

private:
    Ui::MainWindow *ui;
    HelpDialog* help_dialog;
};
#endif // MAINWINDOW_H
