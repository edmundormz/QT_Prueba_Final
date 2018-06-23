#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

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
    }
}

void MainWindow::on_dial_valueChanged(int value)
{
    tiempo_muestreo = value * 100;
    cronometro->start(tiempo_muestreo);
    ui->lbSpeedValue->setText(QString::number(tiempo_muestreo));
}
