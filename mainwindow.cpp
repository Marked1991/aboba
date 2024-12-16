#include "mainwindow.h"
#include "./ui_mainwindow.h"

int settings[6] = {-1,0,0,0,110,0}; // глобальная переменная хранящая что сейчас выбрано {mode, example, frame, maxframe, speed, lenght track}
bool isStarted = false;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //скрываем все обозначения пути (если придумаешь как это сделать лучше поправь)
    clean();

    QPixmap pix(":/img/svaz.png"); // грузим картинку связи
    QSize pixSize(1000, 900);
    pix.scaled(pixSize,Qt::KeepAspectRatio);
    ui->image->setPixmap(pix);

    startRotate();

    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(TimerAlarm()));

   ui->groupBox_2 ->setStyleSheet("QGroupBox#groupBox_2 {border:0;}"); //убираем рамки у боксов
   ui->groupBox ->setStyleSheet("QGroupBox#groupBox {border:0;}");


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::TimerAlarm()  // обработчик таймера для анимаций
{
    if (settings[2] > settings[3]-1){

        settings[2] = 0;
    }
    else settings[2]+=1;

    switch (settings[0]){
    case 1:
        clean();
        message_mode();
        break;
    case 2:
        clean();
        packet_mode();
        break;
    }
}


void MainWindow::on_startBut_clicked()
{
    getSettings();

    switch (settings[0]){
    case 0:
        changeLabelVisible('c',0,true);
        channel_mode();
        break;
    case 1:
        message_mode();
        changeLabelVisible('m',0,true);
        timerControl(1);
        break;
    case 2:
        packet_mode();
        changeLabelVisible('p',0,true);
        timerControl(1);
        break;
    }

    isStarted = true;

}

void MainWindow::getSettings() // записываем в переменную что выбрано в комбобоксах
{
    settings[0] = ui->comboBox_mode->currentIndex();
    settings[1] = ui->comboBox_example->currentIndex();
}


void MainWindow::on_comboBox_mode_currentIndexChanged(int index) // на случай смены во время работы режима работы
{
    getSettings();
    if (isStarted){
    on_stopBut_clicked();
    on_startBut_clicked();
    }
}


void MainWindow::on_comboBox_example_currentIndexChanged(int index) // на случай смены во время работы примера
{
    getSettings();
    if (isStarted){
        on_stopBut_clicked();
        on_startBut_clicked();
    }
}

void MainWindow::on_stopBut_clicked()
{
    clean();
    timerControl(0);
    settings[2] = 0;
    settings[0] = -1;
    changeLabelVisible('s',0,false);
    isStarted = false;
}

void MainWindow::clean(){  // очистка всех обозначений пути
    int track[] = {11,12,13,14,15,16,17,18,21,22,23,24,25,26,27,28,31,32,33,34,35,36,37,1115,1215,
                   1517,1316,1416,1618,1721,2123,2325,2326,2124,2428,2822,2134,3132,3234,3233,3536,3637,3436,1734,1617,2224,2427,41,42,43,44,45,
                    46,47,48,49,1749,3449,4146,4546,4246,4649,4347,4447,4748,4749};
    int track2[] = {};
    int track3[] = {};
    settings[5] = sizeof(track) / sizeof(int);
    for (int i = 0; i<settings[5]; i++){
        changeLabelVisible('R',track[i],false);
        changeLabelVisible('G',track[i],false);
        changeLabelVisible('B',track[i],false);
        track[i] = 0;
        track2[i] = 0;
        track3[i] = 0;
    }
    changeLabelVisible('s',0,false);

    switch (settings[0]){
    case 0:
        changeLabelVisible('c',0,true);
        break;
    case 1:
        changeLabelVisible('m',0,true);
        break;
    case 2:
        changeLabelVisible('p',0,true);
        break;
    }
}

