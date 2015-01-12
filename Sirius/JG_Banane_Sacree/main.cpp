#include "gameboard.h"
#include <QApplication>
#include "m_menustart.h"
#include "w_object.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Gameboard w;
    //WidgetObject w;
    w.show();

    return a.exec();
}
