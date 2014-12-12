#ifndef OVERLAY_H
#define OVERLAY_H

#include <QWidget>

class Overlay : public QWidget
{
    Q_OBJECT

public:
    Overlay(QWidget *parent = 0);
    ~Overlay();
};

#endif // OVERLAY_H
