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

#include "ennemi.h"

#include <QGraphicsItem>
#include <QPoint>
#include <QList>

#include <QBrush>
#include <QPen>
#include <QGraphicsRectItem>

#include <QWidget>
#include <QGraphicsScene>
#include <QPainter>
#include <QStyleOption>

#include <QDebug>

#include "gameboard.h"
#include "b_wall.h"
#include "b_water.h"
#include "b_movable.h"
#include "player.h"
#include "p_penguin.h"

#if defined(__unix__) || (defined(__APPLE__) && defined(__MACH__))
#else
    #include <typeinfo.h>
#endif

Ennemi::Ennemi(QList<QPoint> path, Gameboard *g)
{
    game = g;

    sens = true;
    detectPinguin = false;

    //vitesse entre 1 et 100
    // 1 étant très rapide, 100 étant très lent
    speed = 100; //vitesse par défaut
    time = rand() % speed;

    setPath(path);
    setZValue(2);
}

void Ennemi::setPath(QList<QPoint> path)
{
    iDestPoint = 0;
    this->path = path;
    setPos(path.at(0).x(), path.at(0).y());
}

void Ennemi::viewBlocActif()
{
    QBrush brush;
    QPen pen;

    //Design Activated
    brush.setStyle(Qt::DiagCrossPattern);
    brush.setColor(Qt::red);
    pen.setStyle(Qt::SolidLine);
    pen.setColor(Qt::red);

    QList<QPoint> toDesactivate;
    bool allunactived = false;

    QList<ViewBloc>::iterator it;
    for (it = champVue.begin(); it != champVue.end(); ++it)
    {
        //On les actives tous !
        (*it).actif = true;

        //Design Activated
        (*it).bloc->setBrush(brush);
        (*it).bloc->setPen(pen);

        //lesquels on va désactiver ?
        QList<QGraphicsItem *> CollidingItems = (*it).bloc->collidingItems();
        bool bUnactivate = false;

        foreach (QGraphicsItem *item, CollidingItems) {
            if(typeid(*item).name() == typeid(B_Movable).name()
            || typeid(*item).name() == typeid(B_Wall).name()
            || typeid(*item).name() == typeid(Ennemi).name())
            {
                bUnactivate = true;
            }
        }

        if(bUnactivate)
        {
            if((*it).ligne==0 && (*it).colonne ==1) //si c'est le bloc 1
            {
                allunactived = true;
            }
            toDesactivate.append(QPoint((*it).ligne, (*it).colonne));
        }
    }

    //Design Unactivated
    brush.setStyle(Qt::Dense6Pattern);
    brush.setColor(Qt::green);
    pen.setStyle(Qt::NoPen);

    //on déactive ce qu'il faut
    foreach (QPoint toDes, toDesactivate)
    {
        QList<ViewBloc>::iterator it;
        for (it = champVue.begin(); it != champVue.end(); ++it)
        {
            //on désactive la ligne
            if(((*it).colonne >= toDes.y() && (*it).ligne == toDes.x()) || allunactived)
            {
                (*it).actif=false;

                //Design Unactivated
                (*it).bloc->setBrush(brush);
                (*it).bloc->setPen(pen);
            }
        }
    }

}

void Ennemi::pinguinDetection()
{
    QBrush brush;
    brush.setStyle(Qt::DiagCrossPattern);
    brush.setColor(Qt::yellow);

    QPen pen;
    pen.setStyle(Qt::SolidLine);
    pen.setColor(Qt::yellow);

    detectPinguin = false;
    foreach (ViewBloc vb, champVue)
    {
        if(vb.actif)
        {
            QList<QGraphicsItem *> CollidingItems = vb.bloc->collidingItems();

            for(int i=0; i<CollidingItems.length(); i++)
            {
                if(typeid(*CollidingItems.at(i)).name() == typeid(Pingouin).name())
                {
                    this->detectPinguin = true;
                    vb.bloc->setBrush(brush);
                    vb.bloc->setPen(pen);
                    game->restartEnigma();
                }
            }
        }
    }
}

QPoint Ennemi::convertPosPoint(QPointF psrc)
{
    int x = (psrc.x()-1) /Gameboard::getGameSquares();
    int y = (psrc.y()-1) /Gameboard::getGameSquares();
    return QPoint(x, y);
}

