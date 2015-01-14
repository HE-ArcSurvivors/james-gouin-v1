#ifndef S_DIALOG_H
#define S_DIALOG_H

#include "surface.h"

class QGraphicsItem;

class S_Dialog : public Surface
{
public:
    S_Dialog(int xpos, int ypos, QGraphicsItem *parent = 0);
    S_Dialog(QGraphicsItem *parent = 0);

private:
    void setDesign();
};

#endif // S_DIALOG_H
