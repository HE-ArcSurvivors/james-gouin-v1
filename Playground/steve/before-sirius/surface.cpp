#include "surface.h"
#include <QGraphicsRectItem>

surface::surface(int xpos, int ypos, QGraphicsItem *parent)
    : QGraphicsRectItem(0, 0, 32, 32, parent)
{
    setPos(xpos, ypos);
}

surface::~surface(){}

void surface::setPos(int x, int y)
{
    QGraphicsRectItem::setPos(x*gameSquare-gameSquare, y*gameSquare-gameSquare);
}
