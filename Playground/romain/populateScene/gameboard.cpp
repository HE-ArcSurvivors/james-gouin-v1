#include "gameboard.h"

Gameboard::Gameboard(QWidget *parent) : QWidget(parent)
{
    // Les Variables par default du jeu
    windowTitle = tr("James Gouin et la Banane Sacrée");
    windowSizeX = 640;
    windowSizeY = 480;
    viewStartPostionX = 1;
    viewStartPostionY = 1;
    viewSizeX = 640;
    viewSizeY = 480;
    startingPoint = QPoint (10,10); // 20x15
    viewRequested = QPoint (1,1);
    exit = QPoint (20,6); // 20x15

    QString tutorialLevel = ":/images/sceneTutorial_v1_only_solides.png";

    this->setWindowTitle(windowTitle);
    this->setFixedSize(windowSizeX,windowSizeY);

    mainScene = new QGraphicsScene(this);
    playerView = new QGraphicsView(this);

    //On crée la scene
    QPixmap loadScene(tutorialLevel);
    mainScene->setBackgroundBrush(loadScene);

    setView(viewRequested);
    populateScene();

    //On ajoute le joueur
    player = new Player();
    mainScene->addItem(player);
    player->setPos(pointToPixelX(startingPoint),pointToPixelY(startingPoint));

    transitionSurface = new ViewTransitionSurface();
    mainScene->addItem(transitionSurface);
    transitionSurface->setPos(pointToPixelX(exit)+1,pointToPixelY(exit)+1);

    //On position la vue
    playerView->setScene(mainScene);

}

Gameboard::~Gameboard(){

}

//http://doc.qt.digia.com/4.6/qt.html#Key-enum
void Gameboard::keyPressEvent(QKeyEvent *event)
{
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
        if (player->pos().y() <= viewSizeY-player->getPlayerSizeY()-8)
        {
            player->moveBy(0,gameSquares);
            player->setPlayerOrientation("down");
        }
    }
    if(event->key() == Qt::Key_A)
    {
        if (player->pos().x() > viewStartPostionX)
        {
            player->moveBy(-gameSquares,0);
            player->setPlayerOrientation("left");
        }
    }
    if(event->key() == Qt::Key_D)
    {
        if (player->pos().x() < viewSizeX-player->getPlayerSizeX())
        {
            player->moveBy(gameSquares,0);
            player->setPlayerOrientation("right");            
        }
    }
    if (player->collidesWithItem(transitionSurface))
    {
        transition++;
        if (transition == 2)
        {

        viewRequested.setX(viewRequested.x()+1);
        setView(viewRequested);
        player->moveBy(gameSquares,0);

        player->setPlayerOrientation("right");
        viewSizeX += windowSizeX;
        viewStartPostionX += windowSizeX;
        transition = 0;
        exit = QPoint (20,6) + QPoint (20,0);
        transitionSurface->setPos(pointToPixelX(exit)+1,pointToPixelY(exit)+1);

        }
    }
    qDebug() << "x: " << player->pos().x() <<" y: " << player->pos().y();
    if (!player->collidesWithItem(transitionSurface))
    {
        transition = 0;
    }
//    qDebug() << transition;
//    player->update();   //on recharge le painter
}

int Gameboard::pointToPixelX(QPoint point)
{
    return point.x()*gameSquares-gameSquares;
}

int Gameboard::pointToPixelY(QPoint point)
{
    return point.y()*gameSquares-gameSquares;
}

void Gameboard::setView(QPoint viewPoint)
{
    //int viewStartPostionXTemp = viewStartPostionX;
    //int viewStartPostionYTemp = viewStartPostionY;

    int viewStartPostionXTemp = viewStartPostionX+(viewPoint.x()-1)*viewSizeX;
    int viewStartPostionYTemp = viewStartPostionY+(viewPoint.y()-1)*viewSizeY;


    playerView->setSceneRect(viewStartPostionXTemp,viewStartPostionYTemp,viewSizeX,viewSizeY);
}

void Gameboard::populateScene()
{
    // Populate scene
    int nitems = 0;
    for (int i = 1; i < viewSizeX; i += 32) {

        for (int j = 1; j < viewSizeY; j += 32) {

            QColor color(Qt::blue);
            QGraphicsItem *item = new Surfaces();
            item->setPos(QPointF(i+1, j+1));
            mainScene->addItem(item);
            ++nitems;
        }
    }
    qDebug() << nitems;
}
