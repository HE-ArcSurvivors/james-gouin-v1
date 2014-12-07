#ifndef B_WALL_H
#define B_WALL_H
#include "block.h"
#include <QGraphicsItem>

class B_Wall : public Block
{
public:
    B_Wall(int xpos, int ypos, QGraphicsItem *parent = 0);
};

#endif // B_WALL_H
