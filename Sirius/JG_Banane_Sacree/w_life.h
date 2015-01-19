<<<<<<< HEAD
#ifndef W_LIFE_H
#define W_LIFE_H

#include <QWidget>

class WidgetLife : public QWidget
{
    Q_OBJECT
public:
    WidgetLife(QWidget *parent = 0);
    void paintEvent(QPaintEvent *);
    void updateHearts(int value);

signals:

public slots:

private:
    int totalLife;

};

#endif // W_LIFE_H
=======
#ifndef W_LIFE_H
#define W_LIFE_H

#include <QWidget>

class WidgetLife : public QWidget
{
    Q_OBJECT
public:
    WidgetLife(QWidget *parent = 0);
    void paintEvent(QPaintEvent *);
    void updateHearts(int value);

signals:

public slots:

private:
    int totalLife;

};

#endif // W_LIFE_H
>>>>>>> 851630d3cbf1e1e35392c85bc99b8232862b70b3
