#include "b_water.h"

#include <QBrush>
#include <QGraphicsItem>

B_Water::B_Water(int xpos, int ypos, QGraphicsItem *parent) : Surface(xpos, ypos, parent)
{
    setDesign();
}
B_Water::B_Water(QGraphicsItem *parent) : Surface(0, 0, parent) //Pas le choix, obligé de donner un position fictive
{
    setDesign();
}
void B_Water::setDesign()
{
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::blue);

    setBrush(brush);
}
