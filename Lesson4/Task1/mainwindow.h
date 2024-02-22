#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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


    void on_pb_increment_progress_clicked();

    void on_hs_progressbar_control_sliderMoved(int position);

    void on_pbar_progress_valueChanged(int value);

    void on_dl_progressbar_control_sliderMoved(int position);

    void on_hs_progressbar_control_actionTriggered(int action);

    void on_rb_dial_select_toggled(bool checked);

    void on_rb_slider_select_toggled(bool checked);

    void on_rb_button_select_toggled(bool checked);

    void on_cb_progressbar_color_currentTextChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
