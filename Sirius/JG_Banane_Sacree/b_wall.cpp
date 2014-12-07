#include "b_wall.h"
#include <QBrush>

B_Wall::B_Wall(int xpos, int ypos, QGraphicsItem *parent) : Block(xpos, ypos, parent)
{

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::red);

    setBrush(brush);
}
