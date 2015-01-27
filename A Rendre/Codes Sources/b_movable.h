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

#ifndef B_MOVABLE_H
#define B_MOVABLE_H
#include "surface.h"
#include <QList>

class QGraphicsRectItem;
class QGraphicsScene;


class B_Movable : public Surface
{
public:
    B_Movable(int xpos, int ypos, QGraphicsItem *parent = 0);
    B_Movable(QGraphicsItem *parent = 0);

    void addToScene(QGraphicsScene*);
    void removeFromScene(QGraphicsScene*);

    void moveBy(int, int);
    void setPos(int, int);

    bool IsMovableToLeft();
    bool IsMovableToRight();
    bool IsMovableToBottom();
    bool IsMovableToTop();

    bool isSlide();

    QList<QGraphicsItem *> CollidesCenter();
    QGraphicsRectItem* getCollideBlocPosition(char sens);

    QGraphicsRectItem *leftCollideBox;
    QGraphicsRectItem *rightCollideBox;
    QGraphicsRectItem *bottomCollideBox;
    QGraphicsRectItem *topCollideBox;

private:

    bool IsMovable(QList<QGraphicsItem *>);
    void setDesign(int xpos, int ypos);


};

#endif // B_MOVABLE_H
