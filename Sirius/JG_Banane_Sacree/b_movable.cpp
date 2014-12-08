#include <QBrush>
#include <QDebug>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include "b_wall.h"
#include "b_movable.h"
#include "gameboard.h"

#if defined(__unix__) || (defined(__APPLE__) && defined(__MACH__))
#else
#include <typeinfo.h>
#endif

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

    int size = Gameboard::getGameSquares();

    leftCollideBox = new QGraphicsRectItem(size*xpos-size+1, size*ypos+1,size-2, size-2);
    rightCollideBox = new QGraphicsRectItem(size*xpos+size+1, size*ypos+1,size-2, size-2);
    bottomCollideBox = new QGraphicsRectItem(size*xpos+1, size*ypos+size+1, size-2, size-2);
    topCollideBox = new QGraphicsRectItem(size*xpos+1, size*ypos-size+1, size-2, size-2);
}

void B_Movable::moveBy(int x, int y)
{
    int gameSquare = Gameboard::getGameSquares();

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


