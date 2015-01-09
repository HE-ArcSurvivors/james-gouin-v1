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
#include "level.h"

#include <QList>
#include <QDebug>
#include <QGraphicsItemGroup>
#include <QApplication>
#include <QGraphicsView>
#include <QKeyEvent>
#include <QFile>
#include <QFormLayout>
#include <QGroupBox>
#include <QLabel>
#include <QPoint>
#include <QPushButton>
#include <QMessageBox>
#include <QTimer>

#define SLIDE_SPEED (80)

#if defined(__unix__) || (defined(__APPLE__) && defined(__MACH__))
#else
#include <typeinfo.h>
#endif

int Gameboard::gameSquares = 32;
int Gameboard::sizeX = 20;
int Gameboard::sizeY = 15;

Gameboard::Gameboard(QWidget *parent) : QWidget(parent)
{
//    currentLevel = new Level("test");
    currentLevel = new Level("tutorial");

    // Les Variables par default du jeu
    windowTitle = tr("James Gouin et la Banane Sacrée");
    windowSizeX = sizeX*gameSquares;
    windowSizeY = sizeY*gameSquares;

    menuPauseSizeX = 400;
    menuPauseSizeY = 400;
    toggleGrabTheWorld = false;
    toggleMenuPause = false;
    isSliding = false;

    moveBloc = NULL;
    checkpoint = new QPoint();

    this->setWindowTitle(windowTitle);
    this->setFixedSize(windowSizeX,windowSizeY);
    this->resize(windowSizeX,windowSizeY);

    mainScene = new QGraphicsScene(this);
    mainScene = currentLevel->populateScene();

    viewRequested = currentLevel->getViewStart();
    setViewPosition();

    playerView = new QGraphicsView(this);

    playerView->setHorizontalScrollBarPolicy (Qt::ScrollBarAlwaysOff);
    playerView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    playerView->setSceneRect(viewPositionX,viewPositionY,sizeX*gameSquares,sizeY*gameSquares);

    //On position la vue
    playerView->setScene(mainScene);
    grabKeyboard();

    //On ajoute le joueur
    pingouin = new Pingouin(gameSquares);
    pingouin->addToScene(mainScene);
    pingouin->setPos(currentLevel->getStartingPoint()->x(), currentLevel->getStartingPoint()->y());
    pingouin->addObjectToSacoche(new Object("Poisson"));
    saveCheckpoint();

    menuPauseInGame = new M_Pause(this);
    proxy = mainScene->addWidget(menuPauseInGame);
    proxy->hide();
   
    //initialisation des timer
    timerPingouinSlide = new QTimer();
    timerBlocDeplSlide = new QTimer();
    connect(timerPingouinSlide, SIGNAL(timeout()), this, SLOT(SlidePingouin()));
    connect(timerBlocDeplSlide, SIGNAL(timeout()), this, SLOT(SlideBloc()));
}
void Gameboard::SlideBloc()
{
    for(int i=0; i<listSlindingBlocs.size(); i++)
    {
        B_Movable* SlidingBloc = listSlindingBlocs.at(i).slidingMovable;

        bool removeBloc = true;

        if(SlidingBloc->isSlide())
        {
            switch (listSlindingBlocs.at(i).sens)
            {
            case 't':

                if(SlidingBloc->IsMovableToTop()) //&& Qu'il ne sorte pas de la view
                {
                    SlidingBloc->moveBy(0,-1);
                    if(checkPosition(SlidingBloc))
                    {
                        SinkMovable(SlidingBloc);
                        removeBloc = false;
                    }
                }

                break;

            case 'b':

                if(SlidingBloc->IsMovableToBottom())
                {
                    SlidingBloc->moveBy(0,1);
                    if(checkPosition(SlidingBloc))
                    {
                        SinkMovable(SlidingBloc);
                        removeBloc = false;
                    }
                }

                break;

            case 'l':

                if(SlidingBloc->IsMovableToLeft())
                {
                    SlidingBloc->moveBy(-1,0);
                    SinkMovable(SlidingBloc);
                    if(checkPosition(SlidingBloc))
                    {
                        SinkMovable(SlidingBloc);
                        removeBloc = false;
                    }
                }

                break;

            case 'r':

                if(SlidingBloc->IsMovableToRight())
                {
                    SlidingBloc->moveBy(1,0);
                    SinkMovable(SlidingBloc);
                    if(checkPosition(SlidingBloc))
                    {
                        SinkMovable(SlidingBloc);
                        removeBloc = false;
                    }
                }

                break;

            default:
                break;
            }
        }

        if(removeBloc)
        {
            listSlindingBlocs.removeAt(i);
        }
    }

    if(listSlindingBlocs.size() == 0)
    {
        timerBlocDeplSlide->stop();
    }
}

