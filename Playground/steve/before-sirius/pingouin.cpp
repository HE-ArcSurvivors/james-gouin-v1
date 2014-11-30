#include "pingouin.h"
#include <QPen>
#include <QBrush>
#include <QDebug>
pingouin::pingouin(int gameSquare)
{
    this->gameSquare = gameSquare;
    player = new Player();

    int playerSizeX = player->getPlayerSizeX();
    int playerSizeY = player->getPlayerSizeY();

    leftCollideBox = new QGraphicsRectItem(0,0,playerSizeX,playerSizeY);
    rightCollideBox = new QGraphicsRectItem(0,0,playerSizeX,playerSizeY);
    bottomCollideBox = new QGraphicsRectItem(0,0,playerSizeX,playerSizeY);
    topCollideBox = new QGraphicsRectItem(0,0,playerSizeX,playerSizeY);


    QBrush brush(Qt::blue);
    leftCollideBox->setBrush(brush);
    rightCollideBox->setBrush(brush);
    topCollideBox->setBrush(brush);
    bottomCollideBox->setBrush(brush);

}
void pingouin::setPos(int x, int y)
{
    int xPos = x*gameSquare-gameSquare;
    int yPos = y*gameSquare-gameSquare;

    int playerSizeX = player->getPlayerSizeX();
    int playerSizeY = player->getPlayerSizeY();

    player->setPos(xPos, yPos);

    leftCollideBox->setPos(xPos-playerSizeX, yPos);
    rightCollideBox->setPos(xPos+playerSizeX, yPos);
    bottomCollideBox->setPos(xPos, yPos+playerSizeY);
    topCollideBox->setPos(xPos, yPos-playerSizeY);
}

void pingouin::moveBy(int x, int y)
{
    player->moveBy(x*gameSquare,y*gameSquare);
    leftCollideBox->moveBy(x*gameSquare,y*gameSquare);
    rightCollideBox->moveBy(x*gameSquare,y*gameSquare);
    bottomCollideBox->moveBy(x*gameSquare,y*gameSquare);
    topCollideBox->moveBy(x*gameSquare,y*gameSquare);
}

QPoint pingouin::pos()
{
    return QPoint(player->pos().x(), player->pos().y());
}

void pingouin::addToScene(QGraphicsScene* Scene)
{
    Scene->addItem(player);
    Scene->addItem(topCollideBox);
    Scene->addItem(bottomCollideBox);
    Scene->addItem(leftCollideBox);
    Scene->addItem(rightCollideBox);
}
void pingouin::setPlayerOrientation(QString orientation)
{
    player->Player::setPlayerOrientation(orientation);
}

//temporaire
QGraphicsRectItem* pingouin::getLeftCB(){
    return leftCollideBox;
}
QGraphicsRectItem* pingouin::getRightCB(){
     return rightCollideBox;
}
QGraphicsRectItem* pingouin::getTopCB(){
     return topCollideBox;
}
QGraphicsRectItem* pingouin::getBottomCB(){
     return bottomCollideBox;
}
Player* pingouin::getPlayer(){
     return player;
}
