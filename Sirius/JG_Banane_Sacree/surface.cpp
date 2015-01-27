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

#include "surface.h"
#include "gameboard.h"
#include <QGraphicsItem>
#include <QPoint>
#include <QPen>

#include <QDebug>

Surface::Surface(int xpos, int ypos, QGraphicsItem *parent) : QGraphicsRectItem(0, 0, Gameboard::getGameSquares(), Gameboard::getGameSquares(), parent)
{
    setPen(Qt::NoPen);
    setPos(xpos, ypos);
}
Surface::Surface(int xpos, int ypos, int width, int height, QGraphicsItem *parent) : QGraphicsRectItem(0, 0, width, height, parent)
{
    setPen(Qt::NoPen);
    setPos(xpos, ypos);
}
Surface::~Surface(){}

void Surface::setPos(int x, int y)
{
    QGraphicsRectItem::setPos(x*Gameboard::getGameSquares(), y*Gameboard::getGameSquares());
}
QPoint Surface::getPos()
{
    return QPoint(this->pos().x()/Gameboard::getGameSquares(), this->pos().y()/Gameboard::getGameSquares());
}

void Surface::setColor(QString brushColor)
{
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(brushColor);
    setBrush(brush);
}
