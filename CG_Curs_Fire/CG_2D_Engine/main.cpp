#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    freal A = F2X(10.54);
    freal B = XD(A, I2X(2)); // 5.26953

    qDebug() << X2F(A - B);
    qDebug() << X2F(A + B);
    qDebug() << X2F(XD(A, B));
    qDebug() << X2F(XM(A, B));

    return a.exec();
}
