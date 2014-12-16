#include "gameboard.h"
#include "p_penguin.h"
#include "b_wall.h"
#include "b_movable.h"
#include "b_water.h"
#include "m_menustart.h"
#include "object.h"
#include "s_viewtransition.h"
#include "s_snow.h"
#include "s_ice.h"

#include <QList>
#include <QDebug>
#include <QGraphicsItemGroup>
#include <QGraphicsView>
#include <QKeyEvent>
#include <QFile>
#include <QFormLayout>
#include <QGroupBox>
#include <QLabel>
#include <QPoint>
#include <QPushButton>

#if defined(__unix__) || (defined(__APPLE__) && defined(__MACH__))
#else
#include <typeinfo.h>
#endif

int Gameboard::gameSquares = 32;

Gameboard::Gameboard(QWidget *parent) : QWidget(parent)
{
    // Les Variables par default du jeu
    windowTitle = tr("James Gouin et la Banane Sacrée");
    windowSizeX = 20*gameSquares;
    windowSizeY = 15*gameSquares;
    viewStartPostionX = 1;
    viewStartPostionY = 1;
    viewPositionX = 20*gameSquares;
    viewPositionY = 15*gameSquares;
    maxBlocksHeight = 30;
    maxBlocksWidth = 60;
    viewRequested = QPoint(1,1);
    exit = QPoint (20,6);

    gameSquares = 32;
    transition = 0;
    startingPoint = QPoint(20,6); // 20x15
    QString sceneToLoad = ":/maps/maps/tutorial.png";
    menuPauseSizeX = 400;
    menuPauseSizeY = 400;
    toggleGrabTheWorld = false;
    toggleMenuPause = false;

    bToDepl = NULL;
    checkpoint = new QPoint();

    this->setWindowTitle(windowTitle);
    this->setFixedSize(windowSizeX,windowSizeY);
    this->resize(windowSizeX,windowSizeY);

    mainScene = new QGraphicsScene(this);
    playerView = new QGraphicsView(this);

    //On crée la scene
    QPixmap loadScene(sceneToLoad);
    mainScene->setBackgroundBrush(loadScene);

    playerView->setHorizontalScrollBarPolicy (Qt::ScrollBarAlwaysOff);
    playerView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    playerView->setSceneRect(viewStartPostionX,viewStartPostionY,viewPositionX,viewPositionY);

    //On position la vue
    playerView->setScene(mainScene);
    grabKeyboard();

    //On ajoute le joueur
    pingouin = new Pingouin(gameSquares);
    pingouin->addToScene(mainScene);
    pingouin->setPos(startingPoint.x(), startingPoint.y());

    saveCheckpoint();
    populateScene();

    //On position la vue
    playerView->setScene(mainScene);
}

Gameboard::~Gameboard(){

}

void Gameboard::SinkMovable(B_Movable *b)
{
    QList<QGraphicsItem *> CollidingItems = b->CollidesCenter();
    for(int i=0; i<CollidingItems.length(); i++)
    {
        if(typeid(*CollidingItems.at(i)).name() == typeid(B_Water).name())
        {
            //SINK IT !
            QPoint p = b->getPos();
            qDebug() << "Sink it ! : " << p.x() << " " << p.y();

            b->removeFromScene(mainScene);
            mainScene->removeItem(CollidingItems.at(i));

            S_Snow *sunk = new S_Snow(p.x(),p.y());
            mainScene->addItem(sunk);
        }
    }
}

bool Gameboard::CheckGameOver()
{
    QList<QGraphicsItem *> CollidingItems = pingouin->CollidesCenter();

    for(int i=0; i<CollidingItems.length(); i++)
    {
        if(typeid(*CollidingItems.at(i)).name() == typeid(B_Water).name())
        {
            pingouin->setPlayerOrientation("down");
            loadCheckpoint();
            return true;
        }
    }
    return false;
}

