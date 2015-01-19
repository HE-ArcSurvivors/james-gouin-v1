<<<<<<< HEAD
#include "w_life.h"
#include "object.h"
#include "gameboard.h"

#include <QPainter>

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

    for(int i = 0; i<totalLife; i++)
    {
        qDebug() << i*Gameboard::getGameSquares();
        paint.drawPixmap(i*Gameboard::getGameSquares(),0,Gameboard::getGameSquares(),
                         Gameboard::getGameSquares(),QPixmap(img));
    }
}

void WidgetLife::updateHearts(int value)
{
    this->totalLife = value;
    this->resize(value*Gameboard::getGameSquares(),Gameboard::getGameSquares());
    update();
}
=======
#include "w_life.h"
#include "object.h"
#include "gameboard.h"

#include <QPainter>

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

    for(int i = 0; i<totalLife; i++)
    {
        qDebug() << i*Gameboard::getGameSquares();
        paint.drawPixmap(i*Gameboard::getGameSquares(),0,Gameboard::getGameSquares(),
                         Gameboard::getGameSquares(),QPixmap(img));
    }
}

void WidgetLife::updateHearts(int value)
{
    this->totalLife = value;
    this->resize(value*Gameboard::getGameSquares(),Gameboard::getGameSquares());
    update();
}
>>>>>>> 851630d3cbf1e1e35392c85bc99b8232862b70b3
