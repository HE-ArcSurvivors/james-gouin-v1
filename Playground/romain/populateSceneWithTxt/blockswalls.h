#ifndef BLOCKSWALLS_H
#define BLOCKSWALLS_H

#include <QGraphicsItem>
#include <QPainter>

class BlocksWalls : public QGraphicsItem
{
public:
    BlocksWalls();
    BlocksWalls(QString type);
    QRectF boundingRect() const;    //la box du player
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget); //paint event
    QBrush *surfaceSkin;

    void setType(QString type);

    int getSurfaceSizeX();
    int getSurfaceSizeY();

private:
    int surfaceSizeX = 29;
    int surfaceSizeY = 29;
    QString type = "test";
};

#endif // BLOCKSWALLS_H

