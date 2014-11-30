#ifndef PLAYER_H
#define PLAYER_H

#include <QPainter>
#include <QGraphicsItem>

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

private:
    //J'ai essayé de changer la taille de la box dynamiquement selon l'image,
    //mais le probleme est qu'il y a des bugs graphiques inGame, l'image qui se decompose..
    int playerSizeX = 32;
    int playerSizeY = 32;

    int xPos;
    int yPos;

    //Les skins sont les images attribué au personnage
    QString leftSkin = ":/images/Pingouin_de_Profil_gauche.png";
    QString rightSkin = ":/images/Pingouin_de_Profil_droite.png";
    QString upSkin = ":/images/James Gouin de Face V1.png";
    QString downSkin = ":/images/James Gouin de Face V1.png";
    QString playerOrientation;

};

#endif // PLAYER_H
