#include "s_viewtransition.h"

S_ViewTransition::S_ViewTransition()
{
}

QRectF S_ViewTransition::boundingRect() const
{
    return QRectF(0,0,surfaceSizeX,surfaceSizeY);
}

void S_ViewTransition::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
//    surfaceSkin = new QBrush();//Qt::blue);
    surfaceSkin = new QBrush(Qt::blue);

    QRectF surfaceBox = boundingRect();  //Setting player's box

    painter->setPen(Qt::transparent);   //Le coutour du joueur
    painter->fillRect(surfaceBox,*surfaceSkin);   //charger la couleur
    painter->drawRect(surfaceBox);   //dessiner le joueur
}

int S_ViewTransition::getSurfaceSizeX()
{
    return surfaceSizeX;
}

int S_ViewTransition::getSurfaceSizeY()
{
    return surfaceSizeY;
}