void Gameboard::CheckItem()
{
    QList<QGraphicsItem *> CollidingItems = pingouin->CollidesCenter();

    for(int i=0; i<CollidingItems.length(); i++)
    {
        if(typeid(*CollidingItems.at(i)).name() == typeid(Object).name())
        {
            Object *objet = dynamic_cast<Object*>(CollidingItems.at(i));

            pingouin->addObjectToSacoche(new Object(objet->getName()));
            mainScene->removeItem(CollidingItems.at(i));
        }
    }
}

void Gameboard::CheckChangeView(QKeyEvent *event)
{
    QList<QGraphicsItem *> CollidingItems = pingouin->CollidesCenter();
    for(int i=0; i<CollidingItems.length(); i++)
    {
        if(typeid(*CollidingItems.at(i)).name() == typeid(S_ViewTransition).name())
        {
            if(pingouin->checkObjectSacoche("Poisson"))
            {
                qDebug() << "OK";
                qDebug() << pingouin->x() << " " << pingouin->y();
                checkpoint->setX(pingouin->x());
                checkpoint->setY(pingouin->y());
                qDebug() << "Nouveau Checkpoint : " << checkpoint->x() << " " << checkpoint->y();
            }
            else
            {
                qDebug() << "Pas encore de poisson !";
            }

            qDebug() << pingouin->x() << " " << pingouin->y();
            saveCheckpoint();

            qDebug() << "ViewRequested : " << viewRequested.x() << " " << viewRequested.y();

            if(event->key() == Qt::Key_W || event->key() == Qt::Key_Up)
            {
                if(!CheckGameOver())
                {
                    qDebug() << "Up";
                    this-> checkpoint->setY(checkpoint->y()-gameSquares);
                    viewRequested.setY(viewRequested.y()-1);
                }
            }
            if(event->key() == Qt::Key_S || event->key() == Qt::Key_Down)
            {
                qDebug() << "Down";
                this->checkpoint->setY(checkpoint->y()+gameSquares);
                viewRequested.setY(viewRequested.y()+1);
            }
            if(event->key() == Qt::Key_A || event->key() == Qt::Key_Left)
            {
                qDebug() << "Left";
                this->checkpoint->setX(checkpoint->x()-gameSquares);
                viewRequested.setX(viewRequested.x()-1);
            }
            if(event->key() == Qt::Key_D || event->key() == Qt::Key_Right)
            {
                qDebug() << "Right";

                this->checkpoint->setX(checkpoint->x()+gameSquares);
                viewRequested.setX(viewRequested.x()+1);
            }

            qDebug() << "ViewRequested : " << viewRequested.x() << " " << viewRequested.y();
            loadCheckpoint();
            setView(viewRequested);

            viewPositionX += windowSizeX;
            viewStartPostionX += windowSizeX;
            transition = 0;
        }
    }
}


