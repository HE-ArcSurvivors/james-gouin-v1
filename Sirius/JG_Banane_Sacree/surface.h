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

#ifndef SURFACE_H
#define SURFACE_H

#include <QGraphicsRectItem>
class QPoint;

class Surface : public QGraphicsRectItem
{
public:
    Surface(int xpos, int ypos, QGraphicsItem *parent = 0);
    Surface(int xpos, int ypos, int width, int height, QGraphicsItem *parent = 0);
    ~Surface();
    void setPos(int, int);
    QPoint getPos();
    void setColor(QString brushColor);
};

#endif // SURFACE_H
