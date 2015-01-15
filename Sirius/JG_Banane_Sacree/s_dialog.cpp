#include "s_dialog.h"

#include <QBrush>

S_Dialog::S_Dialog(int xpos, int ypos, QGraphicsItem *parent) : Surface(xpos, ypos, parent)
{
    setDesign();
}
S_Dialog::S_Dialog(QGraphicsItem *parent) : Surface(0, 0, parent)
{
    setDesign();
}

void S_Dialog::setDesign()
{
//    QBrush brush;
//    brush.setStyle(Qt::SolidPattern);
//    brush.setColor(Qt::red);

//    setBrush(brush);
}

void S_Dialog::setDialogNumber(int value)
{
    this->dialogNumber = value;
}

int S_Dialog::getDialogNumber()
{
    return this->dialogNumber;
}
