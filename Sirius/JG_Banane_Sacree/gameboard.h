#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QPixmap>
#include <QKeyEvent>
#include "p_penguin.h"
#include <QFormLayout>
#include "b_movable.h"
#include <QGroupBox>
#include <QMessageBox>
#include <QLabel>
#include <QPushButton>
#include "m_pause.h"
#include <QGraphicsProxyWidget>

class Gameboard : public QWidget
{
    Q_OBJECT
public:
    Gameboard(QWidget *parent = 0);
    ~Gameboard();

    static int getGameSquares();

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
    static int gameSquares;
    QString windowTitle;
    QPoint startingPoint;

    int maxBlocksHeigh;
    int maxBlocksWidth;
    int transition;
    QPoint viewRequested;
    QPoint exit;
    void setView(QPoint);

    bool MovePingouinToLeft();
    bool MovePingouinToRight();
    bool MovePingouinToTop();
    bool MovePingouinToBottom();
    bool MovePingouin(QList<QGraphicsItem *>, char);

    void SinkMovable(B_Movable *b);
    void ChangeView();


    B_Movable *bToDepl;

    void populateScene();

    void pauseMenu();

    int menuPauseSizeX;
    int menuPauseSizeY;

    bool toggleGrabTheWorld;
    bool toggleMenuPause;

    void grabTheWorld();

    QGraphicsProxyWidget *menuPauseOnTop;

    QFormLayout *layoutMenuPause;
    QGroupBox *groupBoxMenuPause;
    QLabel *titleMenuPause;

    QPushButton *btnMenuPauseResume;
    QPushButton *btnMenuPauseConfigure;
    QPushButton *btnMenuPauseQuit;

    M_Pause *menuPauseTest;

    QGraphicsProxyWidget *proxy;

protected:


signals:

public slots:
    void resumeGame();


};

#endif // GAMEBOARD_H
