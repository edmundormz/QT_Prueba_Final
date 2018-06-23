#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QRandomGenerator>

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
            randomA[random_counter] = qrand() % 100;
            randomB[random_counter] = qrand() % 100;
            qDebug()<<random_counter;
            qDebug()<<"Random A:" << randomA[random_counter];
            qDebug()<<"Random B:" << randomB[random_counter];
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
