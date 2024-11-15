#include "mainwindow.h"
#include "./ui_mainwindow.h"

int settings[2] = {0,0}; // глобальная переменная хранящая что сейчас выбрано в combobocksах

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //скрываем все обозначения пути (если придумаешь как это сделать лучше поправь)
    ui->label_11->setVisible(false);
    ui->label_12->setVisible(false);
    ui->label_13->setVisible(false);
    ui->label_14->setVisible(false);
    ui->label_15->setVisible(false);
    ui->label_16->setVisible(false);
    ui->label_17->setVisible(false);
    ui->label_18->setVisible(false);
    ui->label_21->setVisible(false);
    ui->label_22->setVisible(false);
    ui->label_23->setVisible(false);
    ui->label_24->setVisible(false);
    ui->label_25->setVisible(false);
    ui->label_26->setVisible(false);
    ui->label_27->setVisible(false);
    ui->label_28->setVisible(false);
    ui->label_31->setVisible(false);
    ui->label_32->setVisible(false);
    ui->label_33->setVisible(false);
    ui->label_34->setVisible(false);
    ui->label_35->setVisible(false);
    ui->label_36->setVisible(false);
    ui->label_37->setVisible(false);
    ui->label_1115->setVisible(false);
    ui->label_1517->setVisible(false);
    ui->label_1215->setVisible(false);
    ui->label_1316->setVisible(false);
    ui->label_1618->setVisible(false);
    ui->label_1416->setVisible(false);
    ui->label_1617->setVisible(false);
    ui->label_1721->setVisible(false);
    ui->label_1734->setVisible(false);
    ui->label_2134->setVisible(false);
    ui->label_2123->setVisible(false);
    ui->label_2325->setVisible(false);
    ui->label_2326->setVisible(false);
    ui->label_2124->setVisible(false);
    ui->label_2427->setVisible(false);
    ui->label_2428->setVisible(false);
    ui->label_2224->setVisible(false);
    ui->label_3132->setVisible(false);
    ui->label_3234->setVisible(false);
    ui->label_3233->setVisible(false);
    ui->label_3536->setVisible(false);
    ui->label_3637->setVisible(false);
    ui->label_3436->setVisible(false);


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

void MainWindow::TimerAlarm()  // обработчик таймера для анимаций
{

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
}

void MainWindow::clean(){      // очистка всех обозначений пути
    ui->label_11->setVisible(false);
    ui->label_12->setVisible(false);
    ui->label_13->setVisible(false);
    ui->label_14->setVisible(false);
    ui->label_15->setVisible(false);
    ui->label_16->setVisible(false);
    ui->label_17->setVisible(false);
    ui->label_18->setVisible(false);
    ui->label_21->setVisible(false);
    ui->label_22->setVisible(false);
    ui->label_23->setVisible(false);
    ui->label_24->setVisible(false);
    ui->label_25->setVisible(false);
    ui->label_26->setVisible(false);
    ui->label_27->setVisible(false);
    ui->label_28->setVisible(false);
    ui->label_31->setVisible(false);
    ui->label_32->setVisible(false);
    ui->label_33->setVisible(false);
    ui->label_34->setVisible(false);
    ui->label_35->setVisible(false);
    ui->label_36->setVisible(false);
    ui->label_37->setVisible(false);
    ui->label_1115->setVisible(false);
    ui->label_1517->setVisible(false);
    ui->label_1215->setVisible(false);
    ui->label_1316->setVisible(false);
    ui->label_1618->setVisible(false);
    ui->label_1416->setVisible(false);
    ui->label_1617->setVisible(false);
    ui->label_1721->setVisible(false);
    ui->label_1734->setVisible(false);
    ui->label_2134->setVisible(false);
    ui->label_2123->setVisible(false);
    ui->label_2325->setVisible(false);
    ui->label_2326->setVisible(false);
    ui->label_2124->setVisible(false);
    ui->label_2427->setVisible(false);
    ui->label_2428->setVisible(false);
    ui->label_2224->setVisible(false);
    ui->label_3132->setVisible(false);
    ui->label_3234->setVisible(false);
    ui->label_3233->setVisible(false);
    ui->label_3536->setVisible(false);
    ui->label_3637->setVisible(false);
    ui->label_3436->setVisible(false);
}
void MainWindow::channel_mode(){ // обработка для коммутации каналов

    switch(settings[1]){
    case 0:
        ui->label_11->setVisible(true);
        ui->label_1115->setVisible(true);
        ui->label_15->setVisible(true);
        ui->label_1517->setVisible(true);
        ui->label_17->setVisible(true);
        ui->label_1721->setVisible(true);
        ui->label_21->setVisible(true);
        ui->label_2123->setVisible(true);
        ui->label_23->setVisible(true);
        ui->label_2325->setVisible(true);
        ui->label_25->setVisible(true);
        break;
    case 1:
        ui->label_12->setVisible(true);
        ui->label_1215->setVisible(true);
        ui->label_15->setVisible(true);
        ui->label_1517->setVisible(true);
        ui->label_17->setVisible(true);
        ui->label_1734->setVisible(true);
        ui->label_3234->setVisible(true);
        ui->label_34->setVisible(true);
        ui->label_3234->setVisible(true);
        ui->label_32->setVisible(true);
        ui->label_3132->setVisible(true);
        ui->label_31->setVisible(true);
        break;
    case 2:
        ui->label_11->setVisible(true);
        ui->label_1115->setVisible(true);
        ui->label_15->setVisible(true);
        ui->label_1517->setVisible(true);
        ui->label_17->setVisible(true);
        ui->label_1617->setVisible(true);
        ui->label_16->setVisible(true);
        ui->label_1618->setVisible(true);
        ui->label_18->setVisible(true);
        break;
    case 3:
        ui->label_11->setVisible(true);
        ui->label_1115->setVisible(true);
        ui->label_15->setVisible(true);
        ui->label_1517->setVisible(true);
        ui->label_17->setVisible(true);
        ui->label_1721->setVisible(true);
        ui->label_21->setVisible(true);
        ui->label_2124->setVisible(true);
        ui->label_24->setVisible(true);
        ui->label_2428->setVisible(true);
        ui->label_28->setVisible(true);
        break;
    case 4:
        ui->label_28->setVisible(true);
        ui->label_2428->setVisible(true);
        ui->label_24->setVisible(true);
        ui->label_2124->setVisible(true);
        ui->label_21->setVisible(true);
        ui->label_2134->setVisible(true);
        ui->label_34->setVisible(true);
        ui->label_3436->setVisible(true);
        ui->label_36->setVisible(true);
        ui->label_3536->setVisible(true);
        ui->label_35->setVisible(true);
        break;
    case 5:
        ui->label_35->setVisible(true);
        ui->label_3536->setVisible(true);
        ui->label_36->setVisible(true);
        ui->label_3637->setVisible(true);
        ui->label_37->setVisible(true);
        break;
    }
}

void MainWindow::message_mode(){ // обработка для коммутации сообщений

}

void MainWindow::packet_mode(){ // обработка для коммутации пакетов

}