//http://doc.qt.digia.com/4.6/qt.html#Key-enum
void Gameboard::keyPressEvent(QKeyEvent *event)
{
    if(!toggleMenuPause)
    {
        if(event->key() == Qt::Key_W || event->key() == Qt::Key_Up)
        {
            if(MovePingouinToTop())
            {
                pingouin->setPlayerOrientation("up");

                do
                {
                    pingouin->moveBy(0, -1);
                    if(!CheckGameOver())
                    {
                        CheckItem();
                        CheckChangeView(event);

                        if(bToDepl != NULL)
                        {
                            bToDepl->moveBy(0,-1);
                            SinkMovable(bToDepl);
                            bToDepl = NULL;
                        }
                    }
                }
                while(MovePingouinToTop() && pingouin->isSlide());
                bToDepl = NULL;
            }
        }
        if(event->key() == Qt::Key_S || event->key() == Qt::Key_Down)
        {
            if(MovePingouinToBottom())
            {
                pingouin->setPlayerOrientation("down");

                do
                {
                    pingouin->moveBy(0, 1);
                    if(!CheckGameOver())
                    {
                        CheckItem();
                        CheckChangeView(event);

                        if(bToDepl != NULL)
                        {
                            bToDepl->moveBy(0,1);
                            SinkMovable(bToDepl);
                            bToDepl = NULL;
                        }
                    }
                }
                while(MovePingouinToBottom() && pingouin->isSlide());
                bToDepl = NULL;
            }
        }
        if(event->key() == Qt::Key_A || event->key() == Qt::Key_Left)
        {
            if(MovePingouinToLeft())
            {
                pingouin->setPlayerOrientation("left");
                do
                {
                    pingouin->moveBy(-1, 0);
                    if(!CheckGameOver())
                    {
                        CheckItem();
                        CheckChangeView(event);

                        if(bToDepl != NULL)
                        {
                            bToDepl->moveBy(-1,0);
                            SinkMovable(bToDepl);
                            bToDepl = NULL;
                        }
                    }
                }
                while(MovePingouinToLeft() && pingouin->isSlide());
                bToDepl = NULL;
            }
        }
        if(event->key() == Qt::Key_D || event->key() == Qt::Key_Right)
        {
            if(MovePingouinToRight())
            {
                pingouin->setPlayerOrientation("right");
                do
                {
                    pingouin->moveBy(1, 0);
                    if(!CheckGameOver())
                    {
                        CheckItem();
                        CheckChangeView(event);

                        if(bToDepl != NULL)
                        {
                            bToDepl->moveBy(1,0);
                            SinkMovable(bToDepl);
                            bToDepl = NULL;
                        }
                    }
                }
                while(MovePingouinToRight() && pingouin->isSlide());
                bToDepl = NULL;
            }
        }
        if(event->key() == Qt::Key_0)
        {
            /*MenuStart* menuStart = new MenuStart();
            mainScene->addWidget(menuStart);*/

            pingouin->printSacoche();
        }
    }
    if(event->key() == Qt::Key_Escape)
    {
        //qDebug()<<"Escape Menu";
        pauseMenu();
    }
}

bool Gameboard::MovePingouinToLeft()
{
    return MovePingouin(pingouin->CollidesLeft(), 'l');
}

bool Gameboard::MovePingouinToRight()
{
    return MovePingouin(pingouin->CollidesRight(), 'r');
}

bool Gameboard::MovePingouinToTop()
{
    return MovePingouin(pingouin->CollidesTop(), 't');
}

bool Gameboard::MovePingouinToBottom()
{
    return MovePingouin(pingouin->CollidesBottom(), 'b');
}

bool Gameboard::MovePingouin(QList<QGraphicsItem *> CollidingItems, char sensDepl)
{
    bool bMove = true;
    for(int i=0; i<CollidingItems.length(); i++)
    {
        if(typeid(*CollidingItems.at(i)).name() == typeid(B_Wall).name())
        {
            bMove = false;
        }
        else if(typeid(*CollidingItems.at(i)).name() == typeid(B_Water).name())
        {
            //bMove = false;
        }
        else if(typeid(*CollidingItems.at(i)).name() == typeid(B_Movable).name())
        {
//            qDebug() << "bloc moves";
            B_Movable *b;
            b = dynamic_cast<B_Movable*>(CollidingItems.at(i));

            if(sensDepl == 'l' && b->IsMovableToLeft() && b->pos().x() > viewStartPostionY){
                //b->moveBy(-1,0);
                bToDepl = b;
                bMove = true;
            }
            else if(sensDepl == 'r' && b->IsMovableToRight() && b->pos().x() < viewPositionX-Gameboard::getGameSquares()){
                //b->moveBy(1,0);
                bToDepl = b;
                bMove = true;
            }
            else if(sensDepl == 't' && b->IsMovableToTop() && b->pos().y() > viewStartPostionY){
                //b->moveBy(0,-1);
                bToDepl = b;
                bMove = true;
            }
            else if(sensDepl == 'b' && b->IsMovableToBottom() && b->pos().y() <= viewPositionY-Gameboard::getGameSquares()-8){
                //b->moveBy(0, 1);
                bToDepl = b;
                bMove = true;
            }
            else{
                bMove=false;
            }
        }
//        else if(typeid(*CollidingItems.at(i)).name() == typeid(Object).name())
//        {
//            Object *objet = dynamic_cast<Object*>(CollidingItems.at(i));

//            pingouin->addObjectToSacoche(new Object(objet->getName()));
//            mainScene->removeItem(CollidingItems.at(i));
//        }
        /*else if(typeid(*CollidingItems.at(i)).name() == typeid(S_ViewTransition).name())
        {

        }*/

//        if (typeid(*CollidingItems.at(i)).name() == typeid(S_ViewTransition).name())
//        {
//            transition++;
//            if (transition == 2)
//            {

//            viewRequested.setX(viewRequested.x()+1);
//            setView(viewRequested);
//            MovePingouinToRight();

//            viewPositionX += windowSizeX;
//            viewStartPostionX += windowSizeX;
//            transition = 0;

//            }
//        }
//        if (!(typeid(*CollidingItems.at(i)).name() == typeid(S_ViewTransition).name()))
//        {
//            transition = 0;
//        }
    }
    return bMove;
}


