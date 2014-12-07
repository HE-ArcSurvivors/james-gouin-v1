#include "s_snow.h"
#include <QBrush>

S_Snow::S_Snow(int xpos, int ypos, QGraphicsItem *parent) : Surface(xpos, ypos, parent)
{

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::white);

    setBrush(brush);
}
