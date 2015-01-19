#include "maingame.h"
#include "profil.h"

#include <QGraphicsView>
#include <QLabel>
#include <QDebug>

MainGame::MainGame(QWidget *parent) : QWidget(parent)
{
    toggleGameCreated = false;
    toggleFirstStart = true;

    currentLevel = new Level(-1, NULL);

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

    viewPositionX=0;
    viewPositionY=0;

    gameView = new QGraphicsView(this);

    gameView->setHorizontalScrollBarPolicy (Qt::ScrollBarAlwaysOff);
    gameView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    gameView->setSceneRect(viewPositionX,viewPositionY,theGame->sizeX*Gameboard::getGameSquares(),theGame->sizeY*Gameboard::getGameSquares());

    //On position la vue
    gameView->setScene(gameScene);

    gameTitle = new QLabel(this);
    gameTitle->setText(tr("James Gouin et la Banane Sacrée"));
    gameTitle->setStyleSheet("color: blue; font: bold 30px;");
    gameTitle->setGeometry(windowSizeX/2-titleSizeX/2,windowSizeY/2-menuSizeY/2-50,titleSizeX,titleSizeY);

    refreshGameMenu();

    quitGame = new QPushButton(tr("Quitter le jeu"), this);
    QObject::connect(quitGame,SIGNAL(clicked()),this,SLOT(close()));
    quitGame->setGeometry(windowSizeX/2-quitBtnSizeX/2,windowSizeY/2+menuSizeY/2+35,quitBtnSizeX,quitBtnSizeY);
}

MainGame::~MainGame()
{

}

void MainGame::startGame(Profil* user)
{
    theGame = new Gameboard();
    refreshGameMenu();
    theGame->setParent(this);
    theGame->setPlayerProfil(user);
    theGame->show();
    theGame->setGeometry(this->size().width()/2-windowSizeX/2,this->size().height()/2-windowSizeY/2,windowSizeX,windowSizeY);
    toggleGameCreated = true;
}

void MainGame::refreshGameMenu()
{
    if (!toggleFirstStart)
    {
        delete menuStart;
        menuStart = NULL;
    }
    toggleFirstStart = false;
    menuStart = new MenuStart(this);
    connect(menuStart,SIGNAL(startGame(Profil*)),this, SLOT(startGame(Profil*)));
    connect(menuStart,SIGNAL(refreshGameMenu()),this, SLOT(refreshGameMenu()));

    menuStart->setGeometry(this->size().width()/2-menuSizeX/2,this->size().height()/2-menuSizeY/2,menuSizeX,menuSizeY);
    menuStart->show();

}

void MainGame::resizeEvent(QResizeEvent * event) {

    if (event->size().width() >= windowSizeX || event->size().height() >= windowSizeX)
    {
        gameView->resize(event->size().width(),event->size().height());
        menuStart->setGeometry(event->size().width()/2-menuSizeX/2,event->size().height()/2-menuSizeY/2,menuSizeX,menuSizeY);
        gameTitle->setGeometry(event->size().width()/2-titleSizeX/2,event->size().height()/2-menuSizeY/2-50,titleSizeX,titleSizeY);
        quitGame->setGeometry(event->size().width()/2-quitBtnSizeX/2,event->size().height()/2+menuSizeY/2+35,quitBtnSizeX,quitBtnSizeY);
        menuStart->setGeometry(event->size().width()/2-menuSizeX/2,event->size().height()/2-menuSizeY/2,menuSizeX,menuSizeY);
        if (toggleGameCreated)
        {
            theGame->setGeometry(event->size().width()/2-windowSizeX/2,event->size().height()/2-windowSizeY/2,windowSizeX,windowSizeY);
        }

    }
}
