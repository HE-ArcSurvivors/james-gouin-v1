#ifndef LEVEL_H
#define LEVEL_H

class QString;
class QGraphicsScene;
class QPixmap;
class QPoint;

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
    QPixmap* levelBackground;
    QPoint* startingPoint;
    QPoint* viewStart;

    int maxBlocksHeight;
    int maxBlocksWidth;

    void getSceneSize();
};

#endif // LEVEL_H
