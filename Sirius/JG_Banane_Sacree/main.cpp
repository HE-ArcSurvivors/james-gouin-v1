#include "gameboard.h"
#include <QApplication>
#include "m_menustart.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Gameboard w;
    w.show();

    return a.exec();
}
