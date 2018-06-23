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
};

#endif // MAINWINDOW_H
