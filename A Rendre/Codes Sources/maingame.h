/*********************************************************************************
* Copyright © Haute-Ecole ARC - All Rights Reserved
* Copyright © Banana Rocket - All Rights Reserved
*
* This file is part of <P2 Qt Project: James Gouin et la Banane Sacrée>.
*
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Claret-Yakovenko Roman <romain.claret@rocla.ch>, 27 January 2015
* Written by Divernois Margaux <margaux.divernois@gmail.com>, 27 January 2015
* Written by Visinand Steve <visinandst@gmail.com>, 27 January 2015
**********************************************************************************/

#ifndef MAINGAME_H
#define MAINGAME_H

#include <QWidget>
#include "gameboard.h"
#include "m_menustart.h"
#include "profil.h"

class QGraphicsView;
class QLabel;

/**
 * \brief QWidget principal gerant le programme du jeu dans le fond.
 *
 * Ce QWidget gère le jeu dans son fond. Il affiche le menu
 * principal du jeu pour commencer. Il premet d'effectuer la transition
 * entre le menu principal et le Gameboard. Il offre la structure
 * graphique de base du jeu au niveau software et disposition dans
 * l'environment de lancement (OS).
 */

class MainGame : public QWidget
{
    Q_OBJECT
public:
    explicit MainGame(QWidget *parent = 0);
    ~MainGame();

private:

    QPushButton* quitGame;  /**< \var Boutton pour quitter le jeu completement */

    Gameboard *theGame;

    QGraphicsScene *gameScene;
    QGraphicsView *gameView;
    int windowSizeY;
    int windowSizeX;
    int viewPositionX;
    int viewPositionY;
    static int gameSquares;
    QString windowTitle;

    Level* currentLevel;

    int menuSizeX;
    int menuSizeY;

    int quitBtnSizeX;
    int quitBtnSizeY;

    int titleSizeX;
    int titleSizeY;

    MenuStart *menuStart;

    QGraphicsProxyWidget *menuStartProxy;

    QLabel *gameTitle;

    void resizeEvent ( QResizeEvent * event );

    bool toggleGameCreated;
    bool toggleFirstStart;

    void closeEvent (QCloseEvent *event);

signals:

public slots:
    void startGame(Profil *user);
    void refreshGameMenu();

};

#endif // MAINGAME_H
