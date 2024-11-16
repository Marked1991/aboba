#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPixmap>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QPixmap pix;
    QTimer *timer;
    void getSettings();
    void channel_mode();
    void message_mode();
    void packet_mode();
    void clean();
    void changeLabelVisible(char color,int number, bool state);
    void clearTrack();

private slots:
    void TimerAlarm();

    void on_startBut_clicked();

    void on_stopBut_clicked();

    void on_comboBox_mode_currentIndexChanged(int index);

    void on_comboBox_example_currentIndexChanged(int index);

    void on_horizontalSlider_valueChanged(int value);

protected:

};
#endif // MAINWINDOW_H
