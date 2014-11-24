#include "neige.h"
#include <QtWidgets>

neige::neige(qreal xpos, qreal ypos, QGraphicsItem *parent) : surface(xpos, ypos, parent)
{

    QPen pen;
    pen.setWidth(1);
    pen.setBrush(Qt::black);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::blue);

    setBrush(brush);
    setPen(pen);
}
