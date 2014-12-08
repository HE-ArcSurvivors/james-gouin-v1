
#include <QBrush>
#include <QDebug>
#include <QGraphicsRectItem>
#include <QGraphicsScene>

#include "b_wall.h"
#include "b_movable.h"

B_Movable::B_Movable(int xpos, int ypos, QGraphicsItem *parent) : Surface(xpos, ypos, parent)
{
   setDesign(xpos, ypos);
}

B_Movable::B_Movable(QGraphicsItem *parent) : Surface(0, 0, parent) //obligé de donner une position fictive
{
    setDesign(0, 0);
}

void B_Movable::setDesign(int xpos, int ypos)
{
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::gray);

    setBrush(brush);

    int BlocsSizeY = getHeight();
    int BlocsSizeX = getWidth();
    int gameSquare = getGameSquare();

    leftCollideBox = new QGraphicsRectItem(gameSquare*xpos-BlocsSizeX+1, gameSquare*ypos+1,BlocsSizeX-2, BlocsSizeY-2);
    rightCollideBox = new QGraphicsRectItem(gameSquare*xpos+BlocsSizeX+1, gameSquare*ypos+1,BlocsSizeX-2, BlocsSizeY-2);
    bottomCollideBox = new QGraphicsRectItem(gameSquare*xpos+1, gameSquare*ypos+BlocsSizeY+1, BlocsSizeX-2, BlocsSizeY-2);
    topCollideBox = new QGraphicsRectItem(gameSquare*xpos+1, gameSquare*ypos-BlocsSizeY+1, BlocsSizeX-2, BlocsSizeY-2);
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


