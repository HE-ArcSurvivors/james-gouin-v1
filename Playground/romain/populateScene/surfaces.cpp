#include "surfaces.h"

Surfaces::Surfaces()
{
}

QRectF Surfaces::boundingRect() const
{
    return QRectF(0,0,surfaceSizeX,surfaceSizeY);
}

void Surfaces::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
//    surfaceSkin = new QBrush();//Qt::blue);
    surfaceSkin = new QBrush(Qt::red);

    QRectF surfaceBox = boundingRect();  //Setting player's box

    painter->setPen(Qt::transparent);   //Le coutour du joueur
    painter->fillRect(surfaceBox,*surfaceSkin);   //charger la couleur
    painter->drawRect(surfaceBox);   //dessiner le joueur
}
