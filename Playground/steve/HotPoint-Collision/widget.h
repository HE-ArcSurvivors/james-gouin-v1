#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsItem>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();

private:
    QGraphicsView *view;
    QGraphicsScene *scene;

protected:
    virtual void resizeEvent(QResizeEvent* event);
};

#endif // WIDGET_H
