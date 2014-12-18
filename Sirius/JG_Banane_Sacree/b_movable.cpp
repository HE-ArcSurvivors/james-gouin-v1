#include <QBrush>
#include <QDebug>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QList>

#include "b_wall.h"
#include "b_movable.h"
#include "b_water.h"
#include "gameboard.h"

#include "s_ice.h"

#if defined(__unix__) || (defined(__APPLE__) && defined(__MACH__))
#else
#include <typeinfo.h>
#endif

B_Movable::B_Movable(int xpos, int ypos, QGraphicsItem *parent) : Surface(xpos, ypos, Gameboard::getGameSquares()-2, Gameboard::getGameSquares()-2, parent)
{
   setDesign(xpos, ypos);
   setZValue(1);
}

B_Movable::B_Movable(QGraphicsItem *parent) : Surface(0, 0, Gameboard::getGameSquares()-2, Gameboard::getGameSquares()-2, parent) //obligé de donner une position fictive
{
    setDesign(0, 0);
    setZValue(1);
}

void B_Movable::setPos(int x, int y)
{
    QGraphicsRectItem::setPos(x*Gameboard::getGameSquares()+1, y*Gameboard::getGameSquares()+1);
}

void B_Movable::setDesign(int xpos, int ypos)
{
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::gray);

    setBrush(brush);

    int size = Gameboard::getGameSquares();

    setPos(xpos,ypos);
    leftCollideBox = new QGraphicsRectItem(size*xpos-size+1, size*ypos+1,size-2, size-2);
    rightCollideBox = new QGraphicsRectItem(size*xpos+size+1, size*ypos+1,size-2, size-2);
    bottomCollideBox = new QGraphicsRectItem(size*xpos+1, size*ypos+size+1, size-2, size-2);
    topCollideBox = new QGraphicsRectItem(size*xpos+1, size*ypos-size+1, size-2, size-2);

    leftCollideBox->setPen(Qt::NoPen);
    rightCollideBox->setPen(Qt::NoPen);
    bottomCollideBox->setPen(Qt::NoPen);
    topCollideBox->setPen(Qt::NoPen);
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

void B_Movable::removeFromScene(QGraphicsScene* Scene)
{
    Scene->removeItem(this);
    Scene->removeItem(topCollideBox);
    Scene->removeItem(bottomCollideBox);
    Scene->removeItem(leftCollideBox);
    Scene->removeItem(rightCollideBox);
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
        if(typeid(*l.at(i)).name() == typeid(B_Water).name()) //&& !this->IsSunk
        {
            //this->IsSunk = true;
            bMove = true;
//            qDebug() << "on water";
        }
//        else if(this->IsSunk)
//        {
////            qDebug() << "blocked on water";
//            bMove = false;
//        }
    }
    return bMove;
}

bool B_Movable::isSlide()
{
    QList<QGraphicsItem *> CollidingItems = this->CollidesCenter();
    bool slide = false;

    for(int i=0; i<CollidingItems.length(); i++)
    {
        if(typeid(*CollidingItems.at(i)).name() == typeid(S_Ice).name())
        {
            slide = true;
        }
    }
    return slide;
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

QList<QGraphicsItem *> B_Movable::CollidesCenter(){
     return collidingItems();
}
