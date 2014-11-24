#ifndef SURFACE_H
#define SURFACE_H

#include <QGraphicsItem>
#include <QGraphicsRectItem>

class surface : public QGraphicsRectItem
{
public:
    surface(qreal xpos, qreal ypos, QGraphicsItem *parent = 0);
    ~surface();

};

#endif // SURFACE_H
