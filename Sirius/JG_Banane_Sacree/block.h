#ifndef BLOCK_H
#define BLOCK_H

#include <QGraphicsItem>
#include <QGraphicsRectItem>

class Block : public QGraphicsRectItem
{
public:
    Block(int xpos, int ypos, QGraphicsItem *parent = 0);
    ~Block();
    void setPos(int, int);

    int getWidth();
    int getHeight();
    int getGameSquare();

private:
    int gameSquare = 32;
    int width = 32;
    int height = 32;


};

#endif // BLOCK_H
