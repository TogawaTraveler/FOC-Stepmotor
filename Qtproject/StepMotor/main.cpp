#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFile file(":/resource/Aqua.qss");
    file.open(QFile::ReadOnly);
    QTextStream filetext(&file);
    QString stylesheet = filetext.readAll();
    a.setStyleSheet(stylesheet);
    file.close();
    MainWindow w;
    w.show();
    return a.exec();
}
