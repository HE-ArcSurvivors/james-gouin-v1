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

    int getPlayerSizeX();
    int getPlayerSizeY();

    void setPlayerOrientation(QString orientation);

protected:
    //J'ai essayé de changer la taille de la box dynamiquement selon l'image,
    //mais le probleme est qu'il y a des bugs graphiques inGame, l'image qui se decompose..
    int playerSizeX = 32;
    int playerSizeY = 32;

    int xPos;
    int yPos;
private:
    //Les skins sont les images attribué au personnage
    QString leftSkin = ":/characters/characters/player_left.png";
    QString rightSkin = ":/characters/characters/player_right.png";
    QString upSkin = ":/characters/characters/player_front.png";
    QString downSkin = ":/characters/characters/player_front.png";
    QString playerOrientation;

};

#endif // PLAYER_H