void Gameboard::SlidePingouin()
{
    bool endSlide = true;

    switch (cSensPingouinSlide)
    {
    case 't':

        if(MovePingouinToTop() && pingouin->isSlide())
        {
                if(!CheckGameOver())
                {
                    CheckItem();
                    CheckChangeView(cSensPingouinSlide);
                    pingouin->moveBy(0, -1);

                    if(moveBloc != NULL)
                    {
                        moveBloc->moveBy(0,-1);
                        SinkMovable(moveBloc);
                        moveBloc = NULL;
                    }
                }
             endSlide = false;

        }

        break;

    case 'b':

        if(MovePingouinToBottom() && pingouin->isSlide())
        {
            if(!CheckGameOver())
            {
                CheckItem();
                CheckChangeView(cSensPingouinSlide);
                pingouin->moveBy(0, 1);

                if(moveBloc != NULL)
                {
                    moveBloc->moveBy(0,1);
                    SinkMovable(moveBloc);
                    moveBloc = NULL;
                }
            }

            endSlide = false;
        }
        break;

    case 'l':

        if(MovePingouinToLeft() && pingouin->isSlide())
        {
           if(!CheckGameOver())
           {
                CheckItem();
                CheckChangeView(cSensPingouinSlide);
                pingouin->moveBy(-1, 0);

                if(moveBloc != NULL)
                {
                    moveBloc->moveBy(-1,0);
                    SinkMovable(moveBloc);
                    moveBloc = NULL;
                }
            }
           endSlide = false;
        }
        break;

    case 'r':

        if(MovePingouinToRight() && pingouin->isSlide())
        {
            if(!CheckGameOver())
                {
                   pingouin->moveBy(1, 0);
                   CheckItem();
                   CheckChangeView(cSensPingouinSlide);

                   if(moveBloc != NULL)
                    {
                        moveBloc->moveBy(1,0);
                        SinkMovable(moveBloc);
                        moveBloc = NULL;
                    }
                 }

               endSlide = false;
        }
        break;
    default:
        break;
    }

    if(endSlide)
    {
        CheckItem();
        CheckChangeView(cSensPingouinSlide);
        timerPingouinSlide->stop();
        isSliding=false;
    }
}

Gameboard::~Gameboard(){

}


void Gameboard::setViewPosition()
{
    int x = viewRequested.x();
    int y = viewRequested.y();

    if(x==1) { viewPositionX = 1; }
    else
    {
        viewPositionX = (x-1)*20*gameSquares;
    }

    if(y==1)
    {
        viewPositionY = 1;
    }
    else
    {
        viewPositionY = (y-1)*15*gameSquares;
    }
}

void Gameboard::SinkMovable(B_Movable *b)
{
    QList<QGraphicsItem *> CollidingItems = b->CollidesCenter();
    for(int i=0; i<CollidingItems.length(); i++)
    {
        QPoint p = b->getPos();
        if(typeid(*CollidingItems.at(i)).name() == typeid(B_Water).name())
        {
            //SINK IT !
        
            qDebug() << "Sink it ! : " << p.x() << " " << p.y();

            b->removeFromScene(mainScene);
            mainScene->removeItem(CollidingItems.at(i));

            S_Snow *sunk = new S_Snow(p.x(),p.y());
            mainScene->addItem(sunk);
        }
        if(typeid(*CollidingItems.at(i)).name() == typeid(S_ViewTransition).name())
        {
            b->removeFromScene(mainScene);
            mainScene->removeItem(CollidingItems.at(i));

            B_Wall *wall = new B_Wall(p.x(),p.y());
            mainScene->addItem(wall);
        }
        if(typeid(*CollidingItems.at(i)).name() == typeid(Object).name())
        {
            mainScene->removeItem(CollidingItems.at(i));
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
            qDebug() << objet->getName();
            pingouin->addObjectToSacoche(new Object(objet->getName()));
            mainScene->removeItem(CollidingItems.at(i));

            if(objet->getName() == "Chaussure")
            {
                pingouin->setSlideAble(false);
            }
        }
    }
}

