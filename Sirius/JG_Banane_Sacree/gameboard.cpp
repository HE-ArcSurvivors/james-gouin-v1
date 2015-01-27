/*********************************************************************************
* Copyright © Haute-Ecole ARC - All Rights Reserved
* Copyright © Banana Rocket - All Rights Reserved
*
* This file is part of <P2 Qt Project: James Gouin et la Banane Sacrée>.
*
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Claret-Yakovenko Roman <romain.claret@rocla.ch>, 27 January 2015
* Written by Divernois Margaux <margaux.divernois@gmail.com>, 27 January 2015
* Written by Visinand Steve <visinandst@gmail.com>, 27 January 2015
**********************************************************************************/

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
#include "s_dialog.h"
#include "level.h"
#include "ennemi.h"
#include "e_renard.h"
#include "e_loup.h"
#include "profil.h"

#include <QtWidgets>
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
#include <QGraphicsProxyWidget>

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
    // Les Variables par default du jeu
    windowTitle = tr("James Gouin et la Banane Sacrée");
    windowSizeX = sizeX*gameSquares;
    windowSizeY = sizeY*gameSquares;

    setFocus();
    grabKeyboard();
    this->setWindowTitle(windowTitle);
    this->setFixedSize(windowSizeX,windowSizeY);
    this->resize(windowSizeX,windowSizeY);

    mainScene = new QGraphicsScene(this);
    playerView = new QGraphicsView(this);
    pingouin = new Pingouin();
    checkpoint = new QPoint(0,0);
    playerProfil = new Profil();
    currentLevel = new Level(0, this);

    playerView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    playerView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    setProxy();

    isSliding = false;
    moveBloc = NULL;
    endable = false;

    //initialisation des timer
    timerPingouinSlide = new QTimer();
    timerBlocDeplSlide = new QTimer();
    connect(timerPingouinSlide, SIGNAL(timeout()), this, SLOT(SlidePingouin()));
    connect(timerBlocDeplSlide, SIGNAL(timeout()), this, SLOT(SlideBloc()));

    //pour annimer !
    timer = new QTimer();
    setTimer();
    timer->start(100); //10 fois par sec
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

                if(SlidingBloc->IsMovableToTop())
                {
                    SlidingBloc->moveBy(0,-1);
                    fixeMovable(SlidingBloc);
//                    if(checkPosition(SlidingBloc))
//                    {
                        removeBloc = false;
//                    }
                }

                break;

            case 'b':

                if(SlidingBloc->IsMovableToBottom())
                {
                    SlidingBloc->moveBy(0,1);
                    fixeMovable(SlidingBloc);
//                    if(checkPosition(SlidingBloc))
//                    {
                        removeBloc = false;
//                    }
                }

                break;

            case 'l':

                if(SlidingBloc->IsMovableToLeft())
                {
                    SlidingBloc->moveBy(-1,0);
                    fixeMovable(SlidingBloc);
//                    if(checkPosition(SlidingBloc))
//                    {
                        removeBloc = false;
//                    }
                }

                break;

            case 'r':

                if(SlidingBloc->IsMovableToRight())
                {
                    SlidingBloc->moveBy(1,0);
                    fixeMovable(SlidingBloc);
//                    if(checkPosition(SlidingBloc))
//                    {
                        removeBloc = false;
//                    }
                }

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
            pingouin->moveBy(0, -1);
            checkPositionEvents();
            checkChangeView(cSensPingouinSlide);

            if(moveBloc != NULL)
            {
                moveBloc->moveBy(0,-1);
                fixeMovable(moveBloc);
                moveBloc = NULL;
            }
             endSlide = false;

        }

        break;

    case 'b':

        if(MovePingouinToBottom() && pingouin->isSlide())
        {
            checkPositionEvents();
            pingouin->moveBy(0, 1);
            checkChangeView(cSensPingouinSlide);

            if(moveBloc != NULL)
            {
                moveBloc->moveBy(0,1);
                fixeMovable(moveBloc);
                moveBloc = NULL;
            }

            endSlide = false;
        }
        break;

    case 'l':

        if(MovePingouinToLeft() && pingouin->isSlide())
        {
            pingouin->moveBy(-1, 0);
            checkPositionEvents();
            checkChangeView(cSensPingouinSlide);

            if(moveBloc != NULL)
            {
                moveBloc->moveBy(-1,0);
                fixeMovable(moveBloc);
                moveBloc = NULL;
            }

           endSlide = false;
        }
        break;

    case 'r':

        if(MovePingouinToRight() && pingouin->isSlide())
        {
           pingouin->moveBy(1, 0);
           checkPositionEvents();
           checkChangeView(cSensPingouinSlide);

           if(moveBloc != NULL)
            {
                moveBloc->moveBy(1,0);
                fixeMovable(moveBloc);
                moveBloc = NULL;
           }

           endSlide = false;
        }
        break;
    default:
        break;
    }

    if(endSlide)
    {
        checkPositionEvents();
        checkChangeView(cSensPingouinSlide);
        timerPingouinSlide->stop();
        isSliding=false;
        moveBloc = NULL;
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

void Gameboard::fixeMovable(B_Movable *b)
{
    QList<QGraphicsItem *> CollidingItems = b->CollidesCenter();
    for(int i=0; i<CollidingItems.length(); i++)
    {
        QPoint p = b->getPos();
        if(typeid(*CollidingItems.at(i)).name() == typeid(B_Water).name())
        {
            qDebug() << "Sink it ! : " << p.x() << " " << p.y();

            b->removeFromScene(mainScene);
            mainScene->removeItem(CollidingItems.at(i));

            S_Snow *sunk = new S_Snow(p.x(),p.y());
            sunk->setColor("white");
            mainScene->addItem(sunk);
        }
        if(typeid(*CollidingItems.at(i)).name() == typeid(S_ViewTransition).name())
        {
            QString text = tr("Tu as bloqué ta sortie!");
            setPositionCenter(dialog);
            dialogProxy->show();
            dialog->setText(text,2);

            dialogToogle = true;

            b->removeFromScene(mainScene);
            mainScene->removeItem(CollidingItems.at(i));

            B_Wall *wall = new B_Wall(p.x(),p.y());
            wall->setColor("gray");
            mainScene->addItem(wall);
        }
        if(typeid(*CollidingItems.at(i)).name() == typeid(Object).name())
        {
            mainScene->removeItem(CollidingItems.at(i));

            Object *objet = dynamic_cast<Object*>(CollidingItems.at(i));

            if(objet->getName() != "Oeuf")
            {
                restartEnigma();

                QString text = tr("OUCH! Ce bloc vient d'écraser un ");
                text.append(objet->getName());
                text.append(tr("! Tu recommences au dernier checkpoint! "));
                setPositionCenter(dialog);
                dialogProxy->show();
                dialog->setText(text,2);
                dialogToogle = true;
            }
        }
    }
}

void Gameboard::checkPositionEvents()
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
            else if(objet->getName() == "Oeuf")
            {
                if(playerProfil->getNbLive()<Profil::NBMAXVIE)
                {
                    playerProfil->setNbLive(playerProfil->getNbLive()+1);
                    lifeList->updateHearts(playerProfil->getNbLive());
                }
                else
                {
                    QString text(tr("Le nombre de vies maximum de %1 a été atteint").arg(Profil::NBMAXVIE));
                    setPositionCenter(dialog);
                    dialogProxy->show();
                    dialog->setText(text,2);
                    dialogToogle = true;
                }
            }

            objectList->reloadObjectList(pingouin->getSacoche());
            setPositionBottom(objectList);
            objectList->show();
        }
        if(typeid(*CollidingItems.at(i)).name() == typeid(S_Dialog).name())
        {
            S_Dialog *item = dynamic_cast<S_Dialog*>(CollidingItems.at(i));
            mainScene->removeItem(CollidingItems.at(i));

            setPositionCenter(dialog);
            dialogProxy->show();
            dialog->setText(currentLevel->getDialogText(item->getDialogNumber()),1);
            dialogToogle = true;
        }
        if(typeid(*CollidingItems.at(i)).name() == typeid(B_Water).name())
        {
            restartEnigma();

            setPositionCenter(dialog);
            dialogProxy->show();
            dialog->setText("Plouf, dans l'eau! Tu recommences au dernier checkpoint",2);
            dialogToogle = true;
        }
        if(typeid(*CollidingItems.at(i)).name() == typeid(E_Renard).name() || typeid(*CollidingItems.at(i)).name() == typeid(E_Loup).name())
        {
            restartEnigma();

            setPositionCenter(dialog);
            dialogProxy->show();
            dialog->setText("Tu t'es fait repéré par un ennemi",2);
            dialogToogle = true;
        }
    }
    if(pingouin->x() == currentLevel->getUnlockEndPoint().x() && pingouin->y() == currentLevel->getUnlockEndPoint().y())
    {
        qDebug() << "UNLOCKEND";

        int levelNumber = currentLevel->getLevelNumber();
        QString background = ":/maps/maps/";
        background.append(QString("%1").arg(levelNumber));
        background.append("Ouvert");
        background.append(".png");
        QPixmap pixmapBackground(background);

        if(!pixmapBackground.isNull())
        {
            mainScene->setBackgroundBrush(pixmapBackground);
        }

        endable = true;
    }
}

