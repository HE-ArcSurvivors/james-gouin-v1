#include "maingame.h"

#include <QGraphicsView>
#include <QLabel>
#include <QDebug>

MainGame::MainGame(QWidget *parent) : QWidget(parent)
{

    currentLevel = new Level(-1);
    // Les Variables par default du jeu
    windowTitle = tr("James Gouin et la Banane Sacrée");
    windowSizeX = theGame->sizeX*Gameboard::getGameSquares();
    windowSizeY = theGame->sizeY*Gameboard::getGameSquares();

    menuSizeX = 400;
    menuSizeY = 280;

    quitBtnSizeX = menuSizeX-20;
    quitBtnSizeY = 50;

    titleSizeX = 479;
    titleSizeY = 30;

    this->setWindowTitle(windowTitle);
    this->resize(windowSizeX,windowSizeY);

    gameScene = new QGraphicsScene(this);
    gameScene = currentLevel->populateScene();

    viewRequested = currentLevel->getViewStart();
    setViewPosition();

    gameView = new QGraphicsView(this);

    gameView->setHorizontalScrollBarPolicy (Qt::ScrollBarAlwaysOff);
    gameView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    gameView->setSceneRect(viewPositionX,viewPositionY,theGame->sizeX*Gameboard::getGameSquares(),theGame->sizeY*Gameboard::getGameSquares());

    //On position la vue
    gameView->setScene(gameScene);

//    grabKeyboard();

    gameTitle = new QLabel(this);
    gameTitle->setText(tr("James Gouin et la Banane Sacrée"));
    gameTitle->setStyleSheet("color: blue; font: bold 30px;");
    gameTitle->setGeometry(windowSizeX/2-titleSizeX/2,windowSizeY/7-titleSizeY/2,titleSizeX,titleSizeY);

    refreshGameMenu();

    quitGame = new QPushButton(tr("Quitter le jeu"), this);
    QObject::connect(quitGame,SIGNAL(clicked()),this,SLOT(close()));
    quitGame->setGeometry(windowSizeX/2-quitBtnSizeX/2,9*windowSizeY/10-quitBtnSizeY/2,quitBtnSizeX,quitBtnSizeY);

}

MainGame::~MainGame()
{

}

void MainGame::setViewPosition()
{
    int x = viewRequested.x();
    int y = viewRequested.y();

    if(x==1) { viewPositionX = 1; }
    else
    {
        viewPositionX = (x-1)*20*Gameboard::getGameSquares();
    }

    if(y==1)
    {
        viewPositionY = 1;
    }
    else
    {
        viewPositionY = (y-1)*15*Gameboard::getGameSquares();
    }
}

void MainGame::startGame(int a, int b, int c)
{
    theGame = new Gameboard;
    theGame->setParent(this);
    theGame->show();
}

void MainGame::refreshGameMenu()
{
    delete this->menuStart;
    menuStart = new MenuStart(this);
    menuStart->show();
    connect(menuStart,SIGNAL(startGame(int,int,int)),this, SLOT(startGame(int,int,int)));
    connect(menuStart,SIGNAL(refreshGameMenu()),this, SLOT(refreshGameMenu()));
    menuStart->setGeometry(windowSizeX/2-menuSizeX/2,windowSizeY/2-menuSizeY/2,menuSizeX,menuSizeY);
}
