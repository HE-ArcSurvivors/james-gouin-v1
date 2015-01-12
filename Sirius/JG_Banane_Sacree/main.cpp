#include "gameboard.h"
#include "m_menustart.h"
#include <QApplication>
#include "m_menustart.h"
#include "w_object.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MenuStart w;
    Gameboard w;
    //WidgetObject w;
    w.show();

    return a.exec();
}
