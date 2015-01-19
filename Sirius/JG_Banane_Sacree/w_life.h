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
