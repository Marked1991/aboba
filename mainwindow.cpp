#include "mainwindow.h"
#include "./ui_mainwindow.h"

int settings[2] = {0,0}; // глобальная переменная хранящая что сейчас выбрано в combobocksах
int frame = 0;
int len = 0;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //скрываем все обозначения пути (если придумаешь как это сделать лучше поправь)
    clean();


    QPixmap pix(":/img/image.png"); // грузим картинку связи
    QSize pixSize(1000, 900);
    pix.scaled(pixSize,Qt::KeepAspectRatio);
    ui->image->setPixmap(pix);


    QPixmap logopix(":/img/logo.png"); // грузим лого ВУЦ
    QSize logoSize(100, 100);
    logopix.scaled(logoSize,Qt::KeepAspectRatio);
    ui->logo->setPixmap(logopix);

    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(TimerAlarm()));


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::TimerAlarm()  // обработчик таймера для анимаций
{
    frame+=1;
    clean();
    switch (settings[0]){
    case 1:
        message_mode();
        break;
    case 2:
        packet_mode();
        break;
    }
}


void MainWindow::on_startBut_clicked()
{
    getSettings();

    switch (settings[0]){
    case 0:
        channel_mode();
        break;
    case 1:
        message_mode();
        timer ->start(1000);
        break;
    case 2:
        packet_mode();
        break;
    }

}

void MainWindow::getSettings() // записываем в переменную что выбрано в комбобоксах
{
    settings[0] = ui->comboBox_mode->currentIndex();
    settings[1] = ui->comboBox_example->currentIndex();
}


void MainWindow::on_comboBox_mode_currentIndexChanged(int index) // на случай смены во время работы режима работы
{
    getSettings();
    clean();
    on_startBut_clicked();
}


void MainWindow::on_comboBox_example_currentIndexChanged(int index) // на случай смены во время работы примера
{
    getSettings();
    clean();
    on_startBut_clicked();
}

void MainWindow::on_stopBut_clicked()
{
    clean();
    timer->stop();
    frame = 0;
}

void MainWindow::clean(){      // очистка всех обозначений пути
    int track[] = {11,12,13,14,15,16,17,18,21,22,23,24,25,26,27,28,31,32,33,34,35,36,37,1115,1215,
                   1517,1316,1416,1618,1721,2123,2325,2326,2124,2428,2822,2134,3132,3234,3233,3536,3637,3436,1734,1617,2224,2427};
    len = sizeof(track) / sizeof(int);
    for (int i = 0; i<len; i++){
        changeLabelVisible(track[i],false);
    }
}
void MainWindow::channel_mode(){ // обработка для коммутации каналов

    switch(settings[1]){
    case 0:
    {
        int track[] = {11,1115,15,1517,17,1721,21,2123,23,2325,25};
        len = sizeof(track) / sizeof(int);
        for (int i = 0; i<len; i++){
            changeLabelVisible(track[i],true);
        }
        break;
    }
    case 1:
    {
        int track[] = {12,1215,15,1517,17,1734,3234,34,32,3132,31};
        len = sizeof(track) / sizeof(int);
        for (int i = 0; i<len; i++){
            changeLabelVisible(track[i],true);
        }
        break;
    }
    case 2:
    {
        int track[] = {11,1115,15,1517,17,1617,16,1618,18};
        len = sizeof(track) / sizeof(int);
        for (int i = 0; i<len; i++){
            changeLabelVisible(track[i],true);
        }
        break;
    }
    case 3:
    {
        int track[] = {11,1115,15,1517,17,1721,21,2124,24,2428,28};
        len = sizeof(track) / sizeof(int);
        for (int i = 0; i<len; i++){
            changeLabelVisible(track[i],true);
        }
        break;
    }
    case 4:
    {
        int track[] = {28,2428,24,2124,21,2124,34,3436,36,3536,35,2134};
        len = sizeof(track) / sizeof(int);
        for (int i = 0; i<len; i++){
            changeLabelVisible(track[i],true);
        }
        break;
    }
    case 5:
    {
        int track[] = {35,3536,36,3637,37};
        len = sizeof(track) / sizeof(int);
        for (int i = 0; i<len; i++){
            changeLabelVisible(track[i],true);
        }
        break;
    }
    }
}

