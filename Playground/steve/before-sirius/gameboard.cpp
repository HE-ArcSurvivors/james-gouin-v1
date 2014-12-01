#include "gameboard.h"
#include "pingouin.h"
#include "neige.h"
#include <QList>;

Gameboard::Gameboard(QWidget *parent) : QWidget(parent)
{
    // Les Variables par default du jeu
    windowTitle = tr("James Gouin et la Banane Sacrée");
    windowSizeX = 640;
    windowSizeY = 480;
    viewStartPostionX = 1;
    viewStartPostionY = 1;
    viewPositionX = 640;
    viewPositionY = 480;
    startingPoint = QPoint (5,5); // 20x15
    QString tutorialLevel3 = ":/images/test_map_tutoriel_3.png";

    this->setWindowTitle(windowTitle);
    this->setFixedSize(windowSizeX,windowSizeY);

    mainScene = new QGraphicsScene(this);
    playerView = new QGraphicsView(this);

    //On crée la scene
    QPixmap loadScene(tutorialLevel3);
    mainScene->setBackgroundBrush(loadScene);
    //mainScene->setSceneRect(viewStartPostionX,viewStartPostionY,viewPositionX,viewPositionX);

    //Ce qui est dessous peut etre utilise si la map est plus grande que la vue
    //playerView->setHorizontalScrollBarPolicy (Qt::ScrollBarAlwaysOff);
    //playerView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //playerView->setFocus();
    //playerView->setFixedSize(640,480);
    playerView->setSceneRect(viewStartPostionX,viewStartPostionY,viewPositionX,viewPositionX);


    //surfaces
    neige *n = new neige(10,10);

    mainScene->addItem(n);


    //On ajoute le joueur
    pingouin = new Pingouin(gameSquares);
    pingouin->addToScene(mainScene);
    pingouin->setPos(startingPoint.x(), startingPoint.y());




    //On position la vue
    playerView->setScene(mainScene);

}

Gameboard::~Gameboard(){

}

//http://doc.qt.digia.com/4.6/qt.html#Key-enum
void Gameboard::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_W)
    {
        // Determiner si le joueur sort de la vue
        if (pingouin->pos().y() > viewStartPostionY)
        {
            pingouin->moveBy(0, -1);
            pingouin->setPlayerOrientation("up"); //definir l'orientation du joueur
        }
    }
    if(event->key() == Qt::Key_S)
    {
        if (pingouin->pos().y() <= viewPositionY-pingouin->getPlayer()->getPlayerSizeX()-8)
        {
            pingouin->moveBy(0, 1);
            pingouin->setPlayerOrientation("down");
        }
    }
    if(event->key() == Qt::Key_A)
    {
        if (pingouin->pos().x() > viewStartPostionY)
        {
            pingouin->moveBy(-1, 0);
            pingouin->setPlayerOrientation("left");
        }
    }
    if(event->key() == Qt::Key_D)
    {
        if (pingouin->pos().x() < viewPositionX-pingouin->getPlayer()->getPlayerSizeY())
        {



            //JUST des essais de collisions ;)
            QList<QGraphicsItem *> CollidesRight;
            CollidesRight = pingouin->CollidesRight();

            for(int i=0; i<CollidesRight.length(); i++)
            {
                QMessageBox m;
                m.setText(typeid(*CollidesRight.at(i)).name());
                m.exec();

                if(typeid(*CollidesRight.at(i)).name() == typeid(neige).name())
                {
                    QMessageBox m;
                    m.setText(QString("Collision détectée entre le bloc de D et neige"));
                    m.exec();
                }
            }

            QList<QGraphicsItem *> CollidesLeft;
            CollidesLeft = pingouin->CollidesLeft();

            for(int i=0; i<CollidesLeft.length(); i++)
            {
                if(typeid(*CollidesLeft.at(i)).name() == typeid(neige).name())
                {
                    QMessageBox m;
                    m.setText(QString("Collision détectée entre le bloc de G et neige"));
                    m.exec();
                }
            }



            pingouin->moveBy(1, 0);
            pingouin->setPlayerOrientation("right");
        }
    }
    pingouin->getPlayer()->update();   //on recharge le painter
}

