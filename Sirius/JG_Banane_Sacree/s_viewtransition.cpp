#include "s_viewtransition.h"

#include <QGraphicsItem>
#include <QBrush>

S_ViewTransition::S_ViewTransition(int xpos, int ypos, QGraphicsItem *parent) : Surface(xpos, ypos, parent)
{
    setDesign();
    levelEnd = false;
    nextLevel = 0;
    neededItem = new QString("");
    needItem = false;

    setZValue(99);
}
S_ViewTransition::S_ViewTransition(QGraphicsItem *parent) : Surface(0, 0, parent)
{
    setDesign();
}

void S_ViewTransition::setDesign()
{
//    QBrush brush;
//    brush.setStyle(Qt::Dense7Pattern);
//    brush.setColor(Qt::blue);
//    setBrush(brush);
}

bool S_ViewTransition::isEndLevel()
{
    return this->levelEnd;
}

void S_ViewTransition::setLevelEnd(bool value)
{
    this->levelEnd = value;
}

void S_ViewTransition::setNeededItem(QString value)
{
    this->needItem = true;
    this->neededItem = new QString(value);
}

QString* S_ViewTransition::getNeededItem()
{
    return this->neededItem;
}

bool S_ViewTransition::isNeedingItem()
{
    return this->needItem;
}

void S_ViewTransition::setNbItem(int nb)
{
    this->nbItem = nb;
}

int S_ViewTransition::getNbItem()
{
    return this->nbItem;
}

void S_ViewTransition::setNextLevel(int nb)
{
    this->nextLevel = nb;
}

int S_ViewTransition::getNextLevel()
{
    return this->nextLevel;
}
