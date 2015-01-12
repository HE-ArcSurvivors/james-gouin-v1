#ifndef MAINGAME_H
#define MAINGAME_H

#include <QWidget>
#include "gameboard.h"
#include "m_menustart.h"

class QGraphicsView;
class QLabel;

class MainGame : public QWidget
{
    Q_OBJECT
public:
    explicit MainGame(QWidget *parent = 0);
    ~MainGame();

private:

    Gameboard *theGame;

    QGraphicsScene *gameScene;
    QGraphicsView *gameView;
//    void keyPressEvent(QKeyEvent *event);
    int windowSizeY;
    int windowSizeX;
    int viewPositionX;
    int viewPositionY;
    static int gameSquares;
    QString windowTitle;

    Level* currentLevel;

    int menuSizeX;
    int menuSizeY;

    int titleSizeX;
    int titleSizeY;

    QPoint viewRequested;

    void setViewPosition();

    MenuStart *menuStart;

    QGraphicsProxyWidget *menuStartProxy;

    QLabel *gameTitle;

signals:

public slots:
    void startGame(int,int,int);

};

#endif // MAINGAME_H
