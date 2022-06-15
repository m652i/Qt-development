#include <climits>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "qrcodegen.h"
#include "mainwindow.h"
#include <QApplication>

void paintQR(QPainter &painter, const QSize sz, const QString &data, QColor fg);



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;


    w.show();

    return a.exec();
}


