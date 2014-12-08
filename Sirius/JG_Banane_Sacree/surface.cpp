#include "surface.h"
#include "gameboard.h"
#include <QGraphicsItem>


Surface::Surface(int xpos, int ypos, QGraphicsItem *parent) : QGraphicsRectItem(0, 0, Gameboard::getGameSquares(), Gameboard::getGameSquares(), parent)
{
    setPos(xpos, ypos);
}

Surface::~Surface(){}

void Surface::setPos(int x, int y)
{
    QGraphicsRectItem::setPos(x*Gameboard::getGameSquares(), y*Gameboard::getGameSquares());
}
