#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QPixmap>
#include <QKeyEvent>
#include "p_penguin.h"

#include <QMessageBox>

class Gameboard : public QWidget
{
    Q_OBJECT
public:
    Gameboard(QWidget *parent = 0);
    ~Gameboard();

private:
    QGraphicsScene *mainScene;
    QGraphicsScene *preloadedScene;
    QGraphicsView *playerView;
    Pingouin *pingouin;
    void keyPressEvent(QKeyEvent *event);
    int viewPositionX;
    int viewPositionY;
    int windowSizeY;
    int windowSizeX;
    int viewStartPostionX;
    int viewStartPostionY;
    int gameSquares;
    QString windowTitle;
    QPoint startingPoint;

    int maxBlocksHeigh;
    int maxBlocksWidth;

    bool MovePingouinToLeft();
    bool MovePingouinToRight();
    bool MovePingouinToTop();
    bool MovePingouinToBottom();
    bool MovePingouin(QList<QGraphicsItem *>, char);

    void populateScene();

protected:


signals:

public slots:

};

#endif // GAMEBOARD_H
