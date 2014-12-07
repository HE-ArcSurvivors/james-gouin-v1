#ifndef B_MOVABLE_H
#define B_MOVABLE_H
#include "block.h"
#include <QGraphicsRectItem>
#include <QGraphicsScene>
class B_Movable : public Block
{
public:
    B_Movable(int xpos, int ypos, QGraphicsItem *parent = 0);
    void addToScene(QGraphicsScene*);

    void moveBy(int, int);

    bool IsMovableToLeft();
    bool IsMovableToRight();
    bool IsMovableToBottom();
    bool IsMovableToTop();

private:
    QGraphicsRectItem *leftCollideBox;
    QGraphicsRectItem *rightCollideBox;
    QGraphicsRectItem *bottomCollideBox;
    QGraphicsRectItem *topCollideBox;

    bool IsMovable(QList<QGraphicsItem *>);


};

#endif // B_MOVABLE_H
