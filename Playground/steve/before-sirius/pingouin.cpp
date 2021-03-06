#include "pingouin.h"

#include <QGraphicsRectItem>
#include <QPoint>
#include <QGraphicsScene>
#include <QBrush>
#include <QDebug>

//inclusion des surfaces
//#include "neige.h"

Pingouin::Pingouin(int gameSquare) : Player()
{
    this->gameSquare = gameSquare;

    int BlocsSizeX = playerSizeX-2;
    int BlocsSizeY = playerSizeY-2;

    leftCollideBox = new QGraphicsRectItem(0,0,BlocsSizeX,BlocsSizeY);
    rightCollideBox = new QGraphicsRectItem(0,0,BlocsSizeX,BlocsSizeY);
    bottomCollideBox = new QGraphicsRectItem(0,0,BlocsSizeX,BlocsSizeY);
    topCollideBox = new QGraphicsRectItem(0,0,BlocsSizeX,BlocsSizeY);

}
void Pingouin::setPos(int x, int y)
{
    int xPos = x*gameSquare-gameSquare;
    int yPos = y*gameSquare-gameSquare;

    Player::setPos(xPos, yPos);

    leftCollideBox->setPos(xPos-playerSizeX+1, yPos+1);
    rightCollideBox->setPos(xPos+playerSizeX+1, yPos+1);
    bottomCollideBox->setPos(xPos+1, yPos+playerSizeY+1);
    topCollideBox->setPos(xPos+1, yPos-playerSizeY+1);
}

void Pingouin::moveBy(int x, int y)
{
    Player::moveBy(x*gameSquare,y*gameSquare);
    leftCollideBox->moveBy(x*gameSquare,y*gameSquare);
    rightCollideBox->moveBy(x*gameSquare,y*gameSquare);
    bottomCollideBox->moveBy(x*gameSquare,y*gameSquare);
    topCollideBox->moveBy(x*gameSquare,y*gameSquare);
}

void Pingouin::addToScene(QGraphicsScene* Scene)
{
    Scene->addItem(this);
    Scene->addItem(topCollideBox);
    Scene->addItem(bottomCollideBox);
    Scene->addItem(leftCollideBox);
    Scene->addItem(rightCollideBox);
}


//bool Pingouin::IsMovable(QList<QGraphicsItem *> l)
//{
//    bool bMove = true;
//    for(int i=0; i<l.length(); i++)
//    {
//        //QMessageBox m;
//        //m.setText(typeid(*CollidesRight.at(i)).name());
//        //m.exec();

//        if(typeid(*l.at(i)).name() == typeid(Neige).name())
//        {
//            bMove = false;
//        }
//    }
//    return bMove;
//}

//bool Pingouin::IsMovableToLeft()
//{
//    return IsMovable(leftCollideBox->collidingItems());
//}
//bool Pingouin::IsMovableToRight()
//{
//    return IsMovable(rightCollideBox->collidingItems());
//}
//bool Pingouin::IsMovableToBottom()
//{
//    return IsMovable(bottomCollideBox->collidingItems());
//}
//bool Pingouin::IsMovableToTop()
//{
//    return IsMovable(topCollideBox->collidingItems());
//}

//Retour des listes des collisions
QList<QGraphicsItem *> Pingouin::CollidesRight()
{
    return rightCollideBox->collidingItems();
}
QList<QGraphicsItem *> Pingouin::CollidesLeft()
{
    return leftCollideBox->collidingItems();
}
QList<QGraphicsItem *> Pingouin::CollidesTop()
{
    return topCollideBox->collidingItems();
}
QList<QGraphicsItem *> Pingouin::CollidesBottom()
{
    return bottomCollideBox->collidingItems();
}
QList<QGraphicsItem *> Pingouin::CollidesCenter()
{
    return Player::collidingItems();
}


//temporaire
QGraphicsRectItem* Pingouin::getLeftCB(){
    return leftCollideBox;
}
QGraphicsRectItem* Pingouin::getRightCB(){
     return rightCollideBox;
}
QGraphicsRectItem* Pingouin::getTopCB(){
     return topCollideBox;
}
QGraphicsRectItem* Pingouin::getBottomCB(){
     return bottomCollideBox;
}
Player* Pingouin::getPlayer(){
     return this;
}
