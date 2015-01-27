#include "b_wall.h"

#include <QBrush>
#include <QGraphicsItem>
#include <QGraphicsRectItem>

B_Wall::B_Wall(int xpos, int ypos, QGraphicsItem *parent) : Surface(xpos, ypos, parent)
{
    setDesign();
}
B_Wall::B_Wall(QGraphicsItem *parent) : Surface(0, 0, parent) //Pas le choix, obligé de donner un position fictive
{
    setDesign();
}
void B_Wall::setDesign()
{
    //QBrush brush;
    //brush.setStyle(Qt::SolidPattern);
    //brush.setColor(Qt::red);

//    setBrush(brush);
}
