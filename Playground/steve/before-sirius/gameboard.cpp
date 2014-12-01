#include "gameboard.h"
#include "pingouin.h"
#include "neige.h"
#include "blocdeplacable.h"
#include <QList>;
#include <QDebug>;

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
    startingPoint = QPoint (5,5); // 20x15
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


    //surfaces
    Neige *n = new Neige(5,5);

    BlocDeplacable *bd = new BlocDeplacable(15,10);
    BlocDeplacable *bd1 = new BlocDeplacable(5,10);

    mainScene->addItem(n);
    bd->addToScene(mainScene);
    bd1->addToScene(mainScene);


    //On ajoute le joueur
    pingouin = new Pingouin(gameSquares);
    pingouin->addToScene(mainScene);
    pingouin->setPos(startingPoint.x(), startingPoint.y());


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
//        QMessageBox m;
//        m.setText(typeid(*CollidingItems.at(i)).name());
//        m.exec();

        if(typeid(*CollidingItems.at(i)).name() == typeid(Neige).name())                //SNOW
        {
            bMove = false;
        }
        else if(typeid(*CollidingItems.at(i)).name() == typeid(BlocDeplacable).name())  //BLOC_DEPL
        {
            BlocDeplacable *b;
            b = dynamic_cast<BlocDeplacable*>(CollidingItems.at(i));

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

