#ifndef LEVEL_H
#define LEVEL_H

class QString;
class QGraphicsScene;
class QPixmap;
class QPoint;

class Level
{
public:
    Level(QString levelName);
    QGraphicsScene *populateScene();

    QString *getNeededItem();
    QPoint *getStartingPoint();
    QPoint getViewStart();

private:
    QString* levelName;
    QPixmap* levelBackground;
    QString* neededItem;
    QPoint* startingPoint;
    QPoint* viewStart;

    int maxBlocksHeight;
    int maxBlocksWidth;

    void getSceneSize();
};

#endif // LEVEL_H
