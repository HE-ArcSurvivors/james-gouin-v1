#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QWidget>
#include "p_penguin.h"
#include "b_movable.h"
#include "m_pause.h"
#include <QGraphicsProxyWidget>
#include "level.h"
#include "w_object.h"
#include "w_dialog.h"

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
    static int sizeX;
    static int sizeY;
    QPoint *getCheckPoint();

private:

    QTimer *timerPingouinSlide;
    QTimer *timerBlocDeplSlide;
    char cSensPingouinSlide;
    bool isSliding;

    QGraphicsScene *mainScene;
    QGraphicsScene *preloadedScene;
    QGraphicsView *playerView;
    Pingouin *pingouin;
    void keyPressEvent(QKeyEvent *event);
    int windowSizeY;
    int windowSizeX;
    int viewPositionX;
    int viewPositionY;
    static int gameSquares;
    QString windowTitle;

    Level* currentLevel;

    void setViewPosition();
    bool checkPosition(QGraphicsItem *object);

    int transition;
    QPoint viewRequested;
    QPoint exit;

    bool MovePingouinToLeft();
    bool MovePingouinToRight();
    bool MovePingouinToTop();
    bool MovePingouinToBottom();
    bool MovePingouin(QList<QGraphicsItem *>, char);

    void MoveBloc(char);

    void SinkMovable(B_Movable *b);
    void CheckChangeView(char);
    void ChangeView(char sens);
    bool CheckGameOver();
    void CheckItem();

    B_Movable *moveBloc;
    QList<slideBloc> listSlindingBlocs;

    void populateScene();

    void pauseMenu();

    int menuPauseSizeX;
    int menuPauseSizeY;

    QFormLayout *layoutMenuPause;
    QGroupBox *groupBoxMenuPause;
    QLabel *titleMenuPause;

    QPushButton *btnMenuPauseResume;
    QPushButton *btnMenuPauseConfigure;
    QPushButton *btnMenuPauseQuit;

    QPoint* checkpoint;
    void saveCheckpoint();
    void loadCheckpoint();

    // MENU PAUSE
    M_Pause *menuPauseInGame;
    QGraphicsProxyWidget *proxy;
    bool toggleMenuPause;

    // LIST DES OBJETS
    WidgetObject *objectList;
    QGraphicsProxyWidget *objectListProxy;

    // DIALOG
    WidgetDialog *dialog;
    QGraphicsProxyWidget* dialogProxy;
    bool dialogToogle;

    void setPositionBottom(QWidget* widget);
    void setPositionCenter(QWidget* widget);

protected:

signals:

public slots:
    void resumeGame();
    void SlidePingouin();
    void SlideBloc();

    void exitGame();
    void restartLevel();
    void restartGame();
};

#endif // GAMEBOARD_H
