#ifndef S_SNOW_H
#define S_SNOW_H
#include "surface.h"
#include <QGraphicsItem>

class S_Snow : public Surface
{
public:
    S_Snow(int xpos, int ypos, QGraphicsItem *parent = 0);
};

#endif // S_SNOW_H
