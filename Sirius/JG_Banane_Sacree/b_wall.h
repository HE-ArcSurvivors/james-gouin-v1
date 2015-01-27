#ifndef B_WALL_H
#define B_WALL_H
#include "surface.h"

class QGraphicsRectItem;

class B_Wall : public Surface
{
public:
    B_Wall(int xpos, int ypos, QGraphicsItem *parent = 0);
    B_Wall(QGraphicsItem *parent = 0);

private:
    void setDesign();
};

#endif // B_WALL_H
