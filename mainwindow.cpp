#include "mainwindow.h"
#include "./ui_mainwindow.h"

int settings[6] = {0,0,0,0,100,0}; // глобальная переменная хранящая что сейчас выбрано {mode, example, frame, maxframe, speed, lenght track}

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

    // поворот линий
    rotate_lable(":/img/LinePackets.png", ui->label_1115, 9);

    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(TimerAlarm()));


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
        channel_mode();
        break;
    case 1:
        message_mode();
        timer ->start(1000*(200-settings[4])/100);
        break;
    case 2:
        packet_mode();
        timer ->start(1000*(200-settings[4])/100);
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
    on_stopBut_clicked();
    on_startBut_clicked();
}


void MainWindow::on_comboBox_example_currentIndexChanged(int index) // на случай смены во время работы примера
{
    getSettings();
    on_stopBut_clicked();
    on_startBut_clicked();
}

void MainWindow::on_stopBut_clicked()
{
    clean();
    timer->stop();
    settings[2] = 0;
}

void MainWindow::clean(){      // очистка всех обозначений пути
    int track[] = {11,12,13,14,15,16,17,18,21,22,23,24,25,26,27,28,31,32,33,34,35,36,37,1115,1215,
                   1517,1316,1416,1618,1721,2123,2325,2326,2124,2428,2822,2134,3132,3234,3233,3536,3637,3436,1734,1617,2224,2427};
    settings[5] = sizeof(track) / sizeof(int);
    for (int i = 0; i<settings[5]; i++){
        changeLabelVisible('R',track[i],false);
        changeLabelVisible('G',track[i],false);
        changeLabelVisible('B',track[i],false);
        track[i] = 0;
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
        break;
    }
    case 1:
    {
        int track[] = {12,1215,15,1517,17,1734,3234,34,32,3132,31};
        settings[5] = sizeof(track) / sizeof(int);
        for (int i = 0; i<settings[5]; i++){
            changeLabelVisible('R',track[i],true);
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
        break;
    }
    case 3:
    {
        int track[] = {11,1115,15,1517,17,1721,21,2124,24,2428,28};
        settings[5] = sizeof(track) / sizeof(int);
        for (int i = 0; i<settings[5]; i++){
            changeLabelVisible('R',track[i],true);
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
        break;
    }
    case 5:
    {
        int track[] = {35,3536,36,3637,37};
        settings[5] = sizeof(track) / sizeof(int);
        for (int i = 0; i<settings[5]; i++){
            changeLabelVisible('R',track[i],true);
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
        int track[] = {26,2326,23,2123,21,1721,17,1617,16,1316,13};
        settings[3] = sizeof(track) / sizeof(int);
        changeLabelVisible('R',track[settings[2]], true);
        break;
    }
    case 4:
    {
        int track[] = {14,1416,16,1617,17,1721,21,2134,34,3234,32,3132,31};
        settings[3] = sizeof(track) / sizeof(int);
        changeLabelVisible('R',track[settings[2]], true);
        break;
    }
    case 5:
    {
        int track[] = {22,2224,24,2124,21,2123,23,2326,26};
        settings[3] = sizeof(track) / sizeof(int);
        changeLabelVisible('R',track[settings[2]], true);
        break;
    }
    }

}

void MainWindow::packet_mode(){ // обработка для коммутации пакетов

    switch(settings[1]){
    case 0:
    {
        int track1[] = {13,13,13,1316,16,1617,17,1734,34,3234,32,3233,33};
        int track2[] = {13,13,1316,16,1617,17,1734,34,3234,32,3233,33};
        int track3[] = {13,1316,16,1617,17,1734,34,3234,32,3233,33};
        settings[3] = sizeof(track1) / sizeof(int);
        changeLabelVisible('R',track1[settings[2]], true);
        changeLabelVisible('G',track2[settings[2]], true);
        changeLabelVisible('B',track3[settings[2]], true);
        break;
    }
    }
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    settings[4] = value;
    timer->stop();
    timer ->start(1000*(200-settings[4])/100);

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
        case 1734:
            ui->label_B1734->setVisible(state);
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
        case 1734:
            ui->label_G1734->setVisible(state);
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
        }
    }
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
