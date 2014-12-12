#include "p_penguin.h"
#include "gameboard.h"
#include <QGraphicsRectItem>
#include <QPoint>
#include <QGraphicsScene>
#include <QList>
#include <QDebug>
#include "s_ice.h"
#include "object.h"

#if defined(__unix__) || (defined(__APPLE__) && defined(__MACH__))
#else
#include <typeinfo.h>
#endif

Pingouin::Pingouin(int gameSquare) : Player()
{
    this->gameSquare = gameSquare;

    int BlocsSizeX = Gameboard::getGameSquares()-2;
    int BlocsSizeY = Gameboard::getGameSquares()-2;

    leftCollideBox = new QGraphicsRectItem(0,0,BlocsSizeX,BlocsSizeY);
    rightCollideBox = new QGraphicsRectItem(0,0,BlocsSizeX,BlocsSizeY);
    bottomCollideBox = new QGraphicsRectItem(0,0,BlocsSizeX,BlocsSizeY);
    topCollideBox = new QGraphicsRectItem(0,0,BlocsSizeX,BlocsSizeY);

    leftCollideBox->setPen(Qt::NoPen);
    rightCollideBox->setPen(Qt::NoPen);
    bottomCollideBox->setPen(Qt::NoPen);
    topCollideBox->setPen(Qt::NoPen);

}
void Pingouin::setPos(int x, int y)
{
    int xPos = x*gameSquare-gameSquare;
    int yPos = y*gameSquare-gameSquare;

    Player::setPos(xPos, yPos);

    leftCollideBox->setPos(xPos-Gameboard::getGameSquares()+1, yPos+1);
    rightCollideBox->setPos(xPos+Gameboard::getGameSquares()+1, yPos+1);
    bottomCollideBox->setPos(xPos+1, yPos+Gameboard::getGameSquares()+1);
    topCollideBox->setPos(xPos+1, yPos-Gameboard::getGameSquares()+1);
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

bool Pingouin::isSlide()
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


void Pingouin::addObjectToSacoche(QGraphicsItem *object)
{
    sacoche.append(object);
}

void Pingouin::printSacoche()
{
    qDebug() << "PrintSacoche";
    for (int i = 0; i < sacoche.size(); ++i) {
        qDebug() << sacoche.at(i);
    }
}

