#ifndef B_WATER_H
#define B_WATER_H
#include "surface.h"
#include "qgraphicsitem.h"

class B_Water : public Surface
{
public:
    B_Water(int xpos, int ypos, QGraphicsItem *parent = 0);
    B_Water(QGraphicsItem *parent = 0);

private:
    void setDesign();
};

#endif // B_WATER_H