void Gameboard::CheckChangeView(char sens)
{
    QList<QGraphicsItem *> CollidingItems = pingouin->CollidesCenter();
    for(int i=0; i<CollidingItems.length(); i++)
    {
        if(typeid(*CollidingItems.at(i)).name() == typeid(S_ViewTransition).name())
        {
            if(pingouin->checkObjectSacoche(*currentLevel->getNeededItem()))
            {
                pingouin->removeObjectToSacoche(*currentLevel->getNeededItem());
                if(pingouin->checkObjectSacoche(QString("Chaussure")))
                {
                    pingouin->removeObjectToSacoche(QString("Chaussure"));
                    pingouin->setSlideAble(true);
                }
                qDebug() << pingouin->x() << " " << pingouin->y();
                saveCheckpoint();

                qDebug() << "ViewRequested : " << viewRequested.x() << " " << viewRequested.y();

                if(sens == 't')
                {
                    qDebug() << "Up";
                    this-> checkpoint->setY(checkpoint->y()-gameSquares);
                    viewRequested.setY(viewRequested.y()-1);
                }
                if(sens == 'b')
                {
                    qDebug() << "Down";
                    this->checkpoint->setY(checkpoint->y()+gameSquares);
                    viewRequested.setY(viewRequested.y()+1);
                }
                if(sens == 'l')
                {
                    qDebug() << "Left";
                    this->checkpoint->setX(checkpoint->x()-gameSquares);
                    viewRequested.setX(viewRequested.x()-1);
                }
                if(sens == 'r')
                {
                    qDebug() << "Right";

                    this->checkpoint->setX(checkpoint->x()+gameSquares);
                    viewRequested.setX(viewRequested.x()+1);
                }

                qDebug() << "ViewRequested : " << viewRequested.x() << " " << viewRequested.y();
                loadCheckpoint();
                setViewPosition();
                playerView->setSceneRect(viewPositionX,viewPositionY,windowSizeX,windowSizeY);

            }
            else
            {
                qDebug() << "Pas encore de " << *(currentLevel->getNeededItem()) << " ! ";
                pingouin->moveBack();
            }
        }
    }
}

void Gameboard::MoveBloc(char sens)
{
    switch(sens)
    {
        case 't':
            moveBloc->moveBy(0,-1);
        break;
        case 'b':
            moveBloc->moveBy(0,1);
        break;
        case 'l':
            moveBloc->moveBy(-1,0);
        break;
        case 'r':
            moveBloc->moveBy(1,0);
        break;
    }

    SinkMovable(moveBloc);


    if(moveBloc->isSlide())
    {
        slideBloc sb;
        sb.slidingMovable = moveBloc;
        sb.sens = sens;


        listSlindingBlocs.append(sb);

        timerBlocDeplSlide->start(SLIDE_SPEED);
    }

    moveBloc = NULL;
}

bool Gameboard::checkPosition(QGraphicsItem *object)
{
    if(object->y() < (viewRequested.y()-1)*15*gameSquares)
    {
        qDebug() << "Déplacement Impossible : " << object->y() << " < " << (viewRequested.y()-1)*15*gameSquares;
        return false;
    }

    if(object->y() > viewRequested.y()*15*gameSquares-gameSquares)
    {
        qDebug() << "Déplacement Impossible : " << object->y() << " > " << viewRequested.y()*15*gameSquares-gameSquares;
        return false;
    }

    if(object->x() < (viewRequested.x()-1)*20*gameSquares)
    {
        qDebug() << "Déplacement Impossible : " << object->x() << " < " << (viewRequested.x()-1)*20*gameSquares;
        return false;
    }

    if(object->x() > viewRequested.x()*20*gameSquares-gameSquares)
    {
        qDebug() << "Déplacement Impossible : " << object->x() << " > " << viewRequested.x()*20*gameSquares-gameSquares;
        return false;
    }

    return true;
}

