#ifndef PINGOUIN_H
#define PINGOUIN_H
#include "player.h"
#include <QGraphicsRectItem>
#include <QPoint>
#include <QGraphicsScene>

class pingouin
{
private:
    Player *player;

    QGraphicsRectItem *leftCollideBox;
    QGraphicsRectItem *rightCollideBox;
    QGraphicsRectItem *bottomCollideBox;
    QGraphicsRectItem *topCollideBox;

    int gameSquare = 32;

public:
    pingouin(int gameSquare);

    void moveBy(int, int);
    void setPos(int, int);
    QPoint pos();
    void addToScene(QGraphicsScene*);
    void setPlayerOrientation(QString);


    QGraphicsRectItem* getLeftCB();
    QGraphicsRectItem* getRightCB();
    QGraphicsRectItem* getTopCB();
    QGraphicsRectItem* getBottomCB();

    Player* getPlayer();

};

#endif // PINGOUIN_H
