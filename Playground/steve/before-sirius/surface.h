#ifndef SURFACE_H
#define SURFACE_H

#include <QGraphicsItem>
#include <QGraphicsRectItem>

class surface : public QGraphicsRectItem
{
public:
    surface(int xpos, int ypos, QGraphicsItem *parent = 0);
    ~surface();
    void setPos(int, int);

private:
    int gameSquare = 32;
    int width = 32;
    int height = 32;


};

#endif // SURFACE_H