//http://doc.qt.digia.com/4.6/qt.html#Key-enum
void Gameboard::keyPressEvent(QKeyEvent *event)
{
    if(!toggleMenuPause && !isSliding)
    {
        if(event->key() == Qt::Key_W || event->key() == Qt::Key_Up)
        {
            pingouin->setPlayerOrientation("up"); //definir l'orientation du joueur

            if(MovePingouinToTop())
            {
                pingouin->moveBy(0, -1);

                if(!CheckGameOver())
                {
                    CheckItem();
                    CheckChangeView('t');

                    if(moveBloc != NULL)
                    {
                        MoveBloc('t');
                    }
                    if(pingouin->isSlide())
                    {
                        isSliding=true;
                        cSensPingouinSlide = 't';
                        timerPingouinSlide->start(SLIDE_SPEED);
                    }
                }
            }

        }
        if(event->key() == Qt::Key_S || event->key() == Qt::Key_Down)
        {
            pingouin->setPlayerOrientation("down");

            if(MovePingouinToBottom())
            {
                pingouin->moveBy(0, 1);

                if(!CheckGameOver())
                {
                    CheckItem();
                    CheckChangeView('b');
                    if(moveBloc != NULL)
                    {
                        MoveBloc('b');
                    }
                    if(pingouin->isSlide())
                    {
                        isSliding=true;
                        cSensPingouinSlide = 'b';
                        timerPingouinSlide->start(SLIDE_SPEED);
                    }
                }
            }
        }
        if(event->key() == Qt::Key_A || event->key() == Qt::Key_Left)
        {
            pingouin->setPlayerOrientation("left");

            if(MovePingouinToLeft())
            {
                pingouin->moveBy(-1, 0);

                if(!CheckGameOver())
                {
                    CheckItem();
                    CheckChangeView('l');
                    if(moveBloc != NULL)
                    {
                        MoveBloc('l');
                    }
                    if(pingouin->isSlide())
                    {
                        isSliding=true;
                        cSensPingouinSlide = 'l';
                        timerPingouinSlide->start(SLIDE_SPEED);
                    }
                }
            }
        }
        if(event->key() == Qt::Key_D || event->key() == Qt::Key_Right)
        {
            pingouin->setPlayerOrientation("right");

            if(MovePingouinToRight())
            {
                pingouin->moveBy(1, 0);

                if(!CheckGameOver())
                {
                    CheckItem();
                    CheckChangeView('r');
                    if(moveBloc != NULL)
                    {
                        MoveBloc('r');
                    }
                    if(pingouin->isSlide())
                    {
                        isSliding=true;
                        cSensPingouinSlide = 'r';
                        timerPingouinSlide->start(SLIDE_SPEED);
                    }
                }
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
            B_Movable *b;
            b = dynamic_cast<B_Movable*>(CollidingItems.at(i));

            if(sensDepl == 'l' && b->IsMovableToLeft() && checkPosition(b))
            {
                moveBloc = b;
                bMove = true;
            }
            else if(sensDepl == 'r' && b->IsMovableToRight() && checkPosition(b)){
                moveBloc = b;
                bMove = true;
            }
            else if(sensDepl == 't' && b->IsMovableToTop() && checkPosition(b)){
                moveBloc = b;
                bMove = true;
            }
            else if(sensDepl == 'b' && b->IsMovableToBottom() && checkPosition(b)){
                moveBloc = b;
                bMove = true;
            }
            else{
                bMove=false;
            }
        } 
        else if(typeid(*CollidingItems.at(i)).name() == typeid(S_ViewTransition).name())
        {
            bMove = true;
        }
    }
    if(bMove && (!checkPosition(pingouin)))
    {
        bMove=false;
    }
    return bMove;
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
        timerPingouinSlide->stop();
        menuPauseInGame->setGeometry(viewPositionX+windowSizeX/2-menuPauseSizeX/2,viewPositionY+windowSizeY/2-menuPauseSizeY/2,menuPauseSizeX,menuPauseSizeY);

        proxy->show();

    }else{

        proxy->hide();
        timerPingouinSlide->start(SLIDE_SPEED);
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
            if(typeid(*item).name() == typeid(Object).name())
            {
                item->setZValue(2);
            }
        }
    }

}

void Gameboard::resumeGame()
{
    pauseMenu();
}

void Gameboard::exitGame()
{
    QMessageBox msgBox;
    msgBox.setText(tr("Vous êtes sur le point de quitter le jeu"));
    msgBox.setInformativeText("Voulez vous sauvegarder ?");
    msgBox.addButton("Ne pas Sauvegarder", QMessageBox::DestructiveRole);
    msgBox.addButton("Annuler", QMessageBox::RejectRole);
    msgBox.addButton("Sauvegarder", QMessageBox::AcceptRole);

    int ret = msgBox.exec();
    switch (ret) {
    case QMessageBox::AcceptRole:
        close();
        break;
    case QMessageBox::RejectRole:

        break;
    case QMessageBox::DestructiveRole:
        close();
        break;
    default:
        // should never be reached
        break;
    }
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
    CheckItem();
    qDebug() << "LOAD CHECKPOINT" << (checkpoint->x()+gameSquares)/gameSquares << " " << (checkpoint->y()+gameSquares)/gameSquares;
}

