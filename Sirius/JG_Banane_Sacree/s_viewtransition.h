#ifndef S_VIEWTRANSITION_H
#define S_VIEWTRANSITION_H

#include "surface.h"
#include "qgraphicsitem.h"

class S_ViewTransition : public Surface
{
public:
    S_ViewTransition(int xpos, int ypos, QGraphicsItem *parent = 0);
    S_ViewTransition(QGraphicsItem *parent = 0);

private:
    void setDesign();
};

#endif // S_VIEWTRANSITION_H
