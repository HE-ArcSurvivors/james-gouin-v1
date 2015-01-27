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

#include "object.h"
#include "surface.h"
#include <QBrush>
#include <QGraphicsItem>

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
    QString img = ":/items/items/";
    img.append(this->nom->toLower());
    img.append(".png");
    objectSkin->setTexture(QPixmap(img));

    setBrush(*objectSkin);
}

QString Object::getName()
{
    return *nom;
}

QPixmap Object::getTexture()
{
    return objectSkin->texture();
}
