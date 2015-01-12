#include "ennemi.h"

#include <QGraphicsItem>
#include <QPoint>
#include <QList>

#include <QBrush>
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

Ennemi::Ennemi(QList<QPoint> path)
{
    sens = true;
    detectPinguin = false;

    //vitesse entre 1 et 100
    // 1 étant très rapide, 100 étant très lent
    speed = 30;
    time = rand() % speed;

    iDestPoint = 0;
    this->path = path;

    ViewBloc vb;
    vb.bloc = new QGraphicsRectItem(0,0, Gameboard::getGameSquares()-2, Gameboard::getGameSquares()-2);
    vb.colonne=1;
    vb.ligne=0;

    ViewBloc vb2;
    vb2.bloc = new QGraphicsRectItem(0,0, Gameboard::getGameSquares()-2, Gameboard::getGameSquares()-2);
    vb2.colonne=2;
    vb2.ligne=0;

    ViewBloc vb3;
    vb3.bloc = new QGraphicsRectItem(0,0, Gameboard::getGameSquares()-2, Gameboard::getGameSquares()-2);
    vb3.colonne=1;
    vb3.ligne=1;

    ViewBloc vb4;
    vb4.bloc = new QGraphicsRectItem(0,0, Gameboard::getGameSquares()-2, Gameboard::getGameSquares()-2);
    vb4.colonne=1;
    vb4.ligne=-1;

    ViewBloc vb5;
    vb5.bloc = new QGraphicsRectItem(0,0, Gameboard::getGameSquares()-2, Gameboard::getGameSquares()-2);
    vb5.colonne=2;
    vb5.ligne=-1;

    ViewBloc vb6;
    vb6.bloc = new QGraphicsRectItem(0,0, Gameboard::getGameSquares()-2, Gameboard::getGameSquares()-2);
    vb6.colonne=2;
    vb6.actif =true;
    vb6.ligne=1;

    champVue.append(vb);
    champVue.append(vb2);
    champVue.append(vb3);
    champVue.append(vb4);
    champVue.append(vb5);
    champVue.append(vb6);


    setPos(path.at(0).x(), path.at(0).y());

    //par défaut on lui donne une orientation
    setOrientation_left();

}

void Ennemi::viewBlocActif()
{

    for(int i=0; i<champVue.size(); i++)
    {
        ViewBloc nBloc;
        nBloc = champVue.at(i);
        nBloc.actif=true;
        champVue.replace(i,nBloc);
    }

    foreach (ViewBloc vb, champVue)
    {
        QList<QGraphicsItem *> CollidingItems = vb.bloc->collidingItems();
        bool bUnactivate = false;

        for(int i=0; i<CollidingItems.length(); i++)
        {
            if(typeid(*CollidingItems.at(i)).name() == typeid(B_Movable).name())
            {
                bUnactivate = true;
            }
            else if(typeid(*CollidingItems.at(i)).name() == typeid(B_Wall).name())
            {
                bUnactivate = true;
            }
            else if(typeid(*CollidingItems.at(i)).name() == typeid(Ennemi).name())
            {
                bUnactivate = true;
            }
        }

        if(bUnactivate)
        {
            bool allunactived = false;
            if(vb.ligne==0 && vb.colonne ==1) //si c'est le bloc 1
            {
                allunactived = true;
            }
            for(int i=0; i<champVue.size(); i++)
            {
                if((champVue.at(i).colonne >= vb.colonne && champVue.at(i).ligne == vb.ligne) || allunactived)
                {
                    ViewBloc nBloc;
                    nBloc = champVue.at(i);
                    nBloc.actif=false;
                    champVue.replace(i,nBloc);
                }
            }
        }
    }

    //couleur
    foreach (ViewBloc vb, champVue)
    {
        if(vb.actif)
        {
            QBrush brush;
            brush.setStyle(Qt::DiagCrossPattern);
            brush.setColor(Qt::red);
            QPen pen;
            pen.setStyle(Qt::SolidLine);
            pen.setColor(Qt::red);
            vb.bloc->setPen(pen);

            vb.bloc->setBrush(brush);
        }
        else
        {
            QBrush brush;
            brush.setStyle(Qt::Dense6Pattern);
            brush.setColor(Qt::green);
            vb.bloc->setBrush(brush);
            QPen pen;
            pen.setStyle(Qt::NoPen);
            vb.bloc->setPen(pen);
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
    painter->setBrush(Qt::red);
    painter->drawRect(0,0,Gameboard::getGameSquares()-2,Gameboard::getGameSquares()-2);
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
}
void Ennemi::setOrientation_bottom()
{
    orientation = 'b';
    foreach (ViewBloc vb, champVue)
    {
        setPosViewBloc(vb.bloc, QPoint(-vb.ligne, vb.colonne));
    }
}
void Ennemi::setOrientation_left()
{
    orientation = 'l';
    foreach (ViewBloc vb, champVue)
    {
        setPosViewBloc(vb.bloc, QPoint(-vb.colonne, -vb.ligne));
    }
}
void Ennemi::setOrientation_right()
{
    orientation = 'r';
    foreach (ViewBloc vb, champVue)
    {
        setPosViewBloc(vb.bloc, QPoint(vb.colonne, vb.ligne));
    }
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
