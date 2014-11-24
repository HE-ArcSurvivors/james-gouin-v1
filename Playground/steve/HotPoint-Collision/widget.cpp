#include "widget.h"
#include <QtWidgets>
#include "neige.h"
#include "surface.h"
#include <QDebug>
#include <typeinfo>
#include <QList>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{

    resize(500,300);

    //SCENE
    scene = new QGraphicsScene();



    neige* s1 = new neige(0,0);
    scene->addItem(s1);

    neige* s2 = new neige(50, 0);
    scene->addItem(s2);

    neige* s3 = new neige(0, 50);
    scene->addItem(s3);

    neige* s4 = new neige(50, 50);
    scene->addItem(s4 );

    if(s1->collidesWithItem(s2))
    {
        QMessageBox m;
        if(typeid(*s1).name() == typeid(neige).name()){
            m.setText(QString("Collision détectée ! avec neige"));
            m.exec();
        }


    }

    //VIEW
    view = new QGraphicsView(this);
    view->setScene(scene);
    view->show();

}

Widget::~Widget()
{

}
void Widget::resizeEvent(QResizeEvent* event)
{
    view->setGeometry(QRect(0, 0, width(), height()));
    view->setSceneRect(0,0,width(),height());
}
