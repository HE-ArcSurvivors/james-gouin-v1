#include "gameboard.h"
#include "m_menustart.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MenuStart w;
    Gameboard w;
    w.show();

    return a.exec();
}
