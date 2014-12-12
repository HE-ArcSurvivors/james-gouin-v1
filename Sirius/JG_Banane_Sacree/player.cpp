#include "player.h"
#include "gameboard.h"

#include <QPainter>
#include <QGraphicsItem>
#include <QDebug>

Player::Player()
{
    leftSkin = ":/characters/characters/player_left.png";
    rightSkin = ":/characters/characters/player_right.png";
    upSkin = ":/characters/characters/player_front.png";
    downSkin = ":/characters/characters/player_front.png";
    playerOrientation = "down"; //Orientation de depart du joueur

    setZValue(2);
}

QRectF Player::boundingRect() const
{
    return QRectF(1,1,Gameboard::getGameSquares()-2,Gameboard::getGameSquares()-2);
}

void Player::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    playerSkin = new QBrush();

    //Set playerSkin texture depending on player's orientation
    if (playerOrientation == "left"){
        playerSkin->setTexture(QPixmap(leftSkin));
    }
    if (playerOrientation == "right"){
        playerSkin->setTexture(QPixmap(rightSkin));
    }
    if (playerOrientation == "up"){
        playerSkin->setTexture(QPixmap(upSkin));
    }
    if (playerOrientation == "down"){
        playerSkin->setTexture(QPixmap(downSkin));
    }

    QRectF playerBox = boundingRect();  //Setting player's box

    painter->setPen(Qt::transparent);   //Le coutour du joueur
    painter->fillRect(playerBox,*playerSkin);   //charger la couleur
    painter->drawRect(playerBox);   //dessiner le joueur
}

void Player::setPlayerOrientation(QString orientation)
{
    playerOrientation = orientation;
}
