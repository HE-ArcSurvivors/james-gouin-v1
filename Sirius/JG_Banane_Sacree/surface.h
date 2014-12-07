#ifndef SURFACE_H
#define SURFACE_H

#include <QGraphicsItem>
#include <QGraphicsRectItem>

class Surface : public QGraphicsRectItem
{
public:
    Surface(int xpos, int ypos, QGraphicsItem *parent = 0);
    ~Surface();
    void setPos(int, int);

    int getWidth();
    int getHeight();
    int getGameSquare();

private:
    int gameSquare = 32;
    int width = 32;
    int height = 32;


};

#endif // SURFACE_H
