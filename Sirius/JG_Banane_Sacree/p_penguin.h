#ifndef P_PINGOUIN_H
#define P_PINGOUIN_H
#include "player.h"

#include "qgraphicsitem.h"
#include "qpoint.h"
#include "qgraphicsscene.h"

class Pingouin  : public Player
{
private:

    QGraphicsRectItem *leftCollideBox;
    QGraphicsRectItem *rightCollideBox;
    QGraphicsRectItem *bottomCollideBox;
    QGraphicsRectItem *topCollideBox;

    int gameSquare = 32;

//    bool IsMovable(QList<QGraphicsItem *>);

public:
    Pingouin(int gameSquare);

    void setPos(int, int);
    void moveBy(int, int);

    void addToScene(QGraphicsScene*);

//    bool IsMovableToLeft();
//    bool IsMovableToRight();
//    bool IsMovableToBottom();
//    bool IsMovableToTop();

    QList<QGraphicsItem *> CollidesRight();
    QList<QGraphicsItem *> CollidesLeft();
    QList<QGraphicsItem *> CollidesTop();
    QList<QGraphicsItem *> CollidesBottom();
    QList<QGraphicsItem *> CollidesCenter();

    //temporaire
    QGraphicsRectItem* getLeftCB();
    QGraphicsRectItem* getRightCB();
    QGraphicsRectItem* getTopCB();
    QGraphicsRectItem* getBottomCB();
    Player* getPlayer();

};

#endif // P_PINGOUIN_H
