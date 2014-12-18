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
    QString getName();
    void action();

private:
    QBrush* objectSkin;
    QString* nom;

};



#endif // OBJECT_H
