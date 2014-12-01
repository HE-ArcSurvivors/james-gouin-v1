#ifndef BLOQUES_H
#define BLOQUES_H

#include <QGraphicsItem>
#include <QPainter>

class Bloques : public QGraphicsItem
{
public:
    Bloques();
    QRectF boundingRect() const;    //la box du player
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget); //paint event
    QBrush *surfaceSkin;

    int getSurfaceSizeX();
    int getSurfaceSizeY();

private:
    //J'ai essayé de changer la taille de la box dynamiquement selon l'image,
    //mais le probleme est qu'il y a des bugs graphiques inGame, l'image qui se decompose..
    int surfaceSizeX = 29;
    int surfaceSizeY = 29;
};

#endif // BLOQUES_H

