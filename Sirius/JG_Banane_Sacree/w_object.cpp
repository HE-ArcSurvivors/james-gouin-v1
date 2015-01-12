#include "w_object.h"
#include "object.h"
#include "p_penguin.h"
#include "gameboard.h"
#include <QWidget>
#include <QDebug>

#include <QMap>

WidgetObject::WidgetObject(QWidget *parent)
{
    this->resize(Gameboard::getGameSquares(),Gameboard::getGameSquares());
    this->setStyleSheet("background-color: white;");
}

void WidgetObject::paintEvent(QPaintEvent *)
{
    QPainter paint(this);
    paint.setPen(Qt::black);
    QMap<QString, int> map;

    for (int i = 0; i < sacoche.size(); ++i)
    {
        if(map.contains(sacoche.at(i)->getName()))
        {
           map[sacoche.at(i)->getName()] = map.value(sacoche.at(i)->getName())+1;
        }
        else
        {
            map.insert(sacoche.at(i)->getName(),1);
        }
    }

    int j = 0;
    QMap<QString, int>::const_iterator i = map.constBegin();
     while (i != map.constEnd()) {

         QString img = ":/items/items/";
         img.append(i.key().toLower());

         if(i.value()>1)
         {
            img.append(QString::number(i.value()));
         }

         img.append(".png");

         qDebug() << img;
         paint.drawPixmap(j*Gameboard::getGameSquares(),0,Gameboard::getGameSquares(),
                          Gameboard::getGameSquares(),QPixmap(img));
         ++i;
         j++;
     }


//    for (int i = 0; i < sacoche.size(); ++i)
//    {
//        paint.drawPixmap(i*Gameboard::getGameSquares(),0,Gameboard::getGameSquares(),
//                         Gameboard::getGameSquares(),sacoche.at(i)->getTexture());
//    }


}

void WidgetObject::reloadObjectList(QList<Object*> objectList)
{
    sacoche = objectList;

    QMap<QString, int> map;

    for(int i = 0; i < sacoche.size(); ++i)
    {
        if(map.contains(sacoche.at(i)->getName()))
        {
           map[sacoche.at(i)->getName()] = map.value(sacoche.at(i)->getName())+1;
        }
        else
        {
            map.insert(sacoche.at(i)->getName(),1);
        }
    }

    this->resize(map.size()*Gameboard::getGameSquares(),Gameboard::getGameSquares());
    update();
}
