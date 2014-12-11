#include "s_ice.h"

#include <QBrush>
#include <QGraphicsItem>

S_Ice::S_Ice(int xpos, int ypos, QGraphicsItem *parent) : Surface(xpos, ypos, parent)
{
    setDesign();
}
S_Ice::S_Ice(QGraphicsItem *parent) : Surface(0, 0, parent)
{
    setDesign();
}

void S_Ice::setDesign()
{
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::yellow);

    setBrush(brush);
}
