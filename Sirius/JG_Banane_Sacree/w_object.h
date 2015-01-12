#ifndef W_OBJECT_H
#define W_OBJECT_H

#include <QWidget>
#include "object.h"
#include <QList>
#include <QMap>

class WidgetObject : public QWidget
{
    Q_OBJECT
public:
    WidgetObject(QWidget *parent = 0);
    void paintEvent(QPaintEvent *);
    void reloadObjectList(QList<Object*> objectList);

signals:

public slots:

private:
    QList<Object* > sacoche;
    QMap<QString, int> map;

};

#endif // W_OBJECT_H
