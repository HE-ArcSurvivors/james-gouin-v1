#ifndef LEVEL_H
#define LEVEL_H

class QString;
class QGraphicsScene;
class QPixmap;
class QPoint;

#include <QList>

class Level
{
public:
    Level(int levelNumber);
    QGraphicsScene *populateScene();
    QPoint *getStartingPoint();
    QPoint getViewStart();
    QGraphicsScene* changeLevel(int levelNumber);
    int getLevelNumber();

private:
    int levelNumber;
    QPoint* startingPoint;
    QPoint* viewStart;

    int maxBlocksHeight;
    int maxBlocksWidth;

    void getSceneSize();

    QList<QList<QPoint> > ennemi;
};

#endif // LEVEL_H