void Gameboard::checkChangeView(char sens)
{
    QList<QGraphicsItem *> CollidingItems = pingouin->CollidesCenter();
    for(int i=0; i<CollidingItems.length(); i++)
    {
        if(typeid(*CollidingItems.at(i)).name() == typeid(S_ViewTransition).name())
        {
            S_ViewTransition *bloc = dynamic_cast<S_ViewTransition*>(CollidingItems.at(i));
            if(bloc->isEndLevel() && endable)
            {
                endable = false;
                pingouin->emptySacoche();
                setLevel(bloc->getNextLevel());
                setProxy();
                setFirstDialog();
            }
            else if(bloc->isEndLevel())
            {
                pingouin->moveBack();
            }
            else
            {
                if(!bloc->isNeedingItem())
                {
                    if(pingouin->checkObjectSacoche(QString("Chaussure")))
                    {
                        pingouin->removeObjectFromSacoche(QString("Chaussure"));
                        pingouin->setSlideAble(true);
                    }

                    ChangeView(sens);
                }
                else if(bloc->isNeedingItem() && pingouin->checkObjectSacoche(bloc->getNeededItem(), bloc->getNbItem()))
                {
                    if(pingouin->checkObjectSacoche(QString("Chaussure")))
                    {
                        pingouin->removeObjectFromSacoche(QString("Chaussure"));
                        pingouin->setSlideAble(true);
                    }

                    ChangeView(sens);
                }
                else
                {
                    QString text = tr("Il te faut ");
                    text.append(QString::number(bloc->getNbItem()));
                    text.append(tr("x l'objet \""));
                    text.append((bloc->getNeededItem()));
                    text.append(tr("\" pour aller plus loin ;) "));

                    setPositionCenter(dialog);
                    dialogProxy->show();
                    dialog->setText(text,2);

                    dialogToogle = true;

                    pingouin->moveBack();
                }
            }
        }
    }
}

