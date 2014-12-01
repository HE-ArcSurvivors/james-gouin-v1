#ifndef VIEWTRANSITIONSURFACE_H
#define VIEWTRANSITIONSURFACE_H

#include <QGraphicsItem>
#include <QPainter>

class ViewTransitionSurface : public QGraphicsItem
{
public:
    ViewTransitionSurface();
    QRectF boundingRect() const;    //la box du player
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget); //paint event
    QBrush *surfaceSkin;

    int getSurfaceSizeX();
    int getSurfaceSizeY();

private:
    //J'ai essayé de changer la taille de la box dynamiquement selon l'image,
    //mais le probleme est qu'il y a des bugs graphiques inGame, l'image qui se decompose..
    int surfaceSizeX = 30;
    int surfaceSizeY = 30;
};

#endif // VIEWTRANSITIONSURFACE_H
