/*********************************************************************************
* Copyright © Haute-Ecole ARC - All Rights Reserved
* Copyright © Banana Rocket - All Rights Reserved
*
* This file is part of <P2 Qt Project: James Gouin et la Banane Sacrée>.
*
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Claret-Yakovenko Roman <romain.claret@rocla.ch>, 27 January 2015
* Written by Divernois Margaux <margaux.divernois@gmail.com>, 27 January 2015
* Written by Visinand Steve <visinandst@gmail.com>, 27 January 2015
**********************************************************************************/

#include "p_penguin.h"
#include "gameboard.h"
#include <QGraphicsRectItem>
#include <QPoint>
#include <QGraphicsScene>
#include <QList>
#include <QDebug>
#include "s_ice.h"
#include "object.h"

#include <QPropertyAnimation>

#if defined(__unix__) || (defined(__APPLE__) && defined(__MACH__))
#else
#include <typeinfo.h>
#endif

Pingouin::Pingouin() : Player()
{
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

    lastMove = new QPoint(0,0);

    slideAble = true;

}
void Pingouin::setPos(int x, int y)
{
    int xPos = x*Gameboard::getGameSquares()-Gameboard::getGameSquares();
    int yPos = y*Gameboard::getGameSquares()-Gameboard::getGameSquares();

    Player::setPos(xPos, yPos);

    leftCollideBox->setPos(xPos-Gameboard::getGameSquares()+1, yPos+1);
    rightCollideBox->setPos(xPos+Gameboard::getGameSquares()+1, yPos+1);
    bottomCollideBox->setPos(xPos+1, yPos+Gameboard::getGameSquares()+1);
    topCollideBox->setPos(xPos+1, yPos-Gameboard::getGameSquares()+1);
}

void Pingouin::moveBy(int x, int y)
{


//    QPropertyAnimation *animation = new QPropertyAnimation(this, "pos");
//    animation->setDuration(1000);
//    animation->setStartValue(QPoint(this->pos().x(), this->pos().y()));
//    animation->setEndValue(QPoint(this->pos().x() + x*gameSquare, this->pos().y() + y*gameSquare));

//    animation->start();

    Player::moveBy(x*Gameboard::getGameSquares(),y*Gameboard::getGameSquares());
    leftCollideBox->moveBy(x*Gameboard::getGameSquares(),y*Gameboard::getGameSquares());
    rightCollideBox->moveBy(x*Gameboard::getGameSquares(),y*Gameboard::getGameSquares());
    bottomCollideBox->moveBy(x*Gameboard::getGameSquares(),y*Gameboard::getGameSquares());
    topCollideBox->moveBy(x*Gameboard::getGameSquares(),y*Gameboard::getGameSquares());

    lastMove->setX(x);
    lastMove->setY(y);
}

void Pingouin::moveBack()
{
    moveBy(-lastMove->x(),-lastMove->y());
    lastMove->setX(0);
    lastMove->setY(0);

    qDebug() << "MoveBack" << x() << " " << y();
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

    if(slideAble)
    {
        for(int i=0; i<CollidingItems.length(); i++)
        {
            if(typeid(*CollidingItems.at(i)).name() == typeid(S_Ice).name())
            {
                slide = true;
            }
        }
    }
    return slide;
}

void Pingouin::setSlideAble(bool value)
{
    this->slideAble = value;
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

void Pingouin::addObjectToSacoche(Object *object)
{
    if(object->getName()=="Oeuf")
    {
        nbLives++;
    }
    else
    {
        tempSacoche.append(object);
        sacoche.append(object);
    }

}

void Pingouin::removeObjectFromSacoche(QString object)
{
    for (int i = 0; i < sacoche.size(); ++i)
    {
        if (sacoche.at(i)->getName() == object)
        {
            sacoche.removeAt(i);
            return;
        }
    }
}

void Pingouin::printSacoche()
{
    qDebug() << "[PrintSacoche]";
    for (int i = 0; i < sacoche.size(); ++i) {
        qDebug() << sacoche.at(i)->getName();
    }
    qDebug() << " ";

    qDebug() << "[PrintSacocheTemp]";
    for (int i = 0; i < tempSacoche.size(); ++i) {
        qDebug() << tempSacoche.at(i)->getName();
    }
    qDebug() << " ";
}

QList<Object*> Pingouin::getSacoche()
{
    return sacoche;
}

bool Pingouin::checkObjectSacoche(QString object, int quantity)
{
    int total = 0;
    for (int i = 0; i < sacoche.size(); ++i)
    {
        if (sacoche.at(i)->getName() == object)
        {
            total++;
        }
    }

    if(total >= quantity)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Pingouin::emptyTempSacoche()
{
    tempSacoche.clear();
}

void Pingouin::emptySacoche()
{
    sacoche.clear();
}

void Pingouin::removeTempFromSacoche()
{
    for (int i = 0; i < tempSacoche.size(); ++i)
    {
        qDebug() << "Remove : " << tempSacoche.at(i)->getName();
        QString nom = tempSacoche.at(i)->getName();
        removeObjectFromSacoche(nom);
    }
    emptyTempSacoche();
}

QGraphicsRectItem* Pingouin::getCollideBloc(char sensDepl)
{
    if(sensDepl == 'b')
    {
        return bottomCollideBox;
    }
    else if(sensDepl == 'l')
    {
        return leftCollideBox;
    }
    else if(sensDepl == 'r')
    {
        return rightCollideBox;
    }
    else if(sensDepl == 't')
    {
        return topCollideBox;
    }
    return NULL;
}