void Gameboard::populateScene()
{
    int Mat_Walls_Blocks[maxBlocksWidth][maxBlocksHeight];
    int Mat_Movable_Blocks[maxBlocksWidth][maxBlocksHeight];
    int Mat_Items[maxBlocksWidth][maxBlocksHeight];
    int Mat_Bonus[maxBlocksWidth][maxBlocksHeight];
    int Mat_Enemies[maxBlocksWidth][maxBlocksHeight];
    int Mat_Scene_Start[maxBlocksWidth][maxBlocksHeight];
    int Mat_Scene_End[maxBlocksWidth][maxBlocksHeight];
    int Mat_Doors[maxBlocksWidth][maxBlocksHeight];
    int Mat_Water_Blocks[maxBlocksWidth][maxBlocksHeight];
    int Mat_Snow_Surface[maxBlocksWidth][maxBlocksHeight];
    int Mat_Ice_Surface[maxBlocksWidth][maxBlocksHeight];

    QFile f(":/maps/maps/sceneTutorial_v3.txt");
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
            if(line[line_count].contains("type=Walls_Blocks"))
            {
                line_count ++;
                line[line_count]=t.readLine();
                line_count ++;
                line[line_count]=t.readLine();
//                qDebug() << "Found Layer: " << line[line_count] << " at: " << line_count;
                for (matY = 0; matY < maxBlocksHeight; matY++)
                {
                    QStringList values = line[line_count].split(",");

//                    qDebug() << "Flaged: " << line[line_count] << " at: " << line_count;
//                    qDebug() << "Values: " << values;
                    for (matX = 0; matX < maxBlocksWidth; matX++)
                    {
                        Mat_Walls_Blocks[matX][matY] = values.at(matX).toInt();
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
                for (matY = 0; matY < maxBlocksHeight; matY++)
                {
                    QStringList values = line[line_count].split(",");

                    for (matX = 0; matX < maxBlocksWidth; matX++)
                    {
                        Mat_Walls_Blocks[matX][matY] += values.at(matX).toInt();
                    }
                    line_count++;
                    line[line_count]=t.readLine();
                }
            }

            if(line[line_count].contains("type=Movable_Blocks"))
            {
                line_count ++;
                line[line_count]=t.readLine();
                line_count ++;
                line[line_count]=t.readLine();

                for (matY = 0; matY < maxBlocksHeight; matY++)
                {
                    QStringList values = line[line_count].split(",");

                    for (matX = 0; matX < maxBlocksWidth; matX++)
                    {
                        Mat_Movable_Blocks[matX][matY] = values.at(matX).toInt();
                    }
                    line_count++;
                    line[line_count]=t.readLine();
                }
            }

            if(line[line_count].contains("type=Items"))
            {
                line_count ++;
                line[line_count]=t.readLine();
                line_count ++;
                line[line_count]=t.readLine();

                for (matY = 0; matY < maxBlocksHeight; matY++)
                {
                    QStringList values = line[line_count].split(",");

                    for (matX = 0; matX < maxBlocksWidth; matX++)
                    {
                        Mat_Items[matX][matY] = values.at(matX).toInt();
                    }
                    line_count++;
                    line[line_count]=t.readLine();
                }
            }

            if(line[line_count].contains("type=Bonus"))
            {
                line_count ++;
                line[line_count]=t.readLine();
                line_count ++;
                line[line_count]=t.readLine();

                for (matY = 0; matY < maxBlocksHeight; matY++)
                {
                    QStringList values = line[line_count].split(",");

                    for (matX = 0; matX < maxBlocksWidth; matX++)
                    {
                        Mat_Bonus[matX][matY] = values.at(matX).toInt();
                    }
                    line_count++;
                    line[line_count]=t.readLine();
                }
            }

            if(line[line_count].contains("type=Enemies"))
            {
                line_count ++;
                line[line_count]=t.readLine();
                line_count ++;
                line[line_count]=t.readLine();

                for (matY = 0; matY < maxBlocksHeight; matY++)
                {
                    QStringList values = line[line_count].split(",");

                    for (matX = 0; matX < maxBlocksWidth; matX++)
                    {
                        Mat_Enemies[matX][matY] = values.at(matX).toInt();
                    }
                    line_count++;
                    line[line_count]=t.readLine();
                }
            }

            if(line[line_count].contains("type=Scene_Start"))
            {
                line_count ++;
                line[line_count]=t.readLine();
                line_count ++;
                line[line_count]=t.readLine();

                for (matY = 0; matY < maxBlocksHeight; matY++)
                {
                    QStringList values = line[line_count].split(",");

                    for (matX = 0; matX < maxBlocksWidth; matX++)
                    {
                        Mat_Scene_Start[matX][matY] = values.at(matX).toInt();
                    }
                    line_count++;
                    line[line_count]=t.readLine();
                }
            }

            if(line[line_count].contains("type=Scene_End"))
            {
                line_count ++;
                line[line_count]=t.readLine();
                line_count ++;
                line[line_count]=t.readLine();

                for (matY = 0; matY < maxBlocksHeight; matY++)
                {
                    QStringList values = line[line_count].split(",");

                    for (matX = 0; matX < maxBlocksWidth; matX++)
                    {
                        Mat_Scene_End[matX][matY] = values.at(matX).toInt();
                    }
                    line_count++;
                    line[line_count]=t.readLine();
                }
            }
            if(line[line_count].contains("type=Doors"))
            {
                line_count ++;
                line[line_count]=t.readLine();
                line_count ++;
                line[line_count]=t.readLine();

                for (matY = 0; matY < maxBlocksHeight; matY++)
                {
                    QStringList values = line[line_count].split(",");

                    for (matX = 0; matX < maxBlocksWidth; matX++)
                    {
                        Mat_Doors[matX][matY] = values.at(matX).toInt();
                    }
                    line_count++;
                    line[line_count]=t.readLine();
                }
            }

            if(line[line_count].contains("type=Water_Blocks"))
            {
                line_count ++;
                line[line_count]=t.readLine();
                line_count ++;
                line[line_count]=t.readLine();
                for (matY = 0; matY < maxBlocksHeight; matY++)
                {
                    QStringList values = line[line_count].split(",");

                    for (matX = 0; matX < maxBlocksWidth; matX++)
                    {
                        Mat_Water_Blocks[matX][matY] = values.at(matX).toInt();
                    }
                    line_count++;
                    line[line_count]=t.readLine();
                }
            }

            if(line[line_count].contains("type=NoMoves_Blocks"))
            {
                line_count ++;
                line[line_count]=t.readLine();
                line_count ++;
                line[line_count]=t.readLine();

                for (matY = 0; matY < maxBlocksHeight; matY++)
                {
                    QStringList values = line[line_count].split(",");

                    for (matX = 0; matX < maxBlocksWidth; matX++)
                    {
                        Mat_Walls_Blocks[matX][matY] += values.at(matX).toInt();
                    }
                    line_count++;
                    line[line_count]=t.readLine();
                }
            }


            if(line[line_count].contains("type=Snow_Surface"))
            {
                line_count ++;
                line[line_count]=t.readLine();
                line_count ++;
                line[line_count]=t.readLine();

                for (matY = 0; matY < maxBlocksHeight; matY++)
                {
                    QStringList values = line[line_count].split(",");

                    for (matX = 0; matX < maxBlocksWidth; matX++)
                    {
                        Mat_Snow_Surface[matX][matY] = values.at(matX).toInt();
                    }
                    line_count++;
                    line[line_count]=t.readLine();
                }
            }

            if(line[line_count].contains("type=Ice_Surface"))
            {
                line_count ++;
                line[line_count]=t.readLine();
                line_count ++;
                line[line_count]=t.readLine();

                for (matY = 0; matY < maxBlocksHeight; matY++)
                {
                    QStringList values = line[line_count].split(",");

                    for (matX = 0; matX < maxBlocksWidth; matX++)
                    {
                        Mat_Ice_Surface[matX][matY] = values.at(matX).toInt();
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
    for (int i = 0; i < maxBlocksWidth; i++) {

        for (int j = 0; j < maxBlocksHeight; j++) {
            if (Mat_Walls_Blocks[i][j] != 0)
            {
                B_Wall *item = new B_Wall();
                item->setPos(i,j);
                mainScene->addItem(item);
            }
            if (Mat_Movable_Blocks[i][j] != 0)
            {
                B_Movable *item = new B_Movable(i,j);
                item->addToScene(mainScene);
            }
            if (Mat_Items[i][j] != 0)
            {
                Object *item = new Object("Poisson");
                item->setPos(i, j);
                mainScene->addItem(item);
            }
            if (Mat_Bonus[i][j] != 0)
            {
                Object *item = new Object("Oeuf");
                item->setPos(i, j);
                mainScene->addItem(item);
            }
//            if (Mat_Enemies[i][j] != 0)
//            {
//                QGraphicsItem *item = new B_Wall();
//                item->setPos(QPointF(i*gameSquares, j*gameSquares));
//                mainScene->addItem(item);
//            }
//            if (Mat_Scene_Start[i][j] != 0)
//            {
//                QGraphicsItem *item = new B_Wall();
//                item->setPos(QPointF(i*gameSquares, j*gameSquares));
//                mainScene->addItem(item);
//            }
//            if (Mat_Scene_End[i][j] != 0)
//            {
//                QGraphicsItem *item = new B_Wall();
//                item->setPos(QPointF(i*gameSquares, j*gameSquares));
//                mainScene->addItem(item);
//            }
            if (Mat_Doors[i][j] != 0)
            {
                S_ViewTransition *item = new S_ViewTransition();
                item->setPos(i,j);
                mainScene->addItem(item);
            }
            if (Mat_Water_Blocks[i][j] != 0)
            {
                B_Water *item = new B_Water();
                item->setPos(i,j);
                mainScene->addItem(item);
            }
            if (Mat_Snow_Surface[i][j] != 0)
            {
                S_Snow *item = new S_Snow();
                item->setPos(i,j);
                mainScene->addItem(item);
            }
            if (Mat_Ice_Surface[i][j] != 0)
            {
                S_Snow *item = new S_Snow();
                item->setPos(i,j);
                mainScene->addItem(item);
            }
        }
    }
}

void Gameboard::setView(QPoint viewPoint)
{
    int viewStartPostionXTemp = (viewPoint.x()-1)*windowSizeX;
    int viewStartPostionYTemp = (viewPoint.y()-1)*windowSizeY;

    playerView->setSceneRect(viewStartPostionXTemp,viewStartPostionYTemp,windowSizeX,windowSizeY);
}

int Gameboard::getGameSquares()
{
    return gameSquares;
}


void Gameboard::pauseMenu()
{
    toggleMenuPause = !toggleMenuPause;
    grabTheWorld();
    if(toggleMenuPause)
    {
        layoutMenuPause = new QFormLayout;
        groupBoxMenuPause = new QGroupBox;
        titleMenuPause = new QLabel(tr("Menu PAUSE"));
        titleMenuPause->setAlignment(Qt::AlignCenter);
        titleMenuPause->setStyleSheet("margin-left: auto; margin-right : auto; color: blue; font: bold 20px;");
        groupBoxMenuPause->setStyleSheet("text-align: center; color: blue; background-color: lightblue;");
        groupBoxMenuPause->setGeometry(viewStartPostionX+windowSizeX/2-menuPauseSizeX/2,viewStartPostionY+windowSizeY/2-menuPauseSizeY/2,menuPauseSizeX,menuPauseSizeY);
        layoutMenuPause->addRow(titleMenuPause);
        btnMenuPauseResume = new QPushButton(tr("Resume"));
        btnMenuPauseConfigure = new QPushButton(tr("Configure"));
        btnMenuPauseQuit = new QPushButton(tr("Quit"));
        connect(btnMenuPauseQuit, SIGNAL(clicked()),this, SLOT(close()));
        connect(btnMenuPauseResume, SIGNAL(clicked()),this, SLOT(resumeGame()));
        layoutMenuPause->addRow(btnMenuPauseResume);
        layoutMenuPause->addRow(btnMenuPauseConfigure);
        layoutMenuPause->addRow(btnMenuPauseQuit);
        groupBoxMenuPause->setLayout(layoutMenuPause);
        menuPauseOnTop = mainScene->addWidget(groupBoxMenuPause);
//        menuPauseOnTop = mainScene->addWidget(M_Pause);

    }else{

    }

}

void Gameboard::grabTheWorld()
{
    toggleGrabTheWorld = !toggleGrabTheWorld;

    if(toggleGrabTheWorld)
    {
        QList<QGraphicsItem *> items = mainScene->items();

        foreach( QGraphicsItem *item, items )
        {
            if(typeid(*item).name() == typeid(S_Snow).name())
            {
                item->setZValue(-1);
            }
            if(typeid(*item).name() == typeid(B_Movable).name())
            {
                item->setZValue(0);
            }
            if(typeid(*item).name() == typeid(Pingouin).name())
            {
                item->setZValue(0);
            }
            if(typeid(*item).name() == typeid(Object).name())
            {
                item->setZValue(0);
            }
        }
    }else{
        QList<QGraphicsItem *> items = mainScene->items();

        foreach( QGraphicsItem *item, items )
        {
            if(typeid(*item).name() == typeid(S_Snow).name())
            {
                item->setZValue(0);
            }
            if(typeid(*item).name() == typeid(B_Movable).name())
            {
                item->setZValue(1);
            }
            if(typeid(*item).name() == typeid(Pingouin).name())
            {
                item->setZValue(2);
            }
//            if(typeid(*item).name() == typeid(Object).name())
//            {
//                item->setZValue(2);
//            }
        }
    }

}

void Gameboard::resumeGame()
{
    pauseMenu();
}


QPoint* Gameboard::getCheckPoint()
{
    return this->checkpoint;
}

void Gameboard::saveCheckpoint()
{
    checkpoint->setX(pingouin->x());
    checkpoint->setY(pingouin->y());
    qDebug() << "SAVE Checkpoint" << (checkpoint->x()+gameSquares)/gameSquares << " " << (checkpoint->y()+gameSquares)/gameSquares;
}

void Gameboard::loadCheckpoint()
{
    pingouin->setPos((checkpoint->x()+gameSquares)/gameSquares,(checkpoint->y()+gameSquares)/gameSquares);
    qDebug() << "LOAD CHECKPOINT" << (checkpoint->x()+gameSquares)/gameSquares << " " << (checkpoint->y()+gameSquares)/gameSquares;
}
