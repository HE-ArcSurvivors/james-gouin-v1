#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QWidget>
#include "p_penguin.h"
#include "b_movable.h"
#include "m_pause.h"
#include <QGraphicsProxyWidget>

class QGraphicsScene;
class QGraphicsView;
class QGraphicsItem;
class QPixmap;
class QKeyEvent;
class QFormLayout;
class QGroupBox;
class QMessageBox;
class QLabel;
class QPushButton;
class QPoint;
class QTimer;

struct slideBloc{
    B_Movable *slidingMovable;
    char sens; //l, r, t, b
};

class Gameboard : public QWidget
{
    Q_OBJECT
public:
    Gameboard(QWidget *parent = 0);
    ~Gameboard();

    static int getGameSquares();
    QPoint *getCheckPoint();

private:

    QTimer *timerPingouinSlide;
    QTimer *timerBlocDeplSlide;
    char cSensPingouinSlide;

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

    int maxBlocksHeight;
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

    void MoveBloc(char);

    void SinkMovable(B_Movable *b);
    void CheckChangeView(char);
    bool CheckGameOver();
    void CheckItem();

    B_Movable *moveBloc;
    QList<slideBloc> listSlindingBlocs;
    QString* neededItem;

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

    QPoint* checkpoint;
    void saveCheckpoint();
    void loadCheckpoint();

	M_Pause *menuPauseInGame;

    QGraphicsProxyWidget *proxy;protected:


signals:

public slots:
    void resumeGame();
    void SlidePingouin();
    void SlideBloc();

    void exitGame();
};

#endif // GAMEBOARD_H
