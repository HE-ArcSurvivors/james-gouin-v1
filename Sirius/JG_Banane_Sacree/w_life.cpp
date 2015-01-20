#include "w_life.h"
#include "object.h"
#include "gameboard.h"

#include <QPainter>

#include <QWidget>
#include <QDebug>

#include <QHBoxLayout>
#include <QStyleOption>

WidgetLife::WidgetLife(QWidget *parent)
{

    totalLife = 0;
    this->setStyleSheet(
                        "color: #2e2e2e;"
                        "background-color: #ffffff;"
                        "border-style: solid;"
                        "border-color: #d3d3d3;"
                        "border-width: 1px;"
                        "border-radius: 8px;"
                        "font-family: Century Gothic;"
                        );

    layout = new QHBoxLayout;
    layout->setSpacing(0);
    layout->setContentsMargins(5,5,5,5);
    this->setLayout(layout);



//    this->setAttribute(Qt::WA_TranslucentBackground);
}

void WidgetLife::paintEvent(QPaintEvent *)
{
//    qDebug() << "PaintEvent";
//    QPainter paint(this);

//    QString img = ":/items/items/oeuf.png";

//    for(int i = 0; i<totalLife; i++)
//    {
//        qDebug() << i*Gameboard::getGameSquares();
//        paint.drawPixmap(i*Gameboard::getGameSquares(),0,Gameboard::getGameSquares(),
//                         Gameboard::getGameSquares(),QPixmap(img));
//    }

    QStyleOption o;
    o.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(
    QStyle::PE_Widget, &o, &p, this);
}

void WidgetLife::updateHearts(int value)
{
    this->totalLife = value;


    QLayoutItem *item;
    while ((item = layout->takeAt(0)))
    {
        delete item;
    }

    QPixmap pix(":/items/items/oeuf.png");
    for(int i = 0; i<totalLife; i++)
        {
            QLabel *item = new QLabel();
            item->setFixedWidth(Gameboard::getGameSquares());
            item->setStyleSheet(

                                "border-style: none;"
                                 "margin:0px;"
                                "padding:0px;"
                                );

            item->setMargin(0);
            item->setPixmap(pix);
            layout->addWidget(item);
        }
    this->resize(value*Gameboard::getGameSquares(),Gameboard::getGameSquares());
//    this->resize(value*Gameboard::getGameSquares(),Gameboard::getGameSquares());
//    update();
}
