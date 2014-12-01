#ifndef BLOCDEPLACABLE_H
#define BLOCDEPLACABLE_H
#include "surface.h"
#include <QGraphicsRectItem>
#include <QGraphicsScene>
class BlocDeplacable : public Surface
{
public:
    BlocDeplacable(int xpos, int ypos, QGraphicsItem *parent = 0);
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

#endif // BLOCDEPLACABLE_H
