#include "blocdeplacable.h"
#include <QBrush>
#include <QDebug>

#include "neige.h"

BlocDeplacable::BlocDeplacable(int xpos, int ypos, QGraphicsItem *parent) : Surface(xpos, ypos, parent)
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

void BlocDeplacable::moveBy(int x, int y)
{
    int gameSquare = getGameSquare();

    QGraphicsRectItem::moveBy(x*gameSquare,y*gameSquare);
    leftCollideBox->moveBy(x*gameSquare,y*gameSquare);
    rightCollideBox->moveBy(x*gameSquare,y*gameSquare);
    bottomCollideBox->moveBy(x*gameSquare,y*gameSquare);
    topCollideBox->moveBy(x*gameSquare,y*gameSquare);
}

void BlocDeplacable::addToScene(QGraphicsScene* Scene)
{
    Scene->addItem(this);
    Scene->addItem(topCollideBox);
    Scene->addItem(bottomCollideBox);
    Scene->addItem(leftCollideBox);
    Scene->addItem(rightCollideBox);
}

bool BlocDeplacable::IsMovable(QList<QGraphicsItem *> l)
{
    bool bMove = true;
    for(int i=0; i<l.length(); i++)
    {
        if(typeid(*l.at(i)).name() == typeid(Neige).name())
        {
            bMove = false;
        }
        if(typeid(*l.at(i)).name() == typeid(BlocDeplacable).name())
        {
            bMove = false;
        }
    }
    return bMove;
}
bool BlocDeplacable::IsMovableToLeft(){
    return IsMovable(leftCollideBox->collidingItems());
}
bool BlocDeplacable::IsMovableToRight(){
    return IsMovable(rightCollideBox->collidingItems());
}
bool BlocDeplacable::IsMovableToBottom(){
    return IsMovable(bottomCollideBox->collidingItems());
}
bool BlocDeplacable::IsMovableToTop(){
    return IsMovable(topCollideBox->collidingItems());
}


