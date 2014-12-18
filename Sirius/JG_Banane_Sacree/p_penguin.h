#ifndef P_PINGOUIN_H
#define P_PINGOUIN_H
#include "player.h"
#include "object.h"
#include <QList>

class QGraphicsItem;
class QPoint;
class QGraphicsScene;

class Pingouin  : public Player
{
private:

    QGraphicsRectItem *leftCollideBox;
    QGraphicsRectItem *rightCollideBox;
    QGraphicsRectItem *bottomCollideBox;
    QGraphicsRectItem *topCollideBox;

    int gameSquare;

    QList<Object *> sacoche;
    QPoint* lastMove;

public:
    Pingouin(int gameSquare);

    void setPos(int, int);
    void moveBy(int, int);
    void moveBack();

    void addToScene(QGraphicsScene*);
    void addObjectToSacoche(Object *object);
    void removeObjectToSacoche(QString object);
    bool checkObjectSacoche(QString object);
    Object* getObjectSacoche();
    void printSacoche();

    bool isSlide();

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
