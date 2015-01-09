#include "level.h"
#include "gameboard.h"
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QGraphicsScene>

#include "b_wall.h"
#include "b_water.h"
#include "b_movable.h"
#include "s_snow.h"
#include "s_ice.h"
#include "s_viewtransition.h"
#include "object.h"

#include <QPoint>
#include <QDebug>

Level::Level(QString levelName)
{
    this->levelName = new QString(levelName);
    neededItem = new QString("Poisson");

    maxBlocksHeight = 2*Gameboard::sizeY;
    maxBlocksWidth = 3*Gameboard::sizeX;

    startingPoint = new QPoint(0,0);
    viewStart = new QPoint(0,0);
}

QString* Level::getNeededItem()
{
    return this->neededItem;
}

QPoint* Level::getStartingPoint()
{
    return this->startingPoint;
}

QGraphicsScene* Level::populateScene()
{
    QGraphicsScene* scene = new QGraphicsScene();

    getSceneSize();

    int Mat_Walls_Blocks[maxBlocksWidth][maxBlocksHeight];
    int Mat_Movable_Blocks[maxBlocksWidth][maxBlocksHeight];
    int Mat_Items[maxBlocksWidth][maxBlocksHeight];
    int Mat_Bonus[maxBlocksWidth][maxBlocksHeight];
    int Mat_Enemies[maxBlocksWidth][maxBlocksHeight];
    int Mat_Scene_End[maxBlocksWidth][maxBlocksHeight];
    int Mat_Doors[maxBlocksWidth][maxBlocksHeight];
    int Mat_Water_Blocks[maxBlocksWidth][maxBlocksHeight];
    int Mat_Snow_Surface[maxBlocksWidth][maxBlocksHeight];
    int Mat_Ice_Surface[maxBlocksWidth][maxBlocksHeight];
    int Mat_Item_Shoes[maxBlocksWidth][maxBlocksHeight];

    for (int matY = 0; matY < maxBlocksHeight; matY++)
    {
        for (int matX = 0; matX < maxBlocksWidth; matX++)
        {
            Mat_Walls_Blocks[matX][matY] = 0;
            Mat_Movable_Blocks[matX][matY] = 0;
            Mat_Items[matX][matY] = 0;
            Mat_Bonus[matX][matY] = 0;
            Mat_Doors[matX][matY] = 0;
            Mat_Water_Blocks[matX][matY] = 0;
            Mat_Snow_Surface[matX][matY] = 0;
            Mat_Ice_Surface[matX][matY] = 0;
            Mat_Item_Shoes[matX][matY] = 0;
            Mat_Enemies[matX][matY] = 0;
            Mat_Scene_End[matX][matY] = 0;

        }
    }

    QString background = ":/maps/maps/";
    background.append(levelName);
    background.append(".png");
    QPixmap pixmapBackground(background);
    scene->setBackgroundBrush(pixmapBackground);

    QString map = ":/maps/maps/";
    map.append(levelName);
    map.append(".txt");

    QFile f(map);

    if(f.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream t(&f);
        QString line[1000];
        QString s;
        int line_count=0;

        int matX, matY;

        while(!t.atEnd())
        {
            line_count++;
            line[line_count]=t.readLine();
            if(line[line_count].contains("[header]"))
            {
                line_count++;
                line[line_count] = t.readLine();
                QStringList valueWidth = line[line_count].split("=");
                maxBlocksWidth = valueWidth.at(1).toInt();

                line_count++;
                line[line_count] = t.readLine();
                QStringList valueHeight = line[line_count].split("=");
                maxBlocksHeight = valueHeight.at(1).toInt();
            }

            if(line[line_count].contains("type=Walls_Blocks"))
            {
                line_count ++;
                line[line_count]=t.readLine();
                line_count ++;
                line[line_count]=t.readLine();
//              qDebug() << "Found Layer: " << line[line_count] << " at: " << line_count;
                for (matY = 0; matY < maxBlocksHeight; matY++)
                {
                    QStringList values = line[line_count].split(",");

//                    qDebug() << "Flaged: " << line[line_count] << " at: " << line_count;
//                    qDebug() << "Values: " << values;
                    for (matX = 0; matX < maxBlocksWidth; matX++)
                    {
                        Mat_Walls_Blocks[matX][matY] = values.at(matX).toInt();
//                        qDebug() << "Value: " << Walls[matX][matY];
                    }
                    line_count++;
                    line[line_count]=t.readLine();
                }
            }

            if(line[line_count].contains("type=Solid_Blocks"))
            {
                line_count ++;
                line[line_count]=t.readLine();
                line_count ++;
                line[line_count]=t.readLine();
                for (matY = 0; matY < maxBlocksHeight; matY++)
                {
                    QStringList values = line[line_count].split(",");

                    for (matX = 0; matX < maxBlocksWidth; matX++)
                    {
                        Mat_Walls_Blocks[matX][matY] += values.at(matX).toInt();
                    }
                    line_count++;
                    line[line_count]=t.readLine();
                }
            }

            if(line[line_count].contains("type=Movable_Blocks"))
            {
                line_count ++;
                line[line_count]=t.readLine();
                line_count ++;
                line[line_count]=t.readLine();

                for (matY = 0; matY < maxBlocksHeight; matY++)
                {
                    QStringList values = line[line_count].split(",");

                    for (matX = 0; matX < maxBlocksWidth; matX++)
                    {
                        Mat_Movable_Blocks[matX][matY] = values.at(matX).toInt();
                    }
                    line_count++;
                    line[line_count]=t.readLine();
                }
            }

            if(line[line_count].contains("type=Items"))
            {
                line_count ++;
                line[line_count]=t.readLine();
                line_count ++;
                line[line_count]=t.readLine();

                for (matY = 0; matY < maxBlocksHeight; matY++)
                {
                    QStringList values = line[line_count].split(",");

                    for (matX = 0; matX < maxBlocksWidth; matX++)
                    {
                        Mat_Items[matX][matY] = values.at(matX).toInt();
                    }
                    line_count++;
                    line[line_count]=t.readLine();
                }
            }

            if(line[line_count].contains("type=Bonus"))
            {
                line_count ++;
                line[line_count]=t.readLine();
                line_count ++;
                line[line_count]=t.readLine();

                for (matY = 0; matY < maxBlocksHeight; matY++)
                {
                    QStringList values = line[line_count].split(",");

                    for (matX = 0; matX < maxBlocksWidth; matX++)
                    {
                        Mat_Bonus[matX][matY] = values.at(matX).toInt();
                    }
                    line_count++;
                    line[line_count]=t.readLine();
                }
            }

            if(line[line_count].contains("type=Enemies"))
            {
                line_count ++;
                line[line_count]=t.readLine();
                line_count ++;
                line[line_count]=t.readLine();

                for (matY = 0; matY < maxBlocksHeight; matY++)
                {
                    QStringList values = line[line_count].split(",");

                    for (matX = 0; matX < maxBlocksWidth; matX++)
                    {
                        Mat_Enemies[matX][matY] = values.at(matX).toInt();
                    }
                    line_count++;
                    line[line_count]=t.readLine();
                }
            }

            if(line[line_count].contains("type=Scene_Start"))
            {
                line_count ++;
                line[line_count]=t.readLine();
                line_count ++;
                line[line_count]=t.readLine();

                for(matY = 0; matY < maxBlocksHeight; matY++)
                {
                    QStringList values = line[line_count].split(",");

                    for (matX = 0; matX < maxBlocksWidth; matX++)
                    {
                        if(values.at(matX).toInt() != 0)
                        {
                            startingPoint->setX(matX+1);
                            startingPoint->setY(matY+1);
                        }
                    }
                    line_count++;
                    line[line_count]=t.readLine();
                }
            }

            if(line[line_count].contains("type=Scene_End"))
            {
                line_count ++;
                line[line_count]=t.readLine();
                line_count ++;
                line[line_count]=t.readLine();

                for (matY = 0; matY < maxBlocksHeight; matY++)
                {
                    QStringList values = line[line_count].split(",");

                    for (matX = 0; matX < maxBlocksWidth; matX++)
                    {
                        Mat_Scene_End[matX][matY] = values.at(matX).toInt();
                    }
                    line_count++;
                    line[line_count]=t.readLine();
                }
            }
            if(line[line_count].contains("type=Doors"))
            {
                line_count ++;
                line[line_count]=t.readLine();
                line_count ++;
                line[line_count]=t.readLine();

                for (matY = 0; matY < maxBlocksHeight; matY++)
                {
                    QStringList values = line[line_count].split(",");

                    for (matX = 0; matX < maxBlocksWidth; matX++)
                    {
                        Mat_Doors[matX][matY] = values.at(matX).toInt();
                    }
                    line_count++;
                    line[line_count]=t.readLine();
                }
            }

            if(line[line_count].contains("type=Water_Blocks"))
            {
                line_count ++;
                line[line_count]=t.readLine();
                line_count ++;
                line[line_count]=t.readLine();
                for (matY = 0; matY < maxBlocksHeight; matY++)
                {
                    QStringList values = line[line_count].split(",");

                    for (matX = 0; matX < maxBlocksWidth; matX++)
                    {
                        Mat_Water_Blocks[matX][matY] = values.at(matX).toInt();
                    }
                    line_count++;
                    line[line_count]=t.readLine();
                }
            }

            if(line[line_count].contains("type=NoMoves_Blocks"))
            {
                line_count ++;
                line[line_count]=t.readLine();
                line_count ++;
                line[line_count]=t.readLine();

                for (matY = 0; matY < maxBlocksHeight; matY++)
                {
                    QStringList values = line[line_count].split(",");

                    for (matX = 0; matX < maxBlocksWidth; matX++)
                    {
                        Mat_Walls_Blocks[matX][matY] += values.at(matX).toInt();
                    }
                    line_count++;
                    line[line_count]=t.readLine();
                }
            }


            if(line[line_count].contains("type=Snow_Surface"))
            {
                line_count ++;
                line[line_count]=t.readLine();
                line_count ++;
                line[line_count]=t.readLine();

                for (matY = 0; matY < maxBlocksHeight; matY++)
                {
                    QStringList values = line[line_count].split(",");

                    for (matX = 0; matX < maxBlocksWidth; matX++)
                    {
                        Mat_Snow_Surface[matX][matY] = values.at(matX).toInt();
                    }
                    line_count++;
                    line[line_count]=t.readLine();
                }
            }

            if(line[line_count].contains("type=Ice_Surface"))
            {
                line_count ++;
                line[line_count]=t.readLine();
                line_count ++;
                line[line_count]=t.readLine();

                for (matY = 0; matY < maxBlocksHeight; matY++)
                {
                    QStringList values = line[line_count].split(",");

                    for (matX = 0; matX < maxBlocksWidth; matX++)
                    {
                        Mat_Ice_Surface[matX][matY] = values.at(matX).toInt();
                    }
                    line_count++;
                    line[line_count]=t.readLine();
                }
            }

            if(line[line_count].contains("type=Item_Shoes"))
            {
                line_count ++;
                line[line_count]=t.readLine();
                line_count ++;
                line[line_count]=t.readLine();

                for (matY = 0; matY < maxBlocksHeight; matY++)
                {
                    QStringList values = line[line_count].split(",");

                    for (matX = 0; matX < maxBlocksWidth; matX++)
                    {
                        Mat_Item_Shoes[matX][matY] = values.at(matX).toInt();
                    }
                    line_count++;
                    line[line_count]=t.readLine();
                }
            }
        }
        f.resize(0);
        t << s;
        f.close();
    }

    // Populate scene
    for (int i = 0; i < maxBlocksWidth; i++) {

        for (int j = 0; j < maxBlocksHeight; j++)
        {
            if (Mat_Walls_Blocks[i][j] != 0)
            {
                B_Wall *item = new B_Wall();
                item->setPos(i,j);
                scene->addItem(item);
            }
            if (Mat_Movable_Blocks[i][j] != 0)
            {
                B_Movable *item = new B_Movable(i,j);
                item->addToScene(scene);
            }
            if (Mat_Items[i][j] != 0)
            {
                Object *item = new Object(QString("Poisson"));
                item->setPos(i, j);
                scene->addItem(item);
            }
            if (Mat_Bonus[i][j] != 0)
            {
                Object *item = new Object("Oeuf");
                item->setPos(i, j);
                scene->addItem(item);
            }
            if(Mat_Item_Shoes[i][j] != 0)
            {
                Object *item = new Object("Chaussure");
                item->setPos(i, j);
                scene->addItem(item);
            }
//            if (Mat_Enemies[i][j] != 0)
//            {
//                QGraphicsItem *item = new B_Wall();
//                item->setPos(QPointF(i*gameSquares, j*gameSquares));
//                scene->addItem(item);
//            }
//            if (Mat_Scene_End[i][j] != 0)
//            {
//                QGraphicsItem *item = new B_Wall();
//                item->setPos(QPointF(i*gameSquares, j*gameSquares));
//                scene->addItem(item);
//            }
            if (Mat_Doors[i][j] != 0)
            {
                S_ViewTransition *item = new S_ViewTransition();
                item->setPos(i,j);
                scene->addItem(item);
            }
            if (Mat_Water_Blocks[i][j] != 0)
            {
                B_Water *item = new B_Water();
                item->setPos(i,j);
                scene->addItem(item);
            }
            if (Mat_Snow_Surface[i][j] != 0)
            {
                S_Snow *item = new S_Snow();
                item->setPos(i,j);
                scene->addItem(item);
            }
            if (Mat_Ice_Surface[i][j] != 0)
            {
                S_Ice *item = new S_Ice();
                item->setPos(i,j);
                scene->addItem(item);
            }
        }
    }
    return scene;
}


void Level::getSceneSize()
{
    QString map = ":/maps/maps/";
    map.append(levelName);
    map.append(".txt");

    QFile f(map);

    if(f.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream t(&f);
        QString line[1000];
        QString s;
        int line_count=0;

        while(!t.atEnd())
        {
            line_count++;
            line[line_count]=t.readLine();
            if(line[line_count].contains("[header]"))
            {
                line_count++;
                line[line_count] = t.readLine();
                QStringList valueWidth = line[line_count].split("=");
                maxBlocksWidth = valueWidth.at(1).toInt();

                line_count++;
                line[line_count] = t.readLine();
                QStringList valueHeight = line[line_count].split("=");
                maxBlocksHeight = valueHeight.at(1).toInt();

                line_count++;
                line[line_count] = t.readLine();
                QStringList valueViewX = line[line_count].split("=");
                viewStart->setX(valueViewX.at(1).toInt());

                line_count++;
                line[line_count] = t.readLine();
                QStringList valueViewY = line[line_count].split("=");
                viewStart->setY(valueViewY.at(1).toInt());
            }
        }
    }
    f.close();
 }

QPoint Level::getViewStart()
{
    return *(this->viewStart);
}
