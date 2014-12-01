#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QPixmap>
#include <QKeyEvent>
#include "player.h"
#include "viewtransitionsurface.h"
#include <QDebug>
#include <QMessageBox>
#include "surfaces.h"
#include <QFile>

class Gameboard : public QWidget
{
    Q_OBJECT
public:
    Gameboard(QWidget *parent = 0);
    ~Gameboard();


private:
    QGraphicsScene *mainScene;
//    QGraphicsScene *preloadedScene;
    QGraphicsView *playerView;
    Player *player;
    void keyPressEvent(QKeyEvent *event);
    int viewSizeX;
    int viewSizeY;
    int windowSizeY;
    int windowSizeX;
    int viewStartPostionX;
    int viewStartPostionY;
    int gameSquares = 32;
    QString windowTitle;
    QPoint startingPoint;
    QPoint viewRequested;
    QPoint exit;

    ViewTransitionSurface *transitionSurface;

    int pointToPixelX(QPoint);
    int pointToPixelY(QPoint);

    void setView(QPoint);

    int transition = 0;

    void populateScene();

protected:


signals:

public slots:

};

#endif // GAMEBOARD_H
