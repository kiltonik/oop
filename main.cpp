#include <iostream>
#include "mainwindow.h"

#include <QApplication>
#include "test.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Test::run();
    MainWindow w;
    w.show();
    return a.exec();
}
