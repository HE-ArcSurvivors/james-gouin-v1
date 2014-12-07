#include "b_movable.h"
#include <QBrush>
#include <QDebug>

#include "b_wall.h"

B_Movable::B_Movable(int xpos, int ypos, QGraphicsItem *parent) : Block(xpos, ypos, parent)
{
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::gray);

    setBrush(brush);

    int BlocsSizeY = getHeight();
    int BlocsSizeX = getWidth();
    int gameSquare = getGameSquare();

    leftCollideBox = new QGraphicsRectItem(gameSquare*xpos-gameSquare-BlocsSizeX+1, gameSquare*ypos-gameSquare+1,BlocsSizeX-2, BlocsSizeY-2);
    rightCollideBox = new QGraphicsRectItem(gameSquare*xpos-gameSquare+BlocsSizeX+1, gameSquare*ypos-gameSquare+1,BlocsSizeX-2, BlocsSizeY-2);
    bottomCollideBox = new QGraphicsRectItem(gameSquare*xpos-gameSquare+1, gameSquare*ypos-gameSquare+BlocsSizeY+1, BlocsSizeX-2, BlocsSizeY-2);
    topCollideBox = new QGraphicsRectItem(gameSquare*xpos-gameSquare+1, gameSquare*ypos-gameSquare-BlocsSizeY+1, BlocsSizeX-2, BlocsSizeY-2);
}

void B_Movable::moveBy(int x, int y)
{
    int gameSquare = getGameSquare();

    QGraphicsRectItem::moveBy(x*gameSquare,y*gameSquare);
    leftCollideBox->moveBy(x*gameSquare,y*gameSquare);
    rightCollideBox->moveBy(x*gameSquare,y*gameSquare);
    bottomCollideBox->moveBy(x*gameSquare,y*gameSquare);
    topCollideBox->moveBy(x*gameSquare,y*gameSquare);
}

void B_Movable::addToScene(QGraphicsScene* Scene)
{
    Scene->addItem(this);
    Scene->addItem(topCollideBox);
    Scene->addItem(bottomCollideBox);
    Scene->addItem(leftCollideBox);
    Scene->addItem(rightCollideBox);
}

bool B_Movable::IsMovable(QList<QGraphicsItem *> l)
{
    bool bMove = true;
    for(int i=0; i<l.length(); i++)
    {
        if(typeid(*l.at(i)).name() == typeid(B_Wall).name())
        {
            bMove = false;
        }
        if(typeid(*l.at(i)).name() == typeid(B_Movable).name())
        {
            bMove = false;
        }
    }
    return bMove;
}
bool B_Movable::IsMovableToLeft(){
    return IsMovable(leftCollideBox->collidingItems());
}
bool B_Movable::IsMovableToRight(){
    return IsMovable(rightCollideBox->collidingItems());
}
bool B_Movable::IsMovableToBottom(){
    return IsMovable(bottomCollideBox->collidingItems());
}
bool B_Movable::IsMovableToTop(){
    return IsMovable(topCollideBox->collidingItems());
}


