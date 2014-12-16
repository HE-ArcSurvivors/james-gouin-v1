#ifndef PLAYER_H
#define PLAYER_H

#include "qpainter.h"
#include "qgraphicsitem.h"

class Player : public QGraphicsItem
{
public:
    Player();

    QRectF boundingRect() const;    //la box du player

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget); //paint event
    QBrush *playerSkin;

    void setPlayerOrientation(QString orientation);
    QString getPlayerOrientation();
    QPoint *getPos();

protected:
    int xPos;
    int yPos;

private:
    //Les skins sont les images attribué au personnage
    QString leftSkin;
    QString rightSkin;
    QString upSkin;
    QString downSkin;
    QString playerOrientation;

};

#endif // PLAYER_H
