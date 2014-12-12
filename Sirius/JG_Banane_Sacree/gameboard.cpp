#include "gameboard.h"
#include "p_penguin.h"
#include "b_wall.h"
#include "b_movable.h"
#include "b_water.h"
#include "m_menustart.h"
#include "object.h"
#include <QList>
#include <QDebug>

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
    maxBlocksHeigh = 30;
    maxBlocksWidth = 60;
    startingPoint = QPoint (10,10); // 20x15
    QString sceneToLoad = ":/maps/maps/tutorial.png";

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

    //On ajoute le joueur
    pingouin = new Pingouin(gameSquares);
    pingouin->addToScene(mainScene);
    pingouin->setPos(startingPoint.x(), startingPoint.y());

    Object *poisson = new Object("Poisson");
    poisson->setPos(8,8);
    mainScene->addItem(poisson);

    populateScene();

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
        if(MovePingouinToTop())
        {
            pingouin->moveBy(0, -1);
            pingouin->setPlayerOrientation("up"); //definir l'orientation du joueur
        }
    }
    if(event->key() == Qt::Key_S)
    {
        if(MovePingouinToBottom())
        {
            pingouin->moveBy(0, 1);
            pingouin->setPlayerOrientation("down");
        }
    }
    if(event->key() == Qt::Key_A)
    {
        if(MovePingouinToLeft())
        {
            pingouin->moveBy(-1, 0);
            pingouin->setPlayerOrientation("left");
        }
    }
    if(event->key() == Qt::Key_D)
    {
        if(MovePingouinToRight())
        {
            pingouin->moveBy(1, 0);
            pingouin->setPlayerOrientation("right");
        }
    }
    if(event->key() == Qt::Key_0)
    {
        MenuStart* menuStart = new MenuStart();
        mainScene->addWidget(menuStart);
    }
}


bool Gameboard::MovePingouinToLeft()
{
    if (pingouin->pos().x() > viewStartPostionY)
    {
        return MovePingouin(pingouin->CollidesLeft(), 'l');
    }
    else{
        return false;
    }
}
bool Gameboard::MovePingouinToRight()
{
    if (pingouin->pos().x() < viewPositionX-Gameboard::getGameSquares())
    {
        return MovePingouin(pingouin->CollidesRight(), 'r');
    }
    else{
        return false;
    }
}
bool Gameboard::MovePingouinToTop()
{
    // Determiner si le joueur sort de la vue
    if (pingouin->pos().y() > viewStartPostionY)
    {
        return MovePingouin(pingouin->CollidesTop(), 't');
    }
    else{
        return false;
    }
}
bool Gameboard::MovePingouinToBottom()
{
    if (pingouin->pos().y() <= viewPositionY-Gameboard::getGameSquares()-8)
    {
        return MovePingouin(pingouin->CollidesBottom(), 'b');
    }
    else{
        return false;
    }
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
        else if(typeid(*CollidingItems.at(i)).name() == typeid(B_Movable).name())
        {
            B_Movable *b;
            b = dynamic_cast<B_Movable*>(CollidingItems.at(i));

            bMove = true;
            if(sensDepl == 'l' && b->IsMovableToLeft() && b->pos().x() > viewStartPostionY){
                b->moveBy(-1,0);
            }
            else if(sensDepl == 'r' && b->IsMovableToRight() && b->pos().x() < viewPositionX-Gameboard::getGameSquares()){
                b->moveBy(1,0);
            }
            else if(sensDepl == 't' && b->IsMovableToTop() && b->pos().y() > viewStartPostionY){
                b->moveBy(0,-1);
            }
            else if(sensDepl == 'b' && b->IsMovableToBottom() && b->pos().y() <= viewPositionY-Gameboard::getGameSquares()-8){
                b->moveBy(0, 1);
            }
            else{
                bMove=false;
            }
        }
    }
    return bMove;
}

