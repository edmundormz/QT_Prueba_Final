#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QDate>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void fTimer();
    void Logger(QString command, QString log_array);

private slots:
    void on_dial_valueChanged(int value);

    void on_pbStart_clicked();

    void on_pbReset_clicked();

private:
    Ui::MainWindow *ui;

    QTimer *cronometro = new QTimer(this);
    int progress = 1;
    int random_counter = 0;
    int randomA [100];
    int randomB [100];
    bool display_randoms = false;
    QDate date;
    bool init_log_A = false;
    bool init_log_B = false;
    bool paused = true;
};

#endif // MAINWINDOW_H
