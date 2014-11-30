#include "player.h"
#include "gameboard.h"
#include <QDebug>

Player::Player()
{
    playerOrientation = "down"; //Orientation de depart du joueur
}

QRectF Player::boundingRect() const
{
    return QRectF(0,0,playerSizeX,playerSizeY);
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

int Player::getPlayerSizeX()
{
    return playerSizeX;
}

int Player::getPlayerSizeY()
{
    return playerSizeY;
}

void Player::setPlayerOrientation(QString orientation)
{
    playerOrientation = orientation;
}