void Gameboard::populateScene()
{
    int Mat_Walls_Blocks[maxBlocksWidth][maxBlocksHeigh];
    int Mat_Movable_Blocks[maxBlocksWidth][maxBlocksHeigh];
    int Mat_Items[maxBlocksWidth][maxBlocksHeigh];
    int Mat_Bonus[maxBlocksWidth][maxBlocksHeigh];
    int Mat_Enemies[maxBlocksWidth][maxBlocksHeigh];
    int Mat_Scene_Start[maxBlocksWidth][maxBlocksHeigh];
    int Mat_Scene_End[maxBlocksWidth][maxBlocksHeigh];
    int Mat_Doors[maxBlocksWidth][maxBlocksHeigh];
    int Mat_Water_Blocks[maxBlocksWidth][maxBlocksHeigh];

    QFile f(":/maps/maps/tutorial.txt");
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
                for (matY = 0; matY < maxBlocksHeigh; matY++)
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

            if(line[line_count].contains("type=Water_Blocks"))
            {
                line_count ++;
                line[line_count]=t.readLine();
                line_count ++;
                line[line_count]=t.readLine();
                for (matY = 0; matY < maxBlocksHeigh; matY++)
                {
                    QStringList values = line[line_count].split(",");

                    for (matX = 0; matX < maxBlocksWidth; matX++)
                    {
                        Mat_Water_Blocks[matX][matY] += values.at(matX).toInt();
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
                for (matY = 0; matY < maxBlocksHeigh; matY++)
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

            if(line[line_count].contains("type=NoMoves_Blocks"))
            {
                line_count ++;
                line[line_count]=t.readLine();
                line_count ++;
                line[line_count]=t.readLine();

                for (matY = 0; matY < maxBlocksHeigh; matY++)
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

                for (matY = 0; matY < maxBlocksHeigh; matY++)
                {
                    QStringList values = line[line_count].split(",");

                    for (matX = 0; matX < maxBlocksWidth; matX++)
                    {
                        Mat_Movable_Blocks[matX][matY] += values.at(matX).toInt();
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

                for (matY = 0; matY < maxBlocksHeigh; matY++)
                {
                    QStringList values = line[line_count].split(",");

                    for (matX = 0; matX < maxBlocksWidth; matX++)
                    {
                        Mat_Items[matX][matY] += values.at(matX).toInt();
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

                for (matY = 0; matY < maxBlocksHeigh; matY++)
                {
                    QStringList values = line[line_count].split(",");

                    for (matX = 0; matX < maxBlocksWidth; matX++)
                    {
                        Mat_Bonus[matX][matY] += values.at(matX).toInt();
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

                for (matY = 0; matY < maxBlocksHeigh; matY++)
                {
                    QStringList values = line[line_count].split(",");

                    for (matX = 0; matX < maxBlocksWidth; matX++)
                    {
                        Mat_Enemies[matX][matY] += values.at(matX).toInt();
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

                for (matY = 0; matY < maxBlocksHeigh; matY++)
                {
                    QStringList values = line[line_count].split(",");

                    for (matX = 0; matX < maxBlocksWidth; matX++)
                    {
                        Mat_Scene_Start[matX][matY] += values.at(matX).toInt();
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

                for (matY = 0; matY < maxBlocksHeigh; matY++)
                {
                    QStringList values = line[line_count].split(",");

                    for (matX = 0; matX < maxBlocksWidth; matX++)
                    {
                        Mat_Scene_End[matX][matY] += values.at(matX).toInt();
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

                for (matY = 0; matY < maxBlocksHeigh; matY++)
                {
                    QStringList values = line[line_count].split(",");

                    for (matX = 0; matX < maxBlocksWidth; matX++)
                    {
                        Mat_Doors[matX][matY] += values.at(matX).toInt();
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

//    int Mat_Water_Blocks[maxBlocksWidth][maxBlocksHeigh];

    // Populate scene
//    int nitems = 0;
    for (int i = 0; i < maxBlocksHeigh; i++) {

        for (int j = 0; j < maxBlocksWidth; j++) {
            if (Mat_Walls_Blocks[i][j] != 0)
            {
                B_Wall *item = new B_Wall();
                item->setPos(i,j);
                mainScene->addItem(item);
//                ++nitems;
            }
            if (Mat_Movable_Blocks[i][j] != 0)
            {
                B_Movable *item = new B_Movable(i,j);
                item->addToScene(mainScene);
//                ++nitems;
            }
//            if (Mat_Items[i][j] != 0)
//            {
//                QGraphicsItem *item = new B_Wall();
//                item->setPos(QPointF(i*gameSquares, j*gameSquares));
//                mainScene->addItem(item);
//                ++nitems;
//            }
//            if (Mat_Bonus[i][j] != 0)
//            {
//                QGraphicsItem *item = new B_Wall();
//                item->setPos(QPointF(i*gameSquares, j*gameSquares));
//                mainScene->addItem(item);
//                ++nitems;
//            }
//            if (Mat_Enemies[i][j] != 0)
//            {
//                QGraphicsItem *item = new B_Wall();
//                item->setPos(QPointF(i*gameSquares, j*gameSquares));
//                mainScene->addItem(item);
//                ++nitems;
//            }
//            if (Mat_Scene_Start[i][j] != 0)
//            {
//                QGraphicsItem *item = new B_Wall();
//                item->setPos(QPointF(i*gameSquares, j*gameSquares));
//                mainScene->addItem(item);
//                ++nitems;
//            }
//            if (Mat_Scene_End[i][j] != 0)
//            {
//                QGraphicsItem *item = new B_Wall();
//                item->setPos(QPointF(i*gameSquares, j*gameSquares));
//                mainScene->addItem(item);
//                ++nitems;
//            }
//            if (Mat_Doors[i][j] != 0)
//            {
//                QGraphicsItem *item = new B_Wall();
//                item->setPos(QPointF(i*gameSquares, j*gameSquares));
//                mainScene->addItem(item);
//                ++nitems;
//            }
            if (Mat_Water_Blocks[i][j] != 0)
            {
                B_Water *item = new B_Water();
                item->setPos(i,j);
                mainScene->addItem(item);
            }
        }
    }
//    qDebug() << nitems;
}

int Gameboard::getGameSquares()
{
    return gameSquares;
}

