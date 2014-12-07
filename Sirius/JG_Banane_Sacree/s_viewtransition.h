#ifndef S_VIEWTRANSITION_H
#define S_VIEWTRANSITION_H

#include <QGraphicsItem>
#include <QPainter>

class S_ViewTransition : public QGraphicsItem
{
public:
    S_ViewTransition();
    QRectF boundingRect() const;    //la box du player
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget); //paint event
    QBrush *surfaceSkin;

    int getSurfaceSizeX();
    int getSurfaceSizeY();

private:
    int surfaceSizeX = 30;
    int surfaceSizeY = 30;
};

#endif // S_VIEWTRANSITION_H
