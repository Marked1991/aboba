#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPixmap pix(":/img/image.png"); // грузим первоначальную картинку связи
    ui->image->setPixmap(pix);


    QPixmap logopix(":/img/logo.png"); // грузим лого ВУЦ и ресайз под размер окошка
    QSize logoSize(100, 100);
    logopix.scaled(logoSize,Qt::KeepAspectRatio);
    ui->logo->setPixmap(logopix);

}

void MainWindow::resizeEvent(QResizeEvent *event) // переопределение события изменения размера окна
{
    QMainWindow::resizeEvent(event);
    int h = geometry().height(); // берем высоту окна (по идее оно должно так работать ибо у современных мониторов h < w)
   ui->image->setMaximumSize(h*1.06, h); // ограничиваем максимальную ширину через высоту (для сохранения соотношения сторон) (хер знает че оно не сохраняет соотношение всегда) (мб из-за ширины label)
    // по хорошему надо еще сделать чтобы при уменьшении окна не колбасило( это защита от увеличения окна)   *
    if(pix.isNull() ) return; // ждем пока появится картинка
    ui->image->setPixmap(pix.scaled(ui->image->size(), Qt::KeepAspectRatio)); // ресайз и вывод новой картинки


    if (!(ui->image->width() *1.06 >= ui->image->height())){ //тут ничева не работает (попытка создать (*))
        ui->image->setMinimumSize(ui->image->height()*0.89,ui->image->height());
    }
    if (!(ui->image->height() *0.89 >= ui->image->width())){
        ui->image->setMinimumSize(ui->image->height(),ui->image->width()*1.06);
    }



}



MainWindow::~MainWindow()
{
    delete ui;
}
