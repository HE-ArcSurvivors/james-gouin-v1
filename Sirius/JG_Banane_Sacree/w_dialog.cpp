#include "w_dialog.h"
#include <QPainter>
#include <QDebug>

WidgetDialog::WidgetDialog(QWidget *parent)
{
    resize(300,100);

}

void WidgetDialog::setText(QString text)
{
    this->text = text;
    update();
}

void WidgetDialog::paintEvent(QPaintEvent *)
{
     qDebug() << "Write:" << text;
     QPainter paint(this);
     paint.setPen(Qt::black);
     paint.drawText(10,10,280,80,Qt::TextWordWrap,this->text);

     paint.drawText(10,this->height()-20,280,20,Qt::TextWordWrap,"Presse sur la touche espace pour continuer");
}

