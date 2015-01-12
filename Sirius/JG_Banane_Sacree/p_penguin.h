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
//    Q_PROPERTY(QPoint pos READ pos WRITE setPos)

private:

    QGraphicsRectItem *leftCollideBox;
    QGraphicsRectItem *rightCollideBox;
    QGraphicsRectItem *bottomCollideBox;
    QGraphicsRectItem *topCollideBox;

    int gameSquare;

    QList<Object *> sacoche;
    QList<Object *> tempSacoche;
    QPoint* lastMove;

    bool slideAble;

public:
    Pingouin(int gameSquare);

    void setPos(int, int);
    void moveBy(int, int);
    void moveBack();

    void addToScene(QGraphicsScene*);
    void addObjectToSacoche(Object *object);
    void removeObjectFromSacoche(QString object);
    void removeTempFromSacoche();
    bool checkObjectSacoche(QString object, int quantity = 1);
    QList<Object*> getSacoche();
    void printSacoche();
    void emptyTempSacoche();

    bool isSlide();
    void setSlideAble(bool value);

    QGraphicsRectItem* getCollideBloc(char sensDepl);

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
