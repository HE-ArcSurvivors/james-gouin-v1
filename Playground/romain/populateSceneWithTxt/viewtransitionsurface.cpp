#include "viewtransitionsurface.h"

ViewTransitionSurface::ViewTransitionSurface()
{
}

QRectF ViewTransitionSurface::boundingRect() const
{
    return QRectF(0,0,surfaceSizeX,surfaceSizeY);
}

void ViewTransitionSurface::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
//    surfaceSkin = new QBrush();//Qt::blue);
    surfaceSkin = new QBrush(Qt::blue);

    QRectF surfaceBox = boundingRect();  //Setting player's box

    painter->setPen(Qt::transparent);   //Le coutour du joueur
    painter->fillRect(surfaceBox,*surfaceSkin);   //charger la couleur
    painter->drawRect(surfaceBox);   //dessiner le joueur
}

int ViewTransitionSurface::getSurfaceSizeX()
{
    return surfaceSizeX;
}

int ViewTransitionSurface::getSurfaceSizeY()
{
    return surfaceSizeY;
}
