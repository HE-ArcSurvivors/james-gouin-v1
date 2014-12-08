#ifndef SURFACE_H
#define SURFACE_H

#include "qgraphicsitem.h"

class Surface : public QGraphicsRectItem
{
public:
    Surface(int xpos, int ypos, QGraphicsItem *parent = 0);
    ~Surface();
    void setPos(int, int);
};

#endif // SURFACE_H
