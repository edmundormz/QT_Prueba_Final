#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QRandomGenerator>
#include <QFile>
#include <QTextStream>
#include <QDir>
#include <QMessageBox>

int cont=0;
int tiempo_muestreo = 1000;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lcdTimer->setFrameStyle(QFrame::NoFrame);

    connect(cronometro, SIGNAL(timeout()),this,SLOT(fTimer()));
    cronometro->start(tiempo_muestreo);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::fTimer(){
    cont++;
    ui->lcdTimer->display(cont);
    cronometro->start(tiempo_muestreo);
    if(cont  == 1000){
        cont = 1;
        progress++;
        ui->progressBar->setValue(progress);
        if(progress == 100){
            progress = 1;
            if(init_log_A == false){
                Logger("A:","A");
                init_log_A = true;
            }
            if(init_log_B == false){
                Logger("B:","B");
                init_log_B = true;
            }
            randomA[random_counter] = qrand() % 100;
            Logger(QString::number(randomA[random_counter]) + ",","A");
            randomB[random_counter] = qrand() % 100;
            Logger(QString::number(randomB[random_counter]) + ",","B");
//            qDebug()<<random_counter;
//            qDebug()<<"Random A:" << randomA[random_counter];
//            qDebug()<<"Random B:" << randomB[random_counter];
            random_counter++;
    }
}
    if(random_counter == 99){
        random_counter = 0;
        for(int i = 0; i<=99; i++){
            randomA[i] = 0;
            randomB[i] = 0;
        }
    }
}

void MainWindow::on_dial_valueChanged(int value)
{
    tiempo_muestreo = value * 100;
    cronometro->start(tiempo_muestreo);
    ui->lbSpeedValue->setText(QString::number(tiempo_muestreo));
}

void MainWindow::Logger(QString command, QString log_array){
    QString current_day = QString::number(date.currentDate().dayOfYear());
    QString logs_dir_path = "/home/hecmundo/qt_logs";

    //Check if logs directory exists
    if (!QDir(logs_dir_path).exists()){
        QDir().mkdir(logs_dir_path);
    }
    //Check if current log file exists
    QFile log_path(logs_dir_path + "/log_" + current_day + log_array + ".csv");
    if (log_path.open(QIODevice::WriteOnly | QIODevice::Append)){
        QTextStream out_log(&log_path);
        QString log = command;
        out_log << log;
        log_path.flush();
        log_path.close();
    }
    else {
        QMessageBox::information(this, "Error", "Unable to open log file");
    }
}

void MainWindow::on_pbStart_clicked()
{
    if(paused){
        cronometro->stop();
        ui->pbStart->setText("Restart");
    }
    else {
        cronometro->start(tiempo_muestreo);
        ui->pbStart->setText("Pause");
    }
    paused = !paused;
}
