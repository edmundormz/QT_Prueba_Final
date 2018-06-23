#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

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

private slots:
    void on_dial_valueChanged(int value);

private:
    Ui::MainWindow *ui;

    QTimer *cronometro = new QTimer(this);
    int progress = 1;
    int random_counter = 0;
    int randomA [100];
    int randomB [100];
    bool display_randoms = false;
};

#endif // MAINWINDOW_H
