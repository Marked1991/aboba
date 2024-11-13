#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPixmap pix(":/img/image.png"); // грузим картинку связи
    QSize pixSize(1000, 900);
    pix.scaled(pixSize,Qt::KeepAspectRatio);
    ui->image->setPixmap(pix);


    QPixmap logopix(":/img/logo.png"); // грузим лого ВУЦ
    QSize logoSize(100, 100);
    logopix.scaled(logoSize,Qt::KeepAspectRatio);
    ui->logo->setPixmap(logopix);


}




MainWindow::~MainWindow()
{
    delete ui;
}
