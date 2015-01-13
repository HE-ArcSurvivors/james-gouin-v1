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
     paint.drawText(10,20,this->text);
}

