#include "gameboard.h"
#include "blockswalls.h"

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
            if (!canPlayerMove())
            {
                player->moveBy(0,gameSquares);
            }else{
                player->setPlayerOrientation("up");
            }
        }
    }
    if(event->key() == Qt::Key_S)
    {
        if (player->pos().y() <= viewSizeY-player->getPlayerSizeY()-8)
        {
            player->moveBy(0,gameSquares);
            if (!canPlayerMove())
            {
                player->moveBy(0,-gameSquares);
            }else{
                player->setPlayerOrientation("down");
            }
        }
    }
    if(event->key() == Qt::Key_A)
    {
        if (player->pos().x() > viewStartPostionX)
        {
            player->moveBy(-gameSquares,0);
            if (!canPlayerMove())
            {
                player->moveBy(gameSquares,0);
            }else{
                player->setPlayerOrientation("left");
            }
        }
    }
    if(event->key() == Qt::Key_D)
    {
        if (player->pos().x() < viewSizeX-player->getPlayerSizeX())
        {
            player->moveBy(gameSquares,0);
            if (!canPlayerMove())
            {
                player->moveBy(-gameSquares,0);
            }else{
                player->setPlayerOrientation("right");
            }

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

//    qDebug() << "x: " << player->pos().x() <<" y: " << player->pos().y();
    if (!player->collidesWithItem(transitionSurface))
    {
        transition = 0;
    }
//    qDebug() << transition;
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
    int viewStartPostionXTemp = viewStartPostionX+(viewPoint.x()-1)*viewSizeX;
    int viewStartPostionYTemp = viewStartPostionY+(viewPoint.y()-1)*viewSizeY;

    playerView->setSceneRect(viewStartPostionXTemp,viewStartPostionYTemp,viewSizeX,viewSizeY);
}

void Gameboard::populateScene()
{
    int Mat_Walls[60][30];
    QFile f(":/maps/sceneTutorial_v1.txt");
    if(f.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream t(&f);
        QString line[1000];
        QString s;
        int line_count=0;

        int matX, matY;

        while(!t.atEnd())
        {
            line_count++;
            line[line_count]=t.readLine();
            if(line[line_count].contains("type=Walls"))
            {
                line_count ++;
                line[line_count]=t.readLine();
                line_count ++;
                line[line_count]=t.readLine();
//                qDebug() << "Found Layer: " << line[line_count] << " at: " << line_count;
                for (matY = 0; matY < 30; matY++)
                {
                    QStringList values = line[line_count].split(",");

//                    qDebug() << "Flaged: " << line[line_count] << " at: " << line_count;
//                    qDebug() << "Values: " << values;
                    for (matX = 0; matX < 60; matX++)
                    {
                        Mat_Walls[matX][matY] = values.at(matX).toInt();
//                        qDebug() << "Value: " << Walls[matX][matY];
                    }
                    line_count++;
                    line[line_count]=t.readLine();
                }
            }
            if(line[line_count].contains("type=Solid_Blocks"))
            {
                line_count ++;
                line[line_count]=t.readLine();
                line_count ++;
                line[line_count]=t.readLine();
                for (matY = 0; matY < 30; matY++)
                {
                    QStringList values = line[line_count].split(",");

                    for (matX = 0; matX < 60; matX++)
                    {
                        Mat_Walls[matX][matY] += values.at(matX).toInt();
                    }
                    line_count++;
                    line[line_count]=t.readLine();
                }
            }
            if(line[line_count].contains("type=NoMoves"))
            {
                line_count ++;
                line[line_count]=t.readLine();
                line_count ++;
                line[line_count]=t.readLine();

                for (matY = 0; matY < 30; matY++)
                {
                    QStringList values = line[line_count].split(",");

                    for (matX = 0; matX < 60; matX++)
                    {
                        Mat_Walls[matX][matY] += values.at(matX).toInt();
                    }
                    line_count++;
                    line[line_count]=t.readLine();
                }
            }
        }
//        qDebug() << "Total of " << line_count;
//        qDebug() << "test of 31x11 " << Walls[58][29]; //max 59x29
        f.resize(0);
        t << s;
        f.close();
    }


    // Populate scene
    int nitems = 0;
    for (int i = 0; i < 40; i++) {

        for (int j = 0; j < 15; j++) {
            if (Mat_Walls[i][j] != 0)
            {
//                qDebug() << "I am in, i= " << i << "j= " << j;
                QGraphicsItem *item = new BlocksWalls;
                item->setPos(QPointF(i*32+2, j*32+2));
                mainScene->addItem(item);
                ++nitems;
            }
        }
    }
//    qDebug() << nitems;
}

bool Gameboard::canPlayerMove()
{
    QList <QGraphicsItem *> test = player->collidingItems();
    for(int i=0; i<test.length(); i++)
    {
        if(typeid(*test.at(i)).name() == typeid(BlocksWalls).name())
        {
//            qDebug() << "false";
            return false;

        }
    }
    return true;
}