bool Ennemi::collide()
{
    QGraphicsRectItem *collideRect;
    foreach (ViewBloc vb, champVue) {
        if(vb.colonne==1 && vb.ligne==0){
            collideRect = vb.bloc;
        }
    }

    QList<QGraphicsItem *> CollidingItems = collideRect->collidingItems();
    for(int i=0; i<CollidingItems.length(); i++)
    {
        if(typeid(*CollidingItems.at(i)).name() == typeid(B_Water).name())
        {
            return true;
        }
        else if(typeid(*CollidingItems.at(i)).name() == typeid(B_Movable).name())
        {
            return true;
        }
        else if(typeid(*CollidingItems.at(i)).name() == typeid(B_Wall).name())
        {
            return true;
        }
        else if(typeid(*CollidingItems.at(i)).name() == typeid(Ennemi).name())
        {
            return true;
        }
    }
    return false;
}

//renvoi l'id du point suivant dans la liste de point
//prend en compte le sens de déplacement de l'ennemi
int Ennemi::nextPoint()
{
    if(sens)
    {
        iDestPoint ++;
    }
    else
    {
        iDestPoint --;
    }

    if(iDestPoint>path.size()-1)
    {
        iDestPoint = 0;
    }
    else if(iDestPoint<0)
    {
        iDestPoint = path.size()-1;
    }

    return iDestPoint;
}

//Exécuté à chaque appel du slot "advance()" de la scene
//Cerveau de l'ennemi
void Ennemi::advance(int step)
{
    if(step == 1)
    {
        viewBlocActif();
        pinguinDetection();

        if(time % speed==0 && !detectPinguin)
        {
            time = 0;
            QPoint posEnnemi = convertPosPoint(this->pos());

            //1 on trouve son orientation
            char direction = orientation;
            if(path.at(iDestPoint).x() > posEnnemi.x())
            {
                direction = 'r'; // la direction voulu avant de marcher
            }
            else if(path.at(iDestPoint).x() < posEnnemi.x())
            {
                direction = 'l';
            }
            else if(path.at(iDestPoint).y() > posEnnemi.y())
            {
                direction = 'b';
            }
            else if(path.at(iDestPoint).y() < posEnnemi.y())
            {
                direction = 't';
            }

            if(direction != orientation) //l'orientation n'est pas bonne
            {
                //le point est a ma gauche ou a ma droite ?
                   if(orientation == 't')
                   {
                       if(path.at(iDestPoint).x() > posEnnemi.x())
                       {
                           //tourne a droite
                           //turnRight();
                           setOrientation_right();
                       }
                       else if(path.at(iDestPoint).x() < posEnnemi.x())
                       {
                           //tourne a gauche
                           //turnLeft();
                           setOrientation_left();
                       }
                       else if(path.at(iDestPoint).y() > posEnnemi.y())
                       {
                           //on se retourne ( toujours par la droite )
                           //turnRight();
                           setOrientation_right();
                       }
                   }
                   else if(orientation=='b')
                   {
                       if(path.at(iDestPoint).x() > posEnnemi.x())
                       {
                           //tourne a SA gauche
                           //turnLeft();
                           setOrientation_right();
                       }
                       else if(path.at(iDestPoint).x() < posEnnemi.x())
                       {
                           //tourne a SA droite
                           //turnRight();
                           setOrientation_left();
                       }
                       else if(path.at(iDestPoint).y() < posEnnemi.y())
                       {
                           //on se retourne ( toujours par SA droite )
                           setOrientation_left();
                       }
                   }
                   else if(orientation=='r')
                   {
                       if(path.at(iDestPoint).x() < posEnnemi.x())
                       {
                           //on se retourne ( toujours par SA droite )
                           //turnRight();
                           setOrientation_bottom();
                       }
                       else if(path.at(iDestPoint).y() < posEnnemi.y())
                       {
                           //tourne a SA gauche
                           //turnLeft();
                           setOrientation_top();
                       }
                       else if(path.at(iDestPoint).y() > posEnnemi.y())
                       {
                           //tourne a SA droite
                           //turnRight();
                           setOrientation_bottom();
                       }
                   }
                   else if(orientation=='l')
                   {
                       if(path.at(iDestPoint).x() > posEnnemi.x())
                       {
                           //on se retourne ( toujours par SA droite )
                           //turnRight();
                           setOrientation_top();
                       }
                       else if(path.at(iDestPoint).y() < posEnnemi.y())
                       {
                           //tourne a SA droite
                           //turnRight();
                           setOrientation_top();
                       }
                       else if(path.at(iDestPoint).y() > posEnnemi.y())
                       {
                           //tourne a SA droite
                           //turnLeft();
                           setOrientation_bottom();

                       }
                   }
                }
            else
            {
                //déplacement en x en premier puis en y
                if(path.at(iDestPoint).x() > posEnnemi.x())
                {
                    if(!collide())
                    {
                        this->moveBy(1,0);
                    }
                    else
                    {
                        sens = !sens;
                        iDestPoint = nextPoint();
                    }
                }
                else if(path.at(iDestPoint).x() < posEnnemi.x())
                {
                    if(!collide())
                    {
                        this->moveBy(-1,0);
                    }
                    else
                    {
                        sens = !sens;
                        iDestPoint = nextPoint();
                    }
                }
                else if(path.at(iDestPoint).y() > posEnnemi.y())
                {
                    if(!collide())
                    {
                        this->moveBy(0,1);
                    }
                    else
                    {
                        sens = !sens;
                        iDestPoint = nextPoint();
                    }
                }
                else if(path.at(iDestPoint).y() < posEnnemi.y())
                {
                    if(!collide())
                    {
                        this->moveBy(0,-1);
                    }
                    else
                    {
                        sens = !sens;
                        iDestPoint = nextPoint();
                    }
                }
                else //on est arrivé sur le point de destination
                {
                    iDestPoint = nextPoint();
                }
            }

            viewBlocActif();
            pinguinDetection();

        }
        time ++;
    }
}
void Ennemi::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    //Draw the ennemi
    painter->setPen(Qt::transparent);

    ennemiSkin = new QBrush();

    //Set ennemiSkin texture depending on ennemi's orientation
    switch (orientation) {
    case 'l':
        ennemiSkin->setTexture(QPixmap(leftSkin));
        break;
    case 'r':
        ennemiSkin->setTexture(QPixmap(rightSkin));
        break;
    case 't':
        ennemiSkin->setTexture(QPixmap(upSkin));
        break;
    case 'b':
        ennemiSkin->setTexture(QPixmap(downSkin));
        break;
    default:
        break;
    }

    QRectF ennemiBox = boundingRect();  //Setting ennemi's box

    painter->fillRect(ennemiBox,*ennemiSkin);   //charger la couleur
    painter->drawRect(ennemiBox);
}
QRectF Ennemi::boundingRect() const
{
    return QRectF(0,0,Gameboard::getGameSquares()-2,Gameboard::getGameSquares()-2);
}

