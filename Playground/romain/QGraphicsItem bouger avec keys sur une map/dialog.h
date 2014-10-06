#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QtCore>
#include <QtGui>
#include "mysquare.h"

namespace Ui {
    class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private:
    Ui::Dialog *ui;
    QGraphicsScene *scene;
    MySquare *square;
    void keyPressEvent(QKeyEvent *event);
};

#endif // DIALOG_H
