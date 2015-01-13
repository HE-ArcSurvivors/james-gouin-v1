#include "s_snow.h"

#include <QBrush>
#include <QGraphicsItem>

S_Snow::S_Snow(int xpos, int ypos, QGraphicsItem *parent) : Surface(xpos, ypos, parent)
{
    setDesign();
}
S_Snow::S_Snow(QGraphicsItem *parent) : Surface(0, 0, parent)
{
    setDesign();
}

void S_Snow::setDesign()
{
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::white);

    setBrush(brush);
}
