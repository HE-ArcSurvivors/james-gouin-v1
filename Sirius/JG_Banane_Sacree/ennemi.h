#ifndef MECHANT_H
#define MECHANT_H

#include <QGraphicsItem>
class QPoint;
class QGraphicsRectItem;


struct ViewBloc{
    QGraphicsRectItem *bloc;
    int ligne;      //.. -2, -1, 0, 1, 2 ..
    int colonne;    // 0,1,2..
    bool actif;
};

class Ennemi : public QGraphicsItem
{

public:
    Ennemi(QList<QPoint>);
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


};

#endif // MECHANT_H
