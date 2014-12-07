#include "block.h"
#include <QGraphicsRectItem>

Block::Block(int xpos, int ypos, QGraphicsItem *parent) : QGraphicsRectItem(0,0,32,32,parent)
{
    //setRect(xpos*gameSquare-gameSquare, ypos*gameSquare-gameSquare, width, height);
    setPos(xpos, ypos);
}

Block::~Block(){}

void Block::setPos(int x, int y)
{
    QGraphicsRectItem::setPos(x*gameSquare-gameSquare, y*gameSquare-gameSquare);
}

int Block::getWidth(){
    return width;
}
int Block::getHeight(){
    return height;
}
int Block::getGameSquare(){
    return gameSquare;
}
