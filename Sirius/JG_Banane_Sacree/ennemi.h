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

#ifndef MECHANT_H
#define MECHANT_H

#include <QGraphicsItem>

class QPoint;
class QGraphicsRectItem;
class Gameboard;


struct ViewBloc{
    QGraphicsRectItem *bloc;
    int ligne;      //.. -2, -1, 0, 1, 2 ..
    int colonne;    // 0,1,2..
    bool actif;
};

/**
 * \brief Classe parent de touts les ennemis.
 *
 * C'est la classe parent des ennemis. Elle permet de
 * definir, de diriger, et specifier les enemies enfants
 *
 */

class Ennemi : public QGraphicsItem
{

public:
    Ennemi(QList<QPoint>, Gameboard *g);
    void addToScene(QGraphicsScene*);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void setOrientation_top();
    void setOrientation_bottom();
    void setOrientation_left();
    void setOrientation_right();

    void setPath(QList<QPoint>);

protected:
    void advance(int);
    int speed;

    QList<QPoint> path;
    QList<ViewBloc> champVue;

    void setPosViewBloc(QGraphicsRectItem*, QPoint);

    //Les skins sont les images attribué au méchant
    QString leftSkin;
    QString rightSkin;
    QString upSkin;
    QString downSkin;

    QBrush *ennemiSkin;

private:
    int iDestPoint;
    bool sens;
    bool detectPinguin;
    int time;
    char orientation;

    void moveBy(int, int);
    void setPos(int, int);
    QPoint convertPosPoint(QPointF);
    bool collide();

    int nextPoint();

    void viewBlocActif();
    void pinguinDetection();

    Gameboard *game;


};

#endif // MECHANT_H
