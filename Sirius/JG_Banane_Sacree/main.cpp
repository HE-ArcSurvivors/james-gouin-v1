#include "gameboard.h"
#include "m_menustart.h"
#include <QApplication>
#include "w_object.h"
#include "maingame.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MenuStart w;
//    Gameboard w;
//    WidgetObject w;
    MainGame w;
    w.show();

    return a.exec();
}
