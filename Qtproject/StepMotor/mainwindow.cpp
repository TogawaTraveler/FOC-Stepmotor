#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QSerialPortInfo"
#include "QMessageBox"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    QStringList serialNamePort;
    ui->setupUi(this);


    setupLine(ui->customPlot);
    serialPort = new QSerialPort(this);
    connect(serialPort,SIGNAL(readyRead()),this,SLOT(Datadeal()));
    foreach (const QSerialPortInfo &info,QSerialPortInfo::availablePorts())
    {
        serialNamePort<<info.portName();
    }
    ui->Serial->addItems(serialNamePort);
    ui->Speed->setRange(-1400,1400);
    ui->Angle->setMinimum(0);
    ui->Angle->setMaximum(360);
    ui->Angle->setNotchesVisible(true);
    ui->Angle->setNotchTarget(10);
    ui->Angle->setWrapping(true);
    ui->SpeedCheck->setCheckState(Qt::Checked);
    ui->tabWidget->setTabText(0,QString("数据"));
    ui->tabWidget->setTabText(1,QString("参数(小于999的正整数)"));
    angle_flag = 1;
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::DrawLine()
{
    static int count = 0;
    if(ui->AngleCheck->checkState() == Qt::Checked)
        ui->customPlot->graph(0)->addData(count, Angle);
    if(ui->SpeedCheck->checkState() == Qt::Checked)
        ui->customPlot->graph(0)->addData(count, Speed);
    ui->customPlot->graph(0)->rescaleValueAxis(true); // 自动调整纵坐标

    ui->customPlot->xAxis->setRange(count, 50, Qt::AlignRight);
    ui->customPlot->replot();
    count++;
}

void MainWindow::Datadeal()
{
    QString buf;
    buf = QString(serialPort->readAll());
    if(buf[0] == 'V')
    {
        Speed = QString(buf).mid(3,6).toFloat();
        Voltage = QString(buf).mid(12,4).toFloat();
        Temperature = QString(buf).mid(19,4).toFloat();
        Angle = (QString(buf).mid(26,5).toInt()) % 16384;
        if(buf[2] == '-')
            Speed = -Speed;
        DrawLine();
        ui->speedline->setText(QString(buf).mid(2,7));
        ui->temline->setText(QString(buf).mid(19,4));
        ui->posiline->setText(QString(buf).mid(26,5));
        ui->voltline->setText(QString(buf).mid(12,4));
        Re_Angle = (int)(Angle*360/16384.0)%360;
        if(ui->AngleCheck->checkState() != Qt::Checked)
            ui->Angle->setValue((Re_Angle+180)%360);
    }
}

void MainWindow::on_Open_clicked()
{
    serialPort->setPortName(ui->Serial->currentText());
    serialPort->setBaudRate(QSerialPort::Baud115200);
    serialPort->setDataBits(QSerialPort::Data8);
    serialPort->setStopBits(QSerialPort::OneStop);
    serialPort->setParity(QSerialPort::NoParity);
    if(serialPort->open(QIODevice::ReadWrite) == true){

    }else{
        QMessageBox::critical(this,"提示","失败");
    }
}
void MainWindow::setupLine(QCustomPlot *customPlot)
{
    customPlot->setBackground(QBrush(QColor(35,27,23)));
    // 设置坐标轴颜色
    customPlot->xAxis->setBasePen(QPen(QColor("#00C4F7"), 2));     // 轴线画笔
    customPlot->xAxis->setSubTickPen(QPen(QColor("#00C4F7"), 1));  // 轴刻度的画笔
    customPlot->xAxis->setSubTickPen(QPen(QColor("#00C4F7"), 1));  // 轴子刻度线的画笔
    customPlot->xAxis->setTickLabelColor(QColor("#00C4F7"));       // 坐标轴上字体

    customPlot->yAxis->setBasePen(QPen(QColor("#00C4F7"), 2));     // 轴线画笔
    customPlot->yAxis->setSubTickPen(QPen(QColor("#00C4F7"), 1));  // 轴刻度的画笔
    customPlot->yAxis->setSubTickPen(QPen(QColor("#00C4F7"), 1));  // 轴子刻度线的画笔
    customPlot->yAxis->setTickLabelColor(QColor("#00C4F7"));       // 坐标轴上字体
    //坐标轴末端设置样式
    customPlot->xAxis->setUpperEnding(QCPLineEnding::esFlatArrow);
    customPlot->yAxis->setUpperEnding(QCPLineEnding::esFlatArrow);
    customPlot->yAxis->setLabelColor(QColor("#00C4F7"));
    customPlot->yAxis->setSubTicks(false);  // 设置子刻度不显示
    customPlot->yAxis2->setSubTicks(false);
    customPlot->legend->setVisible(true);
    customPlot->addGraph(); // blue line
    QPen pen;
    pen.setColor(QColor(40, 110, 255));
    pen.setWidth(3);
    customPlot->graph(0)->setPen(pen);
    customPlot->graph(0)->setName(QString::fromLocal8Bit("Speed"));


    QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
    timeTicker->setTimeFormat("%h:%m:%s");
    customPlot->xAxis->setTicker(timeTicker);
    customPlot->axisRect()->setupFullAxesBox();
    customPlot->yAxis->setRange(-4800, 4800);

}


