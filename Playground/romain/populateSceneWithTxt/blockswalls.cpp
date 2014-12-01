#include "blockswalls.h"

BlocksWalls::BlocksWalls()
{

}

BlocksWalls::BlocksWalls(QString type)
{
    setType(type);
}

QRectF BlocksWalls::boundingRect() const
{
    return QRectF(0,0,surfaceSizeX,surfaceSizeY);
}

void BlocksWalls::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    surfaceSkin = new QBrush(Qt::transparent);//Qt::blue);
//    surfaceSkin = new QBrush(Qt::blue);

    QRectF surfaceBox = boundingRect();  //Setting player's box

    painter->setPen(Qt::transparent);   //Le coutour du joueur
    painter->fillRect(surfaceBox,*surfaceSkin);   //charger la couleur
    painter->drawRect(surfaceBox);   //dessiner le joueur
}

void BlocksWalls::setType(QString type)
{
    this->type = type;
}
