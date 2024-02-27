#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "stopwatch.h"

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
    void on_pb_start_stop_clicked();
    void on_pb_clear_clicked();
    void on_pb_circle_clicked();
    void sl_update_time_label(double time_value);

private:
    Ui::MainWindow *ui;
    Stopwatch* stopwatch;
};
#endif // MAINWINDOW_H
