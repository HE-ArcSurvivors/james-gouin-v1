#ifndef S_SNOW_H
#define S_SNOW_H
#include "surface.h"
#include "qgraphicsitem.h"

class S_Snow : public Surface
{
public:
    S_Snow(int xpos, int ypos, QGraphicsItem *parent = 0);
    S_Snow(QGraphicsItem *parent = 0);

private:
    void setDesign();
};

#endif // S_SNOW_H
