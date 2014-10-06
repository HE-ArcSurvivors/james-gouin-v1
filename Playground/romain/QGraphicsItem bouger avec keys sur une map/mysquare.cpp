#include "mysquare.h"

//http://doc.qt.digia.com/4.6/qt.html#Key-enum

MySquare::MySquare()
{
    Pressed = false;
    setFlag(ItemIsMovable);
}

QRectF MySquare::boundingRect() const
{
    return QRectF(0,0,30,30);
}

void MySquare::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rec = boundingRect();
    QBrush brush(Qt::blue);

    if(Pressed)
    {
        brush.setColor(Qt::red);
    }
    else
    {
        brush.setColor(Qt::green);
    }

    painter->fillRect(rec,brush);
    //painter->drawEllipse(rec);
    painter->drawRect(rec);
}

void MySquare::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Pressed = true;
    update();
    QGraphicsItem::mousePressEvent(event);
}

void MySquare::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    Pressed = false;
    update();
    QGraphicsItem::mouseReleaseEvent(event);
}
