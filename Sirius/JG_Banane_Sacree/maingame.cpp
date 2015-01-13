#include "maingame.h"

#include <QGraphicsView>
#include <QLabel>
#include <QDebug>

MainGame::MainGame(QWidget *parent) : QWidget(parent)
{
    theGame = new Gameboard;

    currentLevel = new Level(-1);
    // Les Variables par default du jeu
    windowTitle = tr("James Gouin et la Banane Sacrée");
    windowSizeX = theGame->sizeX*Gameboard::getGameSquares();
    windowSizeY = theGame->sizeY*Gameboard::getGameSquares();

    menuSizeX = 400;
    menuSizeY = 280;

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

    menuStart = new MenuStart(this);
    connect(menuStart,SIGNAL(startGame(int,int,int)),this, SLOT(startGame(int,int,int)));
    menuStart->setGeometry(windowSizeX/2-menuSizeX/2,windowSizeY/2-menuSizeY/2,menuSizeX,menuSizeY);

//    menuStartProxy->show();
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
    qDebug() << a << b << c;
    theGame->setParent(this);
    theGame->show();
}

