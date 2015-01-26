#include "w_life.h"
#include "object.h"
#include "gameboard.h"

#include <QPainter>
#include <QBrush>
#include <QFont>
#include <QWidget>
#include <QDebug>

WidgetLife::WidgetLife(QWidget *parent)
{
    totalLife = 0;
    this->resize(Gameboard::getGameSquares(),Gameboard::getGameSquares());
    this->setAttribute(Qt::WA_TranslucentBackground);
}

void WidgetLife::paintEvent(QPaintEvent *)
{
    qDebug() << "PaintEvent";
    QPainter paint(this);

    QString img = ":/items/items/oeuf.png";
    QString totalLifeString = QString::number(totalLife);
    totalLifeString.append("x");

    QBrush brush;
    brush.setColor(Qt::black);

    QFont font;
    font.setWeight(QFont::Bold);
    font.setFamily("Century Gothic");
    font.setPointSize(11);

    paint.drawPixmap(0,0,Gameboard::getGameSquares(),Gameboard::getGameSquares(),QPixmap(img));
    paint.setBrush(brush);
    paint.setFont(font);
    paint.drawText(Gameboard::getGameSquares()+5, Gameboard::getGameSquares()/2+5, totalLifeString);

//    for(int i = 0; i<totalLife; i++)
//    {
//        qDebug() << i*Gameboard::getGameSquares();
//        paint.drawPixmap(i*Gameboard::getGameSquares(),0,Gameboard::getGameSquares(),
//                         Gameboard::getGameSquares(),QPixmap(img));
//    }
}

void WidgetLife::updateHearts(int value)
{
    this->totalLife = value;
    this->resize(value*Gameboard::getGameSquares(),Gameboard::getGameSquares());
    update();
}
