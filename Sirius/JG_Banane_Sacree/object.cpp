#include "object.h"
#include "surface.h"
#include <QBrush>

Object::Object(int xpos, int ypos, QGraphicsItem *parent) : Surface(xpos, ypos, parent)
{
    setDesign();
}
Object::Object(QString new_nom, QGraphicsItem *parent) : Surface(0, 0, parent)
{
    this->nom = new QString(new_nom);
    setZValue(2);
    setDesign();
}

void Object::setDesign()
{
    objectSkin = new QBrush();

    if(*this->nom == "Poisson")
    {
       objectSkin->setTexture(QPixmap(":/characters/characters/baleine.png"));
    }
    else if(*this->nom == "Oeuf")
    {
        objectSkin->setTexture(QPixmap(":/characters/characters/oeuf.png"));
    }
    else
    {
        objectSkin->setTexture(QPixmap(""));
    }

    setBrush(*objectSkin);
}

QString Object::getName()
{
    return *nom;
}

void Object::action()
{

}