void Gameboard::ChangeView(char sens)
{
    saveCheckpoint();
    pingouin->emptyTempSacoche();

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

    objectList->reloadObjectList(pingouin->getSacoche());
    setPositionBottom(objectList);
    setPositionCenter(dialog);
    setPositionTop(lifeList);
}

void Gameboard::setPositionBottom(QWidget* widget)
{
    int width = widget->width();
    int height = widget->height();

    widget->setGeometry(viewPositionX+gameSquares*(sizeX)-width,viewPositionY+gameSquares*(sizeY)-height,width,height);
}

void Gameboard::setPositionCenter(QWidget* widget)
{
    int width = widget->width();
    int height = widget->height();

    widget->setGeometry(viewPositionX+(gameSquares*(sizeX)-width)/2,viewPositionY+(gameSquares*(sizeY)-height)/2,width,height);
}

void Gameboard::setPositionTop(QWidget* widget)
{
    int width = widget->width();
    int height = widget->height();

    widget->setGeometry(viewPositionX,viewPositionY,width,height);
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

    fixeMovable(moveBloc);


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
    if(object->y() < (viewRequested.y()-1)*15*gameSquares+1)
    {
        qDebug() << "Déplacement Impossible : " << object->y() << " < " << (viewRequested.y()-1)*15*gameSquares;
        return false;
    }

    if(object->y() > viewRequested.y()*15*gameSquares-gameSquares+1)
    {
        qDebug() << "Déplacement Impossible : " << object->y() << " > " << viewRequested.y()*15*gameSquares-gameSquares;
        return false;
    }

    if(object->x() < (viewRequested.x()-1)*20*gameSquares+1)
    {
        qDebug() << "Déplacement Impossible : " << object->x() << " < " << (viewRequested.x()-1)*20*gameSquares;
        return false;
    }

    if(object->x() > viewRequested.x()*20*gameSquares-gameSquares+1)
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
        if(!dialogToogle)
        {
            if(event->key() == Qt::Key_W || event->key() == Qt::Key_Up)
            {
                pingouin->setPlayerOrientation("up"); //definir l'orientation du joueur

                if(MovePingouinToTop())
                {
                    pingouin->moveBy(0, -1);

                    checkPositionEvents();
                    checkChangeView('t');

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
            if(event->key() == Qt::Key_S || event->key() == Qt::Key_Down)
            {
                pingouin->setPlayerOrientation("down");

                if(MovePingouinToBottom())
                {
                    pingouin->moveBy(0, 1);

                    checkPositionEvents();
                    checkChangeView('b');
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
            if(event->key() == Qt::Key_A || event->key() == Qt::Key_Left)
            {
                pingouin->setPlayerOrientation("left");

                if(MovePingouinToLeft())
                {
                    pingouin->moveBy(-1, 0);


                        checkPositionEvents();
                        checkChangeView('l');
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
            if(event->key() == Qt::Key_D || event->key() == Qt::Key_Right)
            {
                pingouin->setPlayerOrientation("right");

                if(MovePingouinToRight())
                {
                    pingouin->moveBy(1, 0);


                        checkPositionEvents();
                        checkChangeView('r');
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
            if(event->key() == Qt::Key_0)
            {
                restartEnigma();
            }
        }
        else
        {
            if(event->key() == Qt::Key_Space)
            {
                dialogProxy->hide();
                dialogToogle = false;
            }
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
        else if(typeid(*CollidingItems.at(i)).name() == typeid(B_Movable).name())
        {
            B_Movable *b;
            b = dynamic_cast<B_Movable*>(CollidingItems.at(i));

            if(sensDepl == 'l' && b->IsMovableToLeft() && checkPosition(b->getCollideBlocPosition(sensDepl)))
            {
                moveBloc = b;
                bMove = true;
            }
            else if(sensDepl == 'r' && b->IsMovableToRight() && checkPosition(b->getCollideBlocPosition(sensDepl)))
            {
                moveBloc = b;
                bMove = true;
            }
            else if(sensDepl == 't' && b->IsMovableToTop() && checkPosition(b->getCollideBlocPosition(sensDepl)))
            {
                moveBloc = b;
                bMove = true;
            }
            else if(sensDepl == 'b' && b->IsMovableToBottom()  && checkPosition(b->getCollideBlocPosition(sensDepl)))
            {
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
    if(bMove && (!checkPosition(pingouin->getCollideBloc(sensDepl))))
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
    if(!toggleMenuPause)
    {
        timerPingouinSlide->stop();
        menuPauseInGame->setUnableMenu(currentLevel->getLevelNumber());
        setPositionCenter(menuPauseInGame);
        proxy->show();
        toggleMenuPause = true;
    }else{
        proxy->hide();
        toggleMenuPause = false;
        timerPingouinSlide->start(SLIDE_SPEED);
    }
}

void Gameboard::resumeGame()
{
    pauseMenu();
}

void Gameboard::restartEnigma()
{
    if(playerProfil->getNbLive()>0)
    {
        removeAllItems();
        disconnectTimer();

        playerProfil->setNbLive(playerProfil->getNbLive()-1);
        lifeList->updateHearts(playerProfil->getNbLive());

        loadLevel();
        setProxy();
    }
    else
    {
        playerProfil->setNbLive(4);
        restartLevel();

        setPositionCenter(dialog);
        dialogProxy->show();
        dialog->setText(tr("Tu as perdu toutes tes vies! Tu recommences au début du niveau."),1);
        dialogToogle = true;
    }
}

void Gameboard::restartLevel()
{
    removeAllItems();
    disconnectTimer();

    pingouin->emptySacoche();

    setLevel(currentLevel->getLevelNumber());
    setProxy();

    playerProfil->setNbLive(playerProfil->getNbLive()-1);
    lifeList->updateHearts(playerProfil->getNbLive());

    setFirstDialog();
}



void Gameboard::returnIsland()
{
    mainScene->removeItem(proxy);
    mainScene->removeItem(objectListProxy);
    mainScene->removeItem(lifeListProxy);
    mainScene->removeItem(dialogProxy);

    pingouin->emptySacoche();

    setLevel(1);
    setProxy();
    setFirstDialog();

    objectListProxy->hide();
    lifeListProxy->hide();
}

void Gameboard::exitGame()
{
    QMessageBox msgBox;
    msgBox.setText(tr("Vous êtes sur le point de quitter le jeu"));
    msgBox.setInformativeText(tr("Voulez vous sauvegarder ?"));
    msgBox.addButton(tr("Sauvegarder"), QMessageBox::AcceptRole);
    msgBox.addButton(tr("Annuler"), QMessageBox::RejectRole);
    msgBox.addButton(tr("Ne pas Sauvegarder"), QMessageBox::DestructiveRole);


    int ret = msgBox.exec();
    switch (ret) {
    case QMessageBox::AcceptRole:
        qDebug() << "Accept";
        MenuStart::saveGame(playerProfil);
        close();
        break;
    case QMessageBox::RejectRole:
        qDebug() << "Reject";
        break;
    case QMessageBox::DestructiveRole:
        qDebug() << "Destruct";
        close();
        break;
    default:
        // should never be reached
        break;
    }
}


void Gameboard::saveCheckpoint()
{
    checkpoint->setX(pingouin->x());
    checkpoint->setY(pingouin->y());
}

void Gameboard::loadCheckpoint()
{
    pingouin->setPos((checkpoint->x()+gameSquares)/gameSquares,(checkpoint->y()+gameSquares)/gameSquares);
    checkPositionEvents();
}

void Gameboard::setProxy()
{
    menuPauseInGame = new M_Pause(this);
    setPositionCenter(menuPauseInGame);
    proxy = mainScene->addWidget(menuPauseInGame);
    proxy->hide();
    proxy->setZValue(100);
    toggleMenuPause = false;

    objectList = new WidgetObject(this);
    objectList->reloadObjectList(pingouin->getSacoche());
    setPositionBottom(objectList);
    objectListProxy = mainScene->addWidget(objectList);
    objectListProxy->show();

    lifeList = new WidgetLife(this);
    lifeList->updateHearts(playerProfil->getNbLive());
    setPositionTop(lifeList);
    lifeListProxy = mainScene->addWidget(lifeList);
    lifeListProxy->show();

    dialog = new WidgetDialog(this);
    dialogProxy = mainScene->addWidget(dialog);
    dialogProxy->setZValue(90);
    dialogProxy->hide();
    setPositionCenter(dialog);
    dialogToogle = false;
}

void Gameboard::setLevel(int value)
{
    playerProfil->setLevel(value);
    currentLevel = new Level(value, this);
    pingouin->setPos(currentLevel->getStartingPoint()->x(),currentLevel->getStartingPoint()->y());
    viewRequested = currentLevel->getViewStart();
    MenuStart::saveGame(playerProfil);
    saveCheckpoint();
    loadLevel();
}

void Gameboard::loadLevel()
{
    mainScene = currentLevel->populateScene();
    setViewPosition();

    playerView->setScene(mainScene);
    playerView->setSceneRect(viewPositionX,viewPositionY,sizeX*gameSquares,sizeY*gameSquares);

    pingouin->addToScene(mainScene);

    pingouin->removeTempFromSacoche();
    pingouin->setPlayerOrientation("down");
    loadCheckpoint();
    setTimer();
}

void Gameboard::setTimer()
{
    QObject::connect(timer, SIGNAL(timeout()), mainScene, SLOT(advance()));
}

void Gameboard::disconnectTimer()
{
    QObject::disconnect(timer, SIGNAL(timeout()), mainScene, SLOT(advance()));
}

void Gameboard::setPlayerProfil(Profil *playerProfil)
{
    this->playerProfil = playerProfil;
    setLevel(playerProfil->getLevel());
    setProxy();
    setTimer();

    setFirstDialog();
}

void Gameboard::setFirstDialog()
{
    setPositionCenter(dialog);
    dialogProxy->show();
    dialog->setText(currentLevel->getDialogText(1),1);
    dialogToogle = true;
}

void Gameboard::removeAllItems()
{
    QList<QGraphicsItem*> itemsList = mainScene->items();
    QList<QGraphicsItem*>::iterator iter = itemsList.begin();
    QList<QGraphicsItem*>::iterator end = itemsList.end();
    while(iter != end)
    {
        QGraphicsItem* item = (*iter);
        mainScene->removeItem(item);
        iter++;
    }
    mainScene->clear();
}
