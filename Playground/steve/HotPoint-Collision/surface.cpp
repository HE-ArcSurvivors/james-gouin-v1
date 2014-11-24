#include "surface.h"
#include <QGraphicsRectItem>

surface::surface(qreal xpos, qreal ypos, QGraphicsItem *parent)
    : QGraphicsRectItem(xpos, ypos, 50, 50, parent)
{
}

surface::~surface(){}
