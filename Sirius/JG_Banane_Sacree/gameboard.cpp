#include "gameboard.h"
#include "p_penguin.h"
#include "b_wall.h"
#include "b_movable.h"
#include <QList>
#include <QDebug>

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
    startingPoint = QPoint (10,10); // 20x15
    QString sceneToLoad = ":/maps/maps/tutorial.png";

    this->setWindowTitle(windowTitle);
    //this->setFixedSize(windowSizeX,windowSizeY);
    this->resize(windowSizeX,windowSizeY);

    mainScene = new QGraphicsScene(this);
    playerView = new QGraphicsView(this);

    //On crée la scene
    QPixmap loadScene(sceneToLoad);
    mainScene->setBackgroundBrush(loadScene);

    playerView->setHorizontalScrollBarPolicy (Qt::ScrollBarAlwaysOff);
    playerView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //playerView->setFocus();
    playerView->setSceneRect(viewStartPostionX,viewStartPostionY,viewPositionX,viewPositionX);

    B_Movable *bd = new B_Movable(15,10);
    B_Movable *bd1 = new B_Movable(5,10);

    bd->addToScene(mainScene);
    bd1->addToScene(mainScene);


    //On ajoute le joueur
    pingouin = new Pingouin(gameSquares);
    pingouin->addToScene(mainScene);
    pingouin->setPos(startingPoint.x(), startingPoint.y());

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
    if (pingouin->pos().x() < viewPositionX-pingouin->getPlayerSizeY())
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
    if (pingouin->pos().y() <= viewPositionY-pingouin->getPlayerSizeX()-8)
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

        if(typeid(*CollidingItems.at(i)).name() == typeid(B_Wall).name())                //SNOW
        {
            bMove = false;
        }
        else if(typeid(*CollidingItems.at(i)).name() == typeid(B_Movable).name())  //BLOC_DEPL
        {
            B_Movable *b;
            b = dynamic_cast<B_Movable*>(CollidingItems.at(i));

            bMove = true;
            if(sensDepl == 'l' && b->IsMovableToLeft() && b->pos().x() > viewStartPostionY){
                b->moveBy(-1,0);
            }
            else if(sensDepl == 'r' && b->IsMovableToRight() && b->pos().x() < viewPositionX-b->getWidth()){
                b->moveBy(1,0);
            }
            else if(sensDepl == 't' && b->IsMovableToTop() && b->pos().y() > viewStartPostionY){
                b->moveBy(0,-1);
            }
            else if(sensDepl == 'b' && b->IsMovableToBottom() && b->pos().y() <= viewPositionY-b->getWidth()-8){
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
    int Mat_Walls[60][30];
    QFile f(":/population/maps/tutorial.txt");
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
//STEVE: Il faut debeuger ici: B_Wall() avec item->setPos(QPointF(i*32+2, j*32+2));
//ou B_Wall(i*32+2,j*32+2) devrait marcher, car la c'est du bricolage :(
//                qDebug() << "I am in, i= " << i << "j= " << j;
                //QGraphicsItem *item = new B_Wall(i*32+2,j*32+2);
                QGraphicsItem *item = new B_Wall(0,0);
                item->setPos(QPointF(i*32+2, j*32+2));
                mainScene->addItem(item);
                ++nitems;
            }
        }
    }
    qDebug() << nitems;
}

