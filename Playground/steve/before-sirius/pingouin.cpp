#include "pingouin.h"
#include <QPen>
#include <QBrush>
#include <QDebug>
Pingouin::Pingouin(int gameSquare)
{
    this->gameSquare = gameSquare;
    player = new Player();

    int BlocsSizeX = player->getPlayerSizeX() - 2;
    int BlocsSizeY = player->getPlayerSizeY() - 2;

    leftCollideBox = new QGraphicsRectItem(0,0,BlocsSizeX,BlocsSizeY);
    rightCollideBox = new QGraphicsRectItem(0,0,BlocsSizeX,BlocsSizeY);
    bottomCollideBox = new QGraphicsRectItem(0,0,BlocsSizeX,BlocsSizeY);
    topCollideBox = new QGraphicsRectItem(0,0,BlocsSizeX,BlocsSizeY);


    QBrush brush(Qt::blue);
    leftCollideBox->setBrush(brush);
    rightCollideBox->setBrush(brush);
    topCollideBox->setBrush(brush);
    bottomCollideBox->setBrush(brush);

}
void Pingouin::setPos(int x, int y)
{
    int xPos = x*gameSquare-gameSquare;
    int yPos = y*gameSquare-gameSquare;

    int playerSizeX = player->getPlayerSizeX();
    int playerSizeY = player->getPlayerSizeY();

    player->setPos(xPos, yPos);

    leftCollideBox->setPos(xPos-playerSizeX+1, yPos+1);
    rightCollideBox->setPos(xPos+playerSizeX+1, yPos+1);
    bottomCollideBox->setPos(xPos+1, yPos+playerSizeY+1);
    topCollideBox->setPos(xPos+1, yPos-playerSizeY+1);
}

void Pingouin::moveBy(int x, int y)
{
    player->moveBy(x*gameSquare,y*gameSquare);
    leftCollideBox->moveBy(x*gameSquare,y*gameSquare);
    rightCollideBox->moveBy(x*gameSquare,y*gameSquare);
    bottomCollideBox->moveBy(x*gameSquare,y*gameSquare);
    topCollideBox->moveBy(x*gameSquare,y*gameSquare);
}

QPoint Pingouin::pos()
{
    return QPoint(player->pos().x(), player->pos().y());
}

void Pingouin::addToScene(QGraphicsScene* Scene)
{
    Scene->addItem(player);
    Scene->addItem(topCollideBox);
    Scene->addItem(bottomCollideBox);
    Scene->addItem(leftCollideBox);
    Scene->addItem(rightCollideBox);
}
void Pingouin::setPlayerOrientation(QString orientation)
{
    player->Player::setPlayerOrientation(orientation);
}


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
    return player->collidingItems();
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
     return player;
}
