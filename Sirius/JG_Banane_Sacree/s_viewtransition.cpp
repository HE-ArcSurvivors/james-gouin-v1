#include "s_viewtransition.h"

#include <QGraphicsItem>
#include <QBrush>

S_ViewTransition::S_ViewTransition(int xpos, int ypos, QGraphicsItem *parent) : Surface(xpos, ypos, parent)
{
    setDesign();
}
S_ViewTransition::S_ViewTransition(QGraphicsItem *parent) : Surface(0, 0, parent)
{
    setDesign();
}

void S_ViewTransition::setDesign()
{
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::green);

    setBrush(brush);
}