void MainWindow::message_mode(){ // обработка для коммутации сообщений
    switch(settings[1]){
    case 1:
    {
        int track[] = {35,3536,36,3637,37};
        changeLabelVisible(track[frame], true);
        break;
    }
    }
}

void MainWindow::packet_mode(){ // обработка для коммутации пакетов

}

void MainWindow::changeLabelVisible(int number, bool state){ // функция для более легкой работы с labels
    switch (number) {
    case 11:
        ui->label_11->setVisible(state);
        break;
    case 12:
        ui->label_12->setVisible(state);
        break;
    case 13:
        ui->label_13->setVisible(state);
        break;
    case 14:
        ui->label_14->setVisible(state);
        break;
    case 15:
        ui->label_15->setVisible(state);
        break;
    case 16:
        ui->label_16->setVisible(state);
        break;
    case 17:
        ui->label_17->setVisible(state);
        break;
    case 18:
        ui->label_18->setVisible(state);
        break;
    case 21:
        ui->label_21->setVisible(state);
        break;
    case 22:
        ui->label_22->setVisible(state);
        break;
    case 23:
        ui->label_23->setVisible(state);
        break;
    case 24:
        ui->label_24->setVisible(state);
        break;
    case 25:
        ui->label_25->setVisible(state);
        break;
    case 26:
        ui->label_26->setVisible(state);
        break;
    case 27:
        ui->label_27->setVisible(state);
        break;
    case 28:
        ui->label_28->setVisible(state);
        break;
    case 31:
        ui->label_31->setVisible(state);
        break;
    case 32:
        ui->label_32->setVisible(state);
        break;
    case 33:
        ui->label_33->setVisible(state);
        break;
    case 34:
        ui->label_34->setVisible(state);
        break;
    case 35:
        ui->label_35->setVisible(state);
        break;
    case 36:
        ui->label_36->setVisible(state);
        break;
    case 37:
        ui->label_37->setVisible(state);
        break;
    case 1115:
        ui->label_1115->setVisible(state);
        break;
    case 1517:
        ui->label_1517->setVisible(state);
        break;
    case 1215:
        ui->label_1215->setVisible(state);
        break;
    case 1316:
        ui->label_1316->setVisible(state);
        break;
    case 1618:
        ui->label_1618->setVisible(state);
        break;
    case 1416:
        ui->label_1416->setVisible(state);
        break;
    case 1617:
        ui->label_1617->setVisible(state);
        break;
    case 1721:
        ui->label_1721->setVisible(state);
        break;
    case 1734:
        ui->label_1734->setVisible(state);
        break;
    case 2134:
        ui->label_2134->setVisible(state);
        break;
    case 2123:
        ui->label_2123->setVisible(state);
        break;
    case 2325:
        ui->label_2325->setVisible(state);
        break;
    case 2326:
        ui->label_2326->setVisible(state);
        break;
    case 2124:
        ui->label_2124->setVisible(state);
        break;
    case 2427:
        ui->label_2427->setVisible(state);
        break;
    case 2428:
        ui->label_2428->setVisible(state);
        break;
    case 2224:
        ui->label_2224->setVisible(state);
        break;
    case 3132:
        ui->label_3132->setVisible(state);
        break;
    case 3234:
        ui->label_3234->setVisible(state);
        break;
    case 3233:
        ui->label_3233->setVisible(state);
        break;
    case 3536:
        ui->label_3536->setVisible(state);
        break;
    case 3637:
        ui->label_3637->setVisible(state);
        break;
    case 3436:
        ui->label_3436->setVisible(state);
        break;
    }

}