void MainWindow::channel_mode(){ // обработка для коммутации каналов

    switch(settings[1]){
    case 0:
    {
        int track[] = {11,1115,15,1517,17,1721,21,2123,23,2325,25};
        settings[5] = sizeof(track) / sizeof(int);
        for (int i = 0; i<settings[5]; i++){
            changeLabelVisible('R',track[i],true);
        }
        int track2[] = {41,4146,4649,49,3449,34,3436,36,3536};
        settings[5] = sizeof(track2) / sizeof(int);
        for (int i = 0; i<settings[5]; i++){
            changeLabelVisible('B',track2[i],true);
        }
        int track3[] = {43,4347,47,4447,44};
        settings[5] = sizeof(track3) / sizeof(int);
        for (int i = 0; i<settings[5]; i++){
            changeLabelVisible('G',track3[i],true);
        }
        break;
    }
    case 1:
    {
        int track[] = {12,1215,15,1517,17,1749,49,3449,34,3234,32,3132,31};
        settings[5] = sizeof(track) / sizeof(int);
        for (int i = 0; i<settings[5]; i++){
            changeLabelVisible('R',track[i],true);
        }
        int track2[] = {25,2325,23,2123,21,2124,2224,22};
        settings[5] = sizeof(track2) / sizeof(int);
        for (int i = 0; i<settings[5]; i++){
            changeLabelVisible('B',track2[i],true);
        }
        int track3[] = {45,4546,46,4246,42};
        settings[5] = sizeof(track3) / sizeof(int);
        for (int i = 0; i<settings[5]; i++){
            changeLabelVisible('G',track3[i],true);
        }
        break;
    }
    case 2:
    {
        int track[] = {11,1115,15,1517,17,1617,16,1618,18};
        settings[5] = sizeof(track) / sizeof(int);
        for (int i = 0; i<settings[5]; i++){
            changeLabelVisible('R',track[i],true);
        }
        int track2[] = {26,2326,23,2123,21,2124,24,2427,27};
        settings[5] = sizeof(track2) / sizeof(int);
        for (int i = 0; i<settings[5]; i++){
            changeLabelVisible('B',track2[i],true);
        }
        int track3[] = {31,3132,32,3234,34,3436,36,3536,35};
        settings[5] = sizeof(track3) / sizeof(int);
        for (int i = 0; i<settings[5]; i++){
            changeLabelVisible('G',track3[i],true);
        }
        break;
    }
    case 3:
    {
        int track[] = {11,1115,15,1517,17,1721,21,2124,24,2428,28};
        settings[5] = sizeof(track) / sizeof(int);
        for (int i = 0; i<settings[5]; i++){
            changeLabelVisible('R',track[i],true);
        }
        int track2[] = {13,1316,16,1416,14};
        settings[5] = sizeof(track2) / sizeof(int);
        for (int i = 0; i<settings[5]; i++){
            changeLabelVisible('B',track2[i],true);
        }
        int track3[] = {31,3132,32,3234,34,3436,36,3536,35};
        settings[5] = sizeof(track3) / sizeof(int);
        for (int i = 0; i<settings[5]; i++){
            changeLabelVisible('G',track3[i],true);
        }
        break;
    }
    case 4:
    {
        int track[] = {28,2428,24,2124,21,2124,34,3436,36,3536,35,2134};
        settings[5] = sizeof(track) / sizeof(int);
        for (int i = 0; i<settings[5]; i++){
            changeLabelVisible('R',track[i],true);
        }
        int track2[] = {13,1316,16,1617,17,1517,15,1115,11};
        settings[5] = sizeof(track2) / sizeof(int);
        for (int i = 0; i<settings[5]; i++){
            changeLabelVisible('B',track2[i],true);
        }
        int track3[] = {26,2326,23,2325,25};
        settings[5] = sizeof(track3) / sizeof(int);
        for (int i = 0; i<settings[5]; i++){
            changeLabelVisible('G',track3[i],true);
        }
        break;
    }
    case 5:
    {
        int track[] = {35,3536,36,3637,37};
        settings[5] = sizeof(track) / sizeof(int);
        for (int i = 0; i<settings[5]; i++){
            changeLabelVisible('R',track[i],true);
        }
        int track2[] = {28,2428,24,2124,21,2123,23,2325,25};
        settings[5] = sizeof(track2) / sizeof(int);
        for (int i = 0; i<settings[5]; i++){
            changeLabelVisible('B',track2[i],true);
        }
        int track3[] = {13,1316,16,1617,17,1517,15,1215,12};
        settings[5] = sizeof(track3) / sizeof(int);
        for (int i = 0; i<settings[5]; i++){
            changeLabelVisible('G',track3[i],true);
        }
        break;
    }
    }
}

