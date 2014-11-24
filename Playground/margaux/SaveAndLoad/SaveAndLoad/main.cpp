#include "mainwindow.h"
//#include "menustart.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    //MenuStart w;

    w.show();

    return a.exec();
}
