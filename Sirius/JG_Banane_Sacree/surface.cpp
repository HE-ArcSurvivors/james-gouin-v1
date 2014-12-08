#include "surface.h"
#include <QGraphicsItem>

Surface::Surface(int xpos, int ypos, QGraphicsItem *parent) : QGraphicsRectItem(0, 0, 32, 32, parent) //HEY !?!?!
{
    setPos(xpos, ypos);
}

Surface::~Surface(){}

void Surface::setPos(int x, int y)
{
    QGraphicsRectItem::setPos(x*gameSquare, y*gameSquare);
}

int Surface::getWidth(){
    return width;
}
int Surface::getHeight(){
    return height;
}
int Surface::getGameSquare(){
    return gameSquare;
}
