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

    QList<QPoint> toDesactivate;
    bool allunactived = false;

    for(int i=0; i<champVue.size(); i++)
    {
        //On les actives tous !
        ViewBloc nBloc;
        nBloc = champVue.at(i);
        nBloc.actif=true;
        champVue.replace(i,nBloc);

        //Design Activated
        brush.setStyle(Qt::DiagCrossPattern);
        brush.setColor(Qt::red);
        champVue.at(i).bloc->setBrush(brush);

        pen.setStyle(Qt::SolidLine);
        pen.setColor(Qt::red);
        champVue.at(i).bloc->setPen(pen);

        //les quels on va désactiver ?
        QList<QGraphicsItem *> CollidingItems = champVue.at(i).bloc->collidingItems();
        bool bUnactivate = false;

        for(int j=0; j<CollidingItems.length(); j++)
        {
            if(typeid(*CollidingItems.at(j)).name() == typeid(B_Movable).name()
            || typeid(*CollidingItems.at(j)).name() == typeid(B_Wall).name()
            || typeid(*CollidingItems.at(j)).name() == typeid(Ennemi).name())
            {
                bUnactivate = true;
            }
        }

        if(bUnactivate)
        {
            if(champVue.at(i).ligne==0 && champVue.at(i).colonne ==1) //si c'est le bloc 1
            {
                allunactived = true;
            }
            toDesactivate.append(QPoint(champVue.at(i).ligne, champVue.at(i).colonne));
        }
    }

    //on déactive ce qu'il faut
    foreach (QPoint toDes, toDesactivate)
    {
        for(int i=0; i<champVue.size(); i++)
        {
            //on désactive la ligne
            if((champVue.at(i).colonne >= toDes.y() && champVue.at(i).ligne == toDes.x()) || allunactived)
            {
                ViewBloc nBloc;
                nBloc = champVue.at(i);
                nBloc.actif=false;
                champVue.replace(i,nBloc);

                //Design Unactivated
                brush.setStyle(Qt::Dense6Pattern);
                brush.setColor(Qt::green);
                champVue.at(i).bloc->setBrush(brush);

                pen.setStyle(Qt::NoPen);
                champVue.at(i).bloc->setPen(pen);
            }
        }
    }

}

void Ennemi::pinguinDetection()
{
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

                    QBrush brush;
                    brush.setStyle(Qt::DiagCrossPattern);
                    brush.setColor(Qt::yellow);
                    vb.bloc->setBrush(brush);
                    QPen pen;
                    pen.setStyle(Qt::SolidLine);
                    pen.setColor(Qt::yellow);
                    vb.bloc->setPen(pen);
                  game->restartLevel();                }
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
    viewBlocActif();
    pinguinDetection();
    if(step == 1 && time % speed==0 && !detectPinguin)
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
