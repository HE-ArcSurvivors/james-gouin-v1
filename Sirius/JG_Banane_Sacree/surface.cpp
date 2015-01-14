#include "surface.h"
#include "gameboard.h"
#include <QGraphicsItem>
#include <QPoint>


Surface::Surface(int xpos, int ypos, QGraphicsItem *parent) : QGraphicsRectItem(0, 0, Gameboard::getGameSquares(), Gameboard::getGameSquares(), parent)
{
    setPen(Qt::NoPen);
//    setOpacity(0.6);

    setPos(xpos, ypos);
}
Surface::Surface(int xpos, int ypos, int width, int height, QGraphicsItem *parent) : QGraphicsRectItem(0, 0, width, height, parent)
{
    setPen(Qt::NoPen);

    setPos(xpos, ypos);
}
Surface::~Surface(){}

void Surface::setPos(int x, int y)
{
    QGraphicsRectItem::setPos(x*Gameboard::getGameSquares(), y*Gameboard::getGameSquares());
}
QPoint Surface::getPos()
{
    return QPoint(this->pos().x()/Gameboard::getGameSquares(), this->pos().y()/Gameboard::getGameSquares());
}

void Surface::setTexture(QString nom)
{
    QBrush* surfaceSkin = new QBrush();
    QString img = ":/maps/maps/";
    img.append(nom);
    img.append(".png");
    surfaceSkin->setTexture(QPixmap(img));
    setBrush(*surfaceSkin);
}
