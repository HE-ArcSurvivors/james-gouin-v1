#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QPixmap>
#include <QKeyEvent>
#include "pingouin.h"

#include <QMessageBox>

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
    pingouin *pingouin;
    void keyPressEvent(QKeyEvent *event);
    int viewPositionX;
    int viewPositionY;
    int windowSizeY;
    int windowSizeX;
    int viewStartPostionX;
    int viewStartPostionY;
    int gameSquares = 32;
    QString windowTitle;
    QPoint startingPoint;

protected:


signals:

public slots:

};

#endif // GAMEBOARD_H
