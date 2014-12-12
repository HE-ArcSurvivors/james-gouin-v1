#ifndef B_MOVABLE_H
#define B_MOVABLE_H
#include "surface.h"

#include "qgraphicsitem.h"
#include "qgraphicsscene.h"
#include "qlist.h"

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

    QList<QGraphicsItem *> CollidesCenter();

private:
    QGraphicsRectItem *leftCollideBox;
    QGraphicsRectItem *rightCollideBox;
    QGraphicsRectItem *bottomCollideBox;
    QGraphicsRectItem *topCollideBox;

    bool IsMovable(QList<QGraphicsItem *>);

    void setDesign(int xpos, int ypos);


};

#endif // B_MOVABLE_H