void MainWindow::message_mode(){ // обработка для коммутации сообщений

    switch(settings[1]){
    case 0:
    {
        int track[] = {13,1316,16,1617,17,1734,34,3234,32,3233,33};
        settings[3] = sizeof(track) / sizeof(int);
        changeLabelVisible('R',track[settings[2]], true);
        break;
    }
    case 1:
    {
        int track[] = {35,3536,36,3436,34,2134,21,2124,24,2428,28};
        settings[3] = sizeof(track) / sizeof(int);
        changeLabelVisible('R',track[settings[2]], true);
        break;
    }
    case 2:
    {
        int track[] = {11,1115,15,1517,17,1617,16,1416,14};
        settings[3] = sizeof(track) / sizeof(int);
        changeLabelVisible('R',track[settings[2]], true);
        break;
    }
    case 3:
    {
        int track[] = {26,2326,23,2123,21,2134,34,1734,17,1617,16,1316,13};
        int track2[] = {14,1416,16,1617,17,1721,21,2134,34,3234,32,3132,31};
        int track3[] = {22,2224,24,2124,21,2123,23,2326,26,0,0};
        settings[3] = sizeof(track2) / sizeof(int);
        changeLabelVisible('R',track[settings[2]], true);

        if (settings[2] > 0) changeLabelVisible('B',track2[settings[2] -1], true);
        if (settings[2] > 1) changeLabelVisible('G',track3[settings[2] -2], true);
        break;
    }
    case 4:
    {
        int track[] = {31,3132,32,3234,34,2134,21,2124,24,2427,27,0,0};
        int track2[] = {18,1618,16,1617,17,1721,21,2134,34,3436,36,3637,37,0};
        int track3[] = {37,3637,36,3436,34,1734,17,1617,16,1316,13};
        settings[3] = sizeof(track) / sizeof(int);
        changeLabelVisible('R',track[settings[2]], true);

        if (settings[2] > 0) changeLabelVisible('B',track2[settings[2] -1], true);
        if (settings[2] > 1) changeLabelVisible('G',track3[settings[2] -2], true);
        break;
    }
    case 5:
    {
        int track[] = {11,1115,15,1517,17,1617,16,1618,18,0};
        int track2[] = {22,2224,24,2124,21,2123,23,2325,25};
        int track3[] = {31,3132,32,3234,34,3436,3536,35};
        settings[3] = sizeof(track) / sizeof(int);
        changeLabelVisible('R',track[settings[2]], true);

        if (settings[2] > 0) changeLabelVisible('B',track2[settings[2] -1], true);
        if (settings[2] > 1) changeLabelVisible('G',track3[settings[2] -2], true);
        break;
    }
    }

}

