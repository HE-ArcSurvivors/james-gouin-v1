#ifndef S_ICE_H
#define S_ICE_H
#include "surface.h"

class QGraphicsItem;

class S_Ice : public Surface
{
public:
    S_Ice(int xpos, int ypos, QGraphicsItem *parent = 0);
    S_Ice(QGraphicsItem *parent = 0);

private:
    void setDesign();
};

#endif // S_ICE_H
