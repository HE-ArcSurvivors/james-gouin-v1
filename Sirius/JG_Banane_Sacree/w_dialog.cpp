#include "w_dialog.h"
#include <QPainter>
#include <QDebug>

WidgetDialog::WidgetDialog(QWidget *parent)
{
    resize(300,200);

}

void WidgetDialog::setText(QString text, int type)
{
    this->text = text;
    this->type = type;
    update();
}

void WidgetDialog::paintEvent(QPaintEvent *)
{
     QPainter paint(this);
     paint.setPen(Qt::black);

     if(type == 1)
     {
         paint.drawText(10,10,280,20,Qt::TextWordWrap,"Ordre de mission de James Gouin :");
     }
     paint.drawText(10,30,280,80,Qt::TextWordWrap,this->text);

     paint.drawText(10,this->height()-20,280,20,Qt::AlignRight,"Espace pour continuer");
}