void MainWindow::packet_mode(){ // обработка для коммутации пакетов

    switch(settings[1]){
    case 0:
    {
        int track[] = {11,1115,15,1517,17,1721,21,2124,24,2428,28,0,0};
        int track2[] = {11,1115,15,1517,17,1734,34,2134,21,24,2428,28,0};
        int track3[] = {11,1115,15,1517,17,1721,21,2124,24,2428,28};
        settings[3] = sizeof(track) / sizeof(int);
        changeLabelVisible('R',track[settings[2]], true);

        if (settings[2] > 0) changeLabelVisible('G',track2[settings[2] -1], true);
        if (settings[2] > 1) changeLabelVisible('B',track3[settings[2] -2], true);
        break;
    }
    case 1:
    {
        int track[] = {31,3132,32,3234,34,2134,21,2123,23,2326,26,0,0};
        int track2[] = {31,3132,32,3234,34,1734,17,1721,21,2123,23,2326,26,0};
        int track3[] = {31,3132,32,3234,34,2134,21,2123,23,2326,26};
        settings[3] = sizeof(track) / sizeof(int);
        changeLabelVisible('R',track[settings[2]], true);

        if (settings[2] > 0) changeLabelVisible('G',track2[settings[2] -1], true);
        if (settings[2] > 1) changeLabelVisible('B',track3[settings[2] -2], true);
        break;
    }
    case 2:
    {
        int track[] = {28,2428,24,2124,21,1721,17,1517,15,1215,12,0,0};
        int track2[] = {28,2428,24,2124,21,1721,17,1517,15,1215,12,0};
        int track3[] = {28,2428,24,2124,21,1721,17,1517,15,1215,12};
        settings[3] = sizeof(track) / sizeof(int);
        changeLabelVisible('R',track[settings[2]], true);

        if (settings[2] > 0) changeLabelVisible('G',track2[settings[2] -1], true);
        if (settings[2] > 1) changeLabelVisible('B',track3[settings[2] -2], true);
        break;
    }
    case 3:
    {
        int track11[] = {22,2224,24,2124,21,1721,17,1617,16,1316,13,0,0};
        int track12[] = {22,2224,24,2124,21,1721,17,1617,16,1316,13,0};
        int track13[] = {22,2224,24,2124,21,1721,17,1617,16,1316,13};
        int track21[] = {0,11,1115,15,1517,17,1734,34,2134,21,24,2428,28,0,0};
        int track22[] = {0,11,1115,15,1517,17,1734,34,2134,21,24,2428,28,0};
        int track23[] = {0,11,1115,15,1517,17,1734,34,2134,21,24,2428,28};
        settings[3] = sizeof(track11) / sizeof(int);
        changeLabelVisible('R',track11[settings[2]], true);
        changeLabelVisible('G',track21[settings[2]], true);

        if (settings[2] > 0){
            changeLabelVisible('R',track11[settings[2] -1], true);
            changeLabelVisible('G',track21[settings[2] -1], true);
        }
        if (settings[2] > 1){
            changeLabelVisible('R',track11[settings[2]-2], true);
            changeLabelVisible('G',track21[settings[2]-2], true);
        }
        break;
    }
    case 4:
    {
        int track11[] = {31,3132,32,3234,34,3436,36,3637,37,0,0};
        int track12[] = {31,3132,32,3234,34,3436,36,3637,37,0};
        int track13[] = {31,3132,32,3234,34,3436,36,3637,37};
        int track21[] = {11,1115,15,1517,17,1617,16,1618,18,0,0};
        int track22[] = {11,1115,15,1517,17,1617,16,1618,18,0};
        int track23[] = {11,1115,15,1517,17,1617,16,1618,18};
        settings[3] = sizeof(track11) / sizeof(int);
        changeLabelVisible('R',track11[settings[2]], true);
        changeLabelVisible('R',track21[settings[2]], true);

        if (settings[2] > 0){
            changeLabelVisible('B',track11[settings[2] -1], true);
            changeLabelVisible('B',track21[settings[2] -1], true);
        }
        if (settings[2] > 1){
            changeLabelVisible('G',track11[settings[2]-2], true);
            changeLabelVisible('G',track21[settings[2]-2], true);
        }
        break;
    }
    case 5:
    {
        int track11[] = {31,3132,32,3234,34,3436,36,3637,37,0,0};
        int track12[] = {31,3132,32,3234,34,3436,36,3637,37,0};
        int track13[] = {31,3132,32,3234,34,3436,36,3637,37};
        int track21[] = {11,1115,15,1517,17,1617,16,1618,18,0,0};
        int track22[] = {11,1115,15,1517,17,1617,16,1618,18,0};
        int track23[] = {11,1115,15,1517,17,1617,16,1618,18};
        int track31[] = {26,2326,23,2123,21,2124,24,2224,22,0,0};
        int track32[] = {26,2326,23,2123,21,2124,24,2224,22,0};
        int track33[] = {26,2326,23,2123,21,2124,24,2224,22};
        settings[3] = sizeof(track11) / sizeof(int);
        changeLabelVisible('R',track11[settings[2]], true);
        changeLabelVisible('R',track21[settings[2]], true);
        changeLabelVisible('R',track31[settings[2]], true);

        if (settings[2] > 0){
            changeLabelVisible('B',track12[settings[2] -1], true);
            changeLabelVisible('B',track22[settings[2] -1], true);
            changeLabelVisible('B',track32[settings[2] -1], true);
        }
        if (settings[2] > 1){
            changeLabelVisible('G',track13[settings[2]-2], true);
            changeLabelVisible('G',track23[settings[2]-2], true);
            changeLabelVisible('G',track33[settings[2]-2], true);
        }
        break;
    }
    }
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    settings[4] = value;
    timerControl(2);
}


void MainWindow::timerControl(int mode){
    switch (mode){
    case 1:
        timer ->start(150*(300-settings[4])/300);
        break;
    case 0:
        timer -> stop();
        break;
    case 2:
        timer->stop();
        timer->start(150*(300-settings[4])/300);
        break;

    }


}