void MainWindow::on_Reset_clicked()
{
    QString temp;
    temp.sprintf("RESET%c",ui->IDEdit->text().data()[0]);
    serialPort->write(temp.toLocal8Bit());
    ui->Angle->setValue(180);
    ui->Speed->setValue(0);
}


void MainWindow::on_Send_clicked()
{
    serialPort->write(ui->Send_edit->text().toLocal8Bit().data());
}


void MainWindow::on_AngleCheck_stateChanged(int arg1)
{
    if(ui->AngleCheck->checkState() == Qt::Checked)
    {
        ui->Angle->setDisabled(0);
        QString buf;
        double vule = (360-ui->Angle->value());
        buf.sprintf("L%03d%c",(int)vule,ui->IDEdit->text().data()[0]);
        serialPort->write(buf.toLocal8Bit());
        ui->SpeedCheck->setCheckState(Qt::Unchecked);
        ui->customPlot->graph(0)->setName(QString::fromLocal8Bit("Angle"));
        ui->customPlot->yAxis->setRange(0,16384);
        ui->Speed->setDisabled(1);
    }
}


void MainWindow::on_SpeedCheck_stateChanged(int arg1)
{
    if(ui->SpeedCheck->checkState() == Qt::Checked)
    {
        ui->Speed->setDisabled(0);
        QString buf;
        int vule = ui->Speed->value();
        if(vule >= 0)
            buf.sprintf("V+%04d%c",vule,ui->IDEdit->text().data()[0]);
        else
            buf.sprintf("V-%04d%c",-vule,ui->IDEdit->text().data()[0]);
        serialPort->write(buf.toLocal8Bit());
        ui->AngleCheck->setCheckState(Qt::Unchecked);
        ui->customPlot->graph(0)->setName(QString::fromLocal8Bit("Speed"));
        ui->customPlot->yAxis->setRange(-4800, 4800);
        ui->Angle->setDisabled(1);
    }
}


void MainWindow::on_Speed_sliderReleased()
{
    QString buf;
    int vule = ui->Speed->value();
    if(vule >= 0)
        buf.sprintf("V+%04d%c",vule,ui->IDEdit->text().data()[0]);
    else
        buf.sprintf("V-%04d%c",-vule,ui->IDEdit->text().data()[0]);
    serialPort->write(buf.toLocal8Bit());
}


void MainWindow::on_Angle_sliderReleased()
{
    QString buf;
    angle_flag = 1;
    double vule = (int)(360-ui->Angle->value());
    buf.sprintf("L%03d%c",(int)vule,ui->IDEdit->text().data()[0]);
    serialPort->write(buf.toLocal8Bit());
    qDebug()<<buf<<endl;
}

void MainWindow::on_Angle_sliderPressed()
{
    angle_flag = 0;
}


