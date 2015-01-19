#ifndef LEVEL_H
#define LEVEL_H

class QString;
class QGraphicsScene;
class QPixmap;
class QPoint;
class Gameboard;

#include <QList>
#include <QStringList>
#include "w_dialog.h"

//#include "gameboard.h"


class Level
{
public:
    Level(int levelNumber, Gameboard *game);
    QGraphicsScene *populateScene();
    QPoint *getStartingPoint();
    QPoint getViewStart();
    int changeLevel(int levelNumber);
    int getLevelNumber();
    QString getDialogText(int value);

private:
    int levelNumber;
    QPoint* startingPoint;
    QPoint* viewStart;

    Gameboard *game;

    int maxBlocksHeight;
    int maxBlocksWidth;

    void getSceneSize();
    void getSceneDialog();

    QList<QList<QPoint> > ennemi;
    QStringList dialogList;
    int dialogValue;
};

#endif // LEVEL_H
