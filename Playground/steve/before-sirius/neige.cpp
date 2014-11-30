#include "neige.h"
#include <QtWidgets>

neige::neige(int xpos, int ypos, QGraphicsItem *parent) : surface(xpos, ypos, parent)
{

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::white);

    setBrush(brush);
}
