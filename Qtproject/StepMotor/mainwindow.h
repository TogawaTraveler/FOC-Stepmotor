#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qcustomplot.h"
#include "QSerialPort"
#include <QUdpSocket>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setupLine(QCustomPlot *customPlot);
    void DrawLine();

    QSerialPort *serialPort;
    float Speed;
    int Angle;
    float Voltage;
    float Temperature;
    int Re_Angle;
    bool angle_flag;

private slots:
    void on_Open_clicked();

    void on_SpeedCheck_stateChanged(int arg1);

    void on_Send_clicked();

    void on_Reset_clicked();

    void Datadeal();

    void on_AngleCheck_stateChanged(int arg1);

    void on_Speed_sliderReleased();

    void on_Angle_sliderReleased();

    void on_Angle_sliderPressed();


    void on_tabWidget_currentChanged(int index);

    void on_lineEdit_IP_returnPressed();


    void on_lineEdit_II_returnPressed();

    void on_lineEdit_ID_returnPressed();

    void on_lineEdit_PP_returnPressed();

    void on_lineEdit_PI_returnPressed();

    void on_lineEdit_PD_returnPressed();

    void on_lineEdit_AP_returnPressed();

    void on_lineEdit_AI_returnPressed();

    void on_lineEdit_AD_returnPressed();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
