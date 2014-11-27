#include "gameboard.h"

Gameboard::Gameboard(QWidget *parent) : QWidget(parent)
{
    // Les Variables par default du jeu
    windowTitle = tr("James Gouin et la Banane Sacrée");
    windowSizeX = 640;
    windowSizeY = 480;
    viewStartPostionX = 1;
    viewStartPostionY = 1;
    viewPositionX = 640;
    viewPositionY = 480;
    startingPoint = QPoint (1,10); // 20x15
    QString tutorialLevel3 = ":/images/test_map_tutoriel_3.png";

    this->setWindowTitle(windowTitle);
    this->setFixedSize(windowSizeX,windowSizeY);

    mainScene = new QGraphicsScene(this);
    playerView = new QGraphicsView(this);

    //On crée la scene
    QPixmap loadScene(tutorialLevel3);
    mainScene->setBackgroundBrush(loadScene);
    //mainScene->setSceneRect(viewStartPostionX,viewStartPostionY,viewPositionX,viewPositionX);

    //Ce qui est dessous peut etre utilise si la map est plus grande que la vue
    //playerView->setHorizontalScrollBarPolicy (Qt::ScrollBarAlwaysOff);
    //playerView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //playerView->setFocus();
    //playerView->setFixedSize(640,480);
    playerView->setSceneRect(viewStartPostionX,viewStartPostionY,viewPositionX,viewPositionX);

    //On ajoute le joueur
    player = new Player();
    mainScene->addItem(player);
    player->setPos(startingPoint.x()*gameSquares-gameSquares,startingPoint.y()*gameSquares-gameSquares);

    //On position la vue
    playerView->setScene(mainScene);

}

Gameboard::~Gameboard(){

}

//http://doc.qt.digia.com/4.6/qt.html#Key-enum
void Gameboard::keyPressEvent(QKeyEvent *event)
{
//    QMessageBox msgBox;
//    msgBox.setText(QString(event->key()));
//    msgBox.exec();
    if(event->key() == Qt::Key_W)
    {
        // Determiner si le joueur sort de la vue
        if (player->pos().y() > viewStartPostionY)
        {
            player->moveBy(0,-gameSquares);
            player->setPlayerOrientation("up"); //definir l'orientation du joueur
        }
    }
    if(event->key() == Qt::Key_S)
    {
        if (player->pos().y() <= viewPositionY-player->getPlayerSizeX()-8)
        {
            player->moveBy(0,gameSquares);
            player->setPlayerOrientation("down");
        }
    }
    if(event->key() == Qt::Key_A)
    {
        if (player->pos().x() > viewStartPostionY)
        {
            player->moveBy(-gameSquares,0);
            player->setPlayerOrientation("left");
        }
    }
    if(event->key() == Qt::Key_D)
    {
        if (player->pos().x() < viewPositionX-player->getPlayerSizeY())
        {
            player->moveBy(gameSquares,0);
            player->setPlayerOrientation("right");
        }
    }
    player->update();   //on recharge le painter
}
