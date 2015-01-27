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
