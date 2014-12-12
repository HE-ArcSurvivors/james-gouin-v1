#ifndef OBJECT_H
#define OBJECT_H

#include <QGraphicsItem>
#include "surface.h"

class QPixmap;
class QGraphicsPixmapItem;
class QBrush;

class Object : public Surface
{
public:
    Object(int xpos, int ypos, QGraphicsItem *parent);
    Object(QString new_nom, QGraphicsItem *parent = 0);
    void setDesign();

    //void setName(QString name);
    //void setPos(int x, int y);
    //QGraphicsPixmapItem *getImage();
    //QPixmap *getPicture();
    QBrush *objectSkin;

private:
    //QGraphicsPixmapItem* image;
    //QPixmap* picture;
    QString* nom;

};



#endif // OBJECT_H