void MainWindow::startRotate(){
    // поворот линий
    rotate_lable(":/img/LinePackets.png", ui->label_1115, 9);
    rotate_lable(":/img/LinePackets.png", ui->label_1215, -18);
    rotate_lable(":/img/LinePackets.png", ui->label_1517, 15);
    rotate_lable(":/img/LinePackets.png", ui->label_2123, -13);
    rotate_lable(":/img/LinePackets.png", ui->label_2325, -10);
    rotate_lable(":/img/LinePackets.png", ui->label_2326, 10);
    rotate_lable(":/img/LinePackets.png", ui->label_1316, 9);
    rotate_lable(":/img/LinePackets.png", ui->label_1617, -21);
    rotate_lable(":/img/LinePackets.png", ui->label_1416, -18);
    rotate_lable(":/img/LinePackets.png", ui->label_1618, 12);
    rotate_lable(":/img/LinePackets.png", ui->label_2427, -11);
    rotate_lable(":/img/LinePackets.png", ui->label_2428, 18);
    rotate_lable(":/img/LinePackets.png", ui->label_2124, 21);
    rotate_lable(":/img/LinePackets.png", ui->label_2224, -10);
    rotate_lable(":/img/LinePackets.png", ui->label_3234, -22);
    rotate_lable(":/img/LinePackets.png", ui->label_3132, -22);
    rotate_lable(":/img/LinePackets.png", ui->label_3233, 20);
    rotate_lable(":/img/LinePackets.png", ui->label_3436, 19);
    rotate_lable(":/img/LinePackets.png", ui->label_3536, -14);
    rotate_lable(":/img/LinePackets.png", ui->label_3637, 11);
    rotate_lable(":/img/BLinePackets.png", ui->label_B1115, 9);
    rotate_lable(":/img/BLinePackets.png", ui->label_B1215, -18);
    rotate_lable(":/img/BLinePackets.png", ui->label_B1517, 15);
    rotate_lable(":/img/BLinePackets.png", ui->label_B1617, -21);
    rotate_lable(":/img/BLinePackets.png", ui->label_B1316, 9);
    rotate_lable(":/img/BLinePackets.png", ui->label_B1416, -18);
    rotate_lable(":/img/BLinePackets.png", ui->label_B1618, 12);
    rotate_lable(":/img/BLinePackets.png", ui->label_B2123, -13);
    rotate_lable(":/img/BLinePackets.png", ui->label_B2325, -10);
    rotate_lable(":/img/BLinePackets.png", ui->label_B2124, 21);
    rotate_lable(":/img/BLinePackets.png", ui->label_B2326, 10);
    rotate_lable(":/img/BLinePackets.png", ui->label_B2427, -11);
    rotate_lable(":/img/BLinePackets.png", ui->label_B2428, 18);
    rotate_lable(":/img/BLinePackets.png", ui->label_B2224, -10);
    rotate_lable(":/img/BLinePackets.png", ui->label_B3234, -22);
    rotate_lable(":/img/BLinePackets.png", ui->label_B3436, 19);
    rotate_lable(":/img/BLinePackets.png", ui->label_B3637, 11);
    rotate_lable(":/img/BLinePackets.png", ui->label_B3536, -14);
    rotate_lable(":/img/BLinePackets.png", ui->label_B3233, 20);
    rotate_lable(":/img/BLinePackets.png", ui->label_B3132, -22);
    rotate_lable(":/img/GLinePackets.png", ui->label_G1115, 9);
    rotate_lable(":/img/GLinePackets.png", ui->label_G1215, -18);
    rotate_lable(":/img/GLinePackets.png", ui->label_G1517, 15);
    rotate_lable(":/img/GLinePackets.png", ui->label_G1617, -21);
    rotate_lable(":/img/GLinePackets.png", ui->label_G1316, 9);
    rotate_lable(":/img/GLinePackets.png", ui->label_G1416, -18);
    rotate_lable(":/img/GLinePackets.png", ui->label_G1618, 12);
    rotate_lable(":/img/GLinePackets.png", ui->label_G2123, -13);
    rotate_lable(":/img/GLinePackets.png", ui->label_G2325, -10);
    rotate_lable(":/img/GLinePackets.png", ui->label_G2326, 10);
    rotate_lable(":/img/GLinePackets.png", ui->label_G2124, 21);
    rotate_lable(":/img/GLinePackets.png", ui->label_G2427, -11);
    rotate_lable(":/img/GLinePackets.png", ui->label_G2428, 18);
    rotate_lable(":/img/GLinePackets.png", ui->label_G2224, -10);
    rotate_lable(":/img/GLinePackets.png", ui->label_G3436, 19);
    rotate_lable(":/img/GLinePackets.png", ui->label_G3234, -22);
    rotate_lable(":/img/GLinePackets.png", ui->label_G3637, 11);
    rotate_lable(":/img/GLinePackets.png", ui->label_G3536, -14);
    rotate_lable(":/img/GLinePackets.png", ui->label_G3233, 20);
    rotate_lable(":/img/GLinePackets.png", ui->label_G3132, -22);

}

