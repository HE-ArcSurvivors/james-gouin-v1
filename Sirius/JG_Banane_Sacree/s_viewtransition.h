#ifndef S_VIEWTRANSITION_H
#define S_VIEWTRANSITION_H

#include "surface.h"
#include "qgraphicsitem.h"

class S_ViewTransition : public Surface
{
public:
    S_ViewTransition(int xpos, int ypos, QGraphicsItem *parent = 0);
    S_ViewTransition(QGraphicsItem *parent = 0);

    bool isEndLevel();
    void setLevelEnd(bool value);
    void setNeededItem(QString value);

    QString *getNeededItem();
    bool isNeedingItem();

    void setNbItem(int nb);
    int getNbItem();

    void setNextLevel(int nb);
    int getNextLevel();

private:
    void setDesign();
    bool levelEnd;
    int nextLevel;

    bool needItem;
    int nbItem;
    QString* neededItem;
};

#endif // S_VIEWTRANSITION_H