void MainWindow::on_tabWidget_currentChanged(int index)
{
    if(index == 1)
    {
        ui->Angle->setDisabled(0);
        QString buf;
        double vule = (360-ui->Angle->value());
        buf.sprintf("L%03d%c",(int)vule,ui->IDEdit->text().data()[0]);
        serialPort->write(buf.toLocal8Bit());
        ui->SpeedCheck->setCheckState(Qt::Unchecked);
        ui->customPlot->graph(0)->setName(QString::fromLocal8Bit("Angle"));
        ui->customPlot->yAxis->setRange(0,16384);
        ui->Speed->setDisabled(1);
        ui->AngleCheck->setCheckState(Qt::Checked);
        ui->SpeedCheck->setCheckState(Qt::Unchecked);
        ui->AngleCheck->setEnabled(0);
        ui->SpeedCheck->setEnabled(0);
    }
    else
    {
        ui->AngleCheck->setEnabled(1);
        ui->SpeedCheck->setEnabled(1);
    }
}


void MainWindow::on_lineEdit_IP_returnPressed()
{
    uint16_t data;
    QString buf;
    data = ui->lineEdit_IP->text().toInt();
    buf.sprintf("PIDIP%03d%c",data,ui->IDEdit->text().data()[0]);
    serialPort->write(buf.toLocal8Bit());
    qDebug()<<buf<<endl;
}


void MainWindow::on_lineEdit_II_returnPressed()
{
    uint16_t data;
    QString buf;
    data = ui->lineEdit_IP->text().toInt();
    buf.sprintf("PIDII%03d%c",data,ui->IDEdit->text().data()[0]);
    serialPort->write(buf.toLocal8Bit());
    qDebug()<<buf<<endl;
}


void MainWindow::on_lineEdit_ID_returnPressed()
{
    uint16_t data;
    QString buf;
    data = ui->lineEdit_IP->text().toInt();
    buf.sprintf("PIDID%03d%c",data,ui->IDEdit->text().data()[0]);
    serialPort->write(buf.toLocal8Bit());
    qDebug()<<buf<<endl;
}


void MainWindow::on_lineEdit_PP_returnPressed()
{
    uint16_t data;
    QString buf;
    data = ui->lineEdit_IP->text().toInt();
    buf.sprintf("PIDPP%03d%c",data,ui->IDEdit->text().data()[0]);
    serialPort->write(buf.toLocal8Bit());
    qDebug()<<buf<<endl;
}


void MainWindow::on_lineEdit_PI_returnPressed()
{
    uint16_t data;
    QString buf;
    data = ui->lineEdit_IP->text().toInt();
    buf.sprintf("PIDPI%03d%c",data,ui->IDEdit->text().data()[0]);
    serialPort->write(buf.toLocal8Bit());
    qDebug()<<buf<<endl;
}


void MainWindow::on_lineEdit_PD_returnPressed()
{
    uint16_t data;
    QString buf;
    data = ui->lineEdit_IP->text().toInt();
    buf.sprintf("PIDPD%03d%c",data,ui->IDEdit->text().data()[0]);
    serialPort->write(buf.toLocal8Bit());
    qDebug()<<buf<<endl;
}


void MainWindow::on_lineEdit_AP_returnPressed()
{
    uint16_t data;
    QString buf;
    data = ui->lineEdit_IP->text().toInt();
    buf.sprintf("PIDAP%03d%c",data,ui->IDEdit->text().data()[0]);
    serialPort->write(buf.toLocal8Bit());
    qDebug()<<buf<<endl;
}


void MainWindow::on_lineEdit_AI_returnPressed()
{
    uint16_t data;
    QString buf;
    data = ui->lineEdit_IP->text().toInt();
    buf.sprintf("PIDAI%03d%c",data,ui->IDEdit->text().data()[0]);
    serialPort->write(buf.toLocal8Bit());
    qDebug()<<buf<<endl;
}


void MainWindow::on_lineEdit_AD_returnPressed()
{
    uint16_t data;
    QString buf;
    data = ui->lineEdit_IP->text().toInt();
    buf.sprintf("PIDAD%03d%c",data,ui->IDEdit->text().data()[0]);
    serialPort->write(buf.toLocal8Bit());
    qDebug()<<buf<<endl;
}


void MainWindow::on_pushButton_clicked()
{
    QString buf;
    buf.sprintf("UPDATA%c",ui->IDEdit->text().data()[0]);
    serialPort->write(buf.toLocal8Bit());
    qDebug()<<buf<<endl;
}