void MainWindow::changeLabelVisible(char color,int number, bool state){ // функция для более легкой работы с labels

    switch (color){
    case 'R':
    {
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
        case 41:
            ui->label_41->setVisible(state);
            break;
        case 42:
            ui->label_42->setVisible(state);
            break;
        case 43:
            ui->label_43->setVisible(state);
            break;
        case 44:
            ui->label_44->setVisible(state);
            break;
        case 45:
            ui->label_45->setVisible(state);
            break;
        case 46:
            ui->label_46->setVisible(state);
            break;
        case 47:
            ui->label_47->setVisible(state);
            break;
        case 48:
            ui->label_48->setVisible(state);
            break;
        case 49:
            ui->label_49->setVisible(state);
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
        case 1749:
            ui->label_1749->setVisible(state);
            break;
        case 3449:
            ui->label_3449->setVisible(state);
            break;
        case 4146:
            ui->label_4146->setVisible(state);
            break;
        case 4546:
            ui->label_4546->setVisible(state);
            break;
        case 4246:
            ui->label_4246->setVisible(state);
            break;
        case 4649:
            ui->label_4649->setVisible(state);
            break;
        case 4347:
            ui->label_4347->setVisible(state);
            break;
        case 4447:
            ui->label_4447->setVisible(state);
            break;
        case 4748:
            ui->label_4748->setVisible(state);
            break;
        case 4749:
            ui->label_4749->setVisible(state);
            break;
        }
        break;
    }

    case 'B':
    {
        switch (number) {
        case 11:
            ui->label_B11->setVisible(state);
            break;
        case 12:
            ui->label_B12->setVisible(state);
            break;
        case 13:
            ui->label_B13->setVisible(state);
            break;
        case 14:
            ui->label_B14->setVisible(state);
            break;
        case 15:
            ui->label_B15->setVisible(state);
            break;
        case 16:
            ui->label_B16->setVisible(state);
            break;
        case 17:
            ui->label_B17->setVisible(state);
            break;
        case 18:
            ui->label_B18->setVisible(state);
            break;
        case 21:
            ui->label_B21->setVisible(state);
            break;
        case 22:
            ui->label_B22->setVisible(state);
            break;
        case 23:
            ui->label_B23->setVisible(state);
            break;
        case 24:
            ui->label_B24->setVisible(state);
            break;
        case 25:
            ui->label_B25->setVisible(state);
            break;
        case 26:
            ui->label_B26->setVisible(state);
            break;
        case 27:
            ui->label_B27->setVisible(state);
            break;
        case 28:
            ui->label_B28->setVisible(state);
            break;
        case 31:
            ui->label_B31->setVisible(state);
            break;
        case 32:
            ui->label_B32->setVisible(state);
            break;
        case 33:
            ui->label_B33->setVisible(state);
            break;
        case 34:
            ui->label_B34->setVisible(state);
            break;
        case 35:
            ui->label_B35->setVisible(state);
            break;
        case 36:
            ui->label_B36->setVisible(state);
            break;
        case 37:
            ui->label_B37->setVisible(state);
            break;
        case 41:
            ui->label_B41->setVisible(state);
            break;
        case 42:
            ui->label_B42->setVisible(state);
            break;
        case 43:
            ui->label_B43->setVisible(state);
            break;
        case 44:
            ui->label_B44->setVisible(state);
            break;
        case 45:
            ui->label_B45->setVisible(state);
            break;
        case 46:
            ui->label_B46->setVisible(state);
            break;
        case 47:
            ui->label_B47->setVisible(state);
            break;
        case 48:
            ui->label_B48->setVisible(state);
            break;
        case 49:
            ui->label_B49->setVisible(state);
            break;
        case 1115:
            ui->label_B1115->setVisible(state);
            break;
        case 1517:
            ui->label_B1517->setVisible(state);
            break;
        case 1215:
            ui->label_B1215->setVisible(state);
            break;
        case 1316:
            ui->label_B1316->setVisible(state);
            break;
        case 1618:
            ui->label_B1618->setVisible(state);
            break;
        case 1416:
            ui->label_B1416->setVisible(state);
            break;
        case 1617:
            ui->label_B1617->setVisible(state);
            break;
        case 1721:
            ui->label_B1721->setVisible(state);
            break;
        case 2134:
            ui->label_B2134->setVisible(state);
            break;
        case 2123:
            ui->label_B2123->setVisible(state);
            break;
        case 2325:
            ui->label_B2325->setVisible(state);
            break;
        case 2326:
            ui->label_B2326->setVisible(state);
            break;
        case 2124:
            ui->label_B2124->setVisible(state);
            break;
        case 2427:
            ui->label_B2427->setVisible(state);
            break;
        case 2428:
            ui->label_B2428->setVisible(state);
            break;
        case 2224:
            ui->label_B2224->setVisible(state);
            break;
        case 3132:
            ui->label_B3132->setVisible(state);
            break;
        case 3234:
            ui->label_B3234->setVisible(state);
            break;
        case 3233:
            ui->label_B3233->setVisible(state);
            break;
        case 3536:
            ui->label_B3536->setVisible(state);
            break;
        case 3637:
            ui->label_B3637->setVisible(state);
            break;
        case 3436:
            ui->label_B3436->setVisible(state);
            break;
        case 1749:
            ui->label_B1749->setVisible(state);
            break;
        case 3449:
            ui->label_B3449->setVisible(state);
            break;
        case 4146:
            ui->label_B4146->setVisible(state);
            break;
        case 4546:
            ui->label_B4546->setVisible(state);
            break;
        case 4246:
            ui->label_B4246->setVisible(state);
            break;
        case 4649:
            ui->label_B4649->setVisible(state);
            break;
        case 4347:
            ui->label_B4347->setVisible(state);
            break;
        case 4447:
            ui->label_B4447->setVisible(state);
            break;
        case 4748:
            ui->label_B4748->setVisible(state);
            break;
        case 4749:
            ui->label_B4749->setVisible(state);
            break;
        }

        break;
    }

    case 'G':
    {
        switch (number) {
        case 11:
            ui->label_G11->setVisible(state);
            break;
        case 12:
            ui->label_G12->setVisible(state);
            break;
        case 13:
            ui->label_G13->setVisible(state);
            break;
        case 14:
            ui->label_G14->setVisible(state);
            break;
        case 15:
            ui->label_G15->setVisible(state);
            break;
        case 16:
            ui->label_G16->setVisible(state);
            break;
        case 17:
            ui->label_G17->setVisible(state);
            break;
        case 18:
            ui->label_G18->setVisible(state);
            break;
        case 21:
            ui->label_G21->setVisible(state);
            break;
        case 22:
            ui->label_G22->setVisible(state);
            break;
        case 23:
            ui->label_G23->setVisible(state);
            break;
        case 24:
            ui->label_G24->setVisible(state);
            break;
        case 25:
            ui->label_G25->setVisible(state);
            break;
        case 26:
            ui->label_G26->setVisible(state);
            break;
        case 27:
            ui->label_G27->setVisible(state);
            break;
        case 28:
            ui->label_G28->setVisible(state);
            break;
        case 31:
            ui->label_G31->setVisible(state);
            break;
        case 32:
            ui->label_G32->setVisible(state);
            break;
        case 33:
            ui->label_G33->setVisible(state);
            break;
        case 34:
            ui->label_G34->setVisible(state);
            break;
        case 35:
            ui->label_G35->setVisible(state);
            break;
        case 36:
            ui->label_G36->setVisible(state);
            break;
        case 37:
            ui->label_G37->setVisible(state);
            break;
        case 41:
            ui->label_G41->setVisible(state);
            break;
        case 42:
            ui->label_G42->setVisible(state);
            break;
        case 43:
            ui->label_G43->setVisible(state);
            break;
        case 44:
            ui->label_G44->setVisible(state);
            break;
        case 45:
            ui->label_G45->setVisible(state);
            break;
        case 46:
            ui->label_G46->setVisible(state);
            break;
        case 47:
            ui->label_G47->setVisible(state);
            break;
        case 48:
            ui->label_G48->setVisible(state);
            break;
        case 49:
            ui->label_G49->setVisible(state);
            break;
        case 1115:
            ui->label_G1115->setVisible(state);
            break;
        case 1517:
            ui->label_G1517->setVisible(state);
            break;
        case 1215:
            ui->label_G1215->setVisible(state);
            break;
        case 1316:
            ui->label_G1316->setVisible(state);
            break;
        case 1618:
            ui->label_G1618->setVisible(state);
            break;
        case 1416:
            ui->label_G1416->setVisible(state);
            break;
        case 1617:
            ui->label_G1617->setVisible(state);
            break;
        case 1721:
            ui->label_G1721->setVisible(state);
            break;
        case 2134:
            ui->label_G2134->setVisible(state);
            break;
        case 2123:
            ui->label_G2123->setVisible(state);
            break;
        case 2325:
            ui->label_G2325->setVisible(state);
            break;
        case 2326:
            ui->label_G2326->setVisible(state);
            break;
        case 2124:
            ui->label_G2124->setVisible(state);
            break;
        case 2427:
            ui->label_G2427->setVisible(state);
            break;
        case 2428:
            ui->label_G2428->setVisible(state);
            break;
        case 2224:
            ui->label_G2224->setVisible(state);
            break;
        case 3132:
            ui->label_G3132->setVisible(state);
            break;
        case 3234:
            ui->label_G3234->setVisible(state);
            break;
        case 3233:
            ui->label_G3233->setVisible(state);
            break;
        case 3536:
            ui->label_G3536->setVisible(state);
            break;
        case 3637:
            ui->label_G3637->setVisible(state);
            break;
        case 3436:
            ui->label_G3436->setVisible(state);
            break;
        case 1749:
            ui->label_G1749->setVisible(state);
            break;
        case 3449:
            ui->label_G3449->setVisible(state);
            break;
        case 4146:
            ui->label_G4146->setVisible(state);
            break;
        case 4546:
            ui->label_G4546->setVisible(state);
            break;
        case 4246:
            ui->label_G4246->setVisible(state);
            break;
        case 4649:
            ui->label_G4649->setVisible(state);
            break;
        case 4347:
            ui->label_G4347->setVisible(state);
            break;
        case 4447:
            ui->label_G4447->setVisible(state);
            break;
        case 4748:
            ui->label_G4748->setVisible(state);
            break;
        case 4749:
            ui->label_G4749->setVisible(state);
            break;
        }
    }
    break;
    case 'c':
        ui->groupBox_message->setVisible(state);
        ui->label_ch1->setVisible(state);
        ui->label_ch2->setVisible(state);
        ui->label_ch3->setVisible(state);
        ui->label_4->setVisible(state);
        ui->label_ms1->setVisible(false);
        ui->label_ms2->setVisible(false);
        ui->label_ms3->setVisible(false);
        ui->label_pc1->setVisible(false);
        ui->label_pc2->setVisible(false);
        ui->label_pc3->setVisible(false);
        ui->label_5->setVisible(false);
        ui->label_6->setVisible(false);
        break;
    case 'm':
        ui->groupBox_message->setVisible(state);
        ui->label_ms1->setVisible(state);
        ui->label_ms2->setVisible(state);
        ui->label_ms3->setVisible(state);
        ui->label_5->setVisible(state);
        ui->label_ch1->setVisible(false);
        ui->label_ch2->setVisible(false);
        ui->label_ch3->setVisible(false);
        ui->label_pc1->setVisible(false);
        ui->label_pc2->setVisible(false);
        ui->label_pc3->setVisible(false);
        ui->label_4->setVisible(false);
        ui->label_6->setVisible(false);
        break;
    case 'p':
        ui->groupBox_message->setVisible(state);
        ui->label_pc1->setVisible(state);
        ui->label_pc2->setVisible(state);
        ui->label_pc3->setVisible(state);
        ui->label_6->setVisible(state);
        ui->label_ms1->setVisible(false);
        ui->label_ms2->setVisible(false);
        ui->label_ms3->setVisible(false);
        ui->label_ch1->setVisible(false);
        ui->label_ch2->setVisible(false);
        ui->label_ch3->setVisible(false);
        ui->label_4->setVisible(false);
        ui->label_5->setVisible(false);
        break;
    case 's':
        ui->groupBox_message->setVisible(false);
        ui->label_ch1->setVisible(false);
        ui->label_ch2->setVisible(false);
        ui->label_ch3->setVisible(false);
        ui->label_ms1->setVisible(false);
        ui->label_ms2->setVisible(false);
        ui->label_ms3->setVisible(false);
        ui->label_pc1->setVisible(false);
        ui->label_pc2->setVisible(false);
        ui->label_pc3->setVisible(false);
        ui->label_4->setVisible(false);
        ui->label_5->setVisible(false);
        ui->label_6->setVisible(false);
        break;
    }

}

void MainWindow::rotate_lable(char* file_name, QLabel* map, float angle){ // функция для поворота lables

    QPixmap ship(file_name);
    QPixmap rotate(ship.size());
    rotate.fill(Qt::transparent);

    QPainter p(&rotate);
    p.setRenderHint(QPainter::Antialiasing);
    p.setRenderHint(QPainter::SmoothPixmapTransform);
    p.translate(ship.size().width() / 2, ship.size().height() / 2);
    p.rotate(angle);
    p.translate(-ship.size().width() / 2, -ship.size().height() / 2);

    p.drawPixmap(0, 0, ship);
    p.end();

    map->setPixmap(rotate);

}



