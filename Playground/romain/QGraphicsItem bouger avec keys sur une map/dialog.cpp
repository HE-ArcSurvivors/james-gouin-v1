#include "dialog.h"
#include "ui_dialog.h"
//#include "IcePuzzle.jpg"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    scene = new QGraphicsScene(this);
    QPixmap m(":/IcePuzzle.jpg");
    scene->setBackgroundBrush(m);//.scaled(545,412,Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
    ui->graphicsView->setScene(scene);

    square = new MySquare();
    scene->addItem(square);
    square->setPos (290,192);
}

Dialog::~Dialog()
{
    delete ui;
}

//http://doc.qt.digia.com/4.6/qt.html#Key-enum
void Dialog::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_W)
        {
            ui->myLabel->setText("You pressed W");
            square->moveBy(0,-32);

        }
    if(event->key() == Qt::Key_S)
        {
            ui->myLabel->setText("You pressed S");
            square->moveBy(0,32);
        }
    if(event->key() == Qt::Key_A)
        {
            ui->myLabel->setText("You pressed A");
            square->moveBy(-32,0);
        }
    if(event->key() == Qt::Key_D)
        {
            ui->myLabel->setText("You pressed D");
            square->moveBy(32,0);
        }
}