void Ennemi::setOrientation_top()
{
    orientation = 't';
    foreach (ViewBloc vb, champVue)
    {
        setPosViewBloc(vb.bloc, QPoint(vb.ligne, -vb.colonne));
    }
    update();
}
void Ennemi::setOrientation_bottom()
{
    orientation = 'b';
    foreach (ViewBloc vb, champVue)
    {
        setPosViewBloc(vb.bloc, QPoint(-vb.ligne, vb.colonne));
    }
    update();
}
void Ennemi::setOrientation_left()
{
    orientation = 'l';
    foreach (ViewBloc vb, champVue)
    {
        setPosViewBloc(vb.bloc, QPoint(-vb.colonne, -vb.ligne));
    }
    update();
}
void Ennemi::setOrientation_right()
{
    orientation = 'r';
    foreach (ViewBloc vb, champVue)
    {
        setPosViewBloc(vb.bloc, QPoint(vb.colonne, vb.ligne));
    }
    update();
}

//Défini la position d'un bloc "viewBloc" en fonction de sa ligne et sa colonne
void Ennemi::setPosViewBloc(QGraphicsRectItem* bloc, QPoint p)
{
    int gs = Gameboard::getGameSquares();
    QPoint posEnnemi = convertPosPoint(this->pos());

    bloc->setPos(posEnnemi.x()*gs + p.x()*gs+1, posEnnemi.y()*gs + p.y()*gs+1);
}

void Ennemi::setPos(int x, int y)
{
    foreach (ViewBloc vb, champVue)
    {
        setPosViewBloc(vb.bloc, QPoint(vb.ligne, vb.colonne));
    }

    QGraphicsItem::setPos(x*Gameboard::getGameSquares()+1, y*Gameboard::getGameSquares()+1);
}
void Ennemi::moveBy(int x, int y)
{
    int gameSquare = Gameboard::getGameSquares();
    foreach (ViewBloc vb, champVue)
    {
        vb.bloc->moveBy(x*gameSquare,y*gameSquare);
    }

    QGraphicsItem::moveBy(x*gameSquare,y*gameSquare);
}

void Ennemi::addToScene(QGraphicsScene* scene)
{
    scene->addItem(this);

    foreach (ViewBloc vb, champVue)
    {
        scene->addItem(vb.bloc);
    }
}
