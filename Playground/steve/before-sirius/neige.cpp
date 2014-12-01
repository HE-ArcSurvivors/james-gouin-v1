#include "neige.h"
#include <QBrush>

Neige::Neige(int xpos, int ypos, QGraphicsItem *parent) : Surface(xpos, ypos, parent)
{

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::white);

    setBrush(brush);
}
