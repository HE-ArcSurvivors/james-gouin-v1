/*********************************************************************************
* Copyright © Haute-Ecole ARC - All Rights Reserved
* Copyright © Banana Rocket - All Rights Reserved
*
* This file is part of <P2 Qt Project: James Gouin et la Banane Sacrée>.
*
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Claret-Yakovenko Roman <romain.claret@rocla.ch>, 27 January 2015
* Written by Divernois Margaux <margaux.divernois@gmail.com>, 27 January 2015
* Written by Visinand Steve <visinandst@gmail.com>, 27 January 2015
**********************************************************************************/

#ifndef PROFIL_H
#define PROFIL_H

#include <QString>
#include <QJsonObject>
#include <QList>

class Profil
{
public:
    Profil();
    Profil(const QString &username);

    QString getUsername();
    QString getStartDate();
    QString getSaveDate();
    QString getGameTime();
    QString getLoadDate();
    int getLevel();
    QList<int> getPower();
    int getNbLive();
    int getDifficulty();

    void setUsername(QString);
    void setStartDate(QString);
    void setSaveDate(QString);
    void setGameTime(QString);
    void setLevel(int);
    void setPower(QList<int>);
    void setNbLive(int);
    void setDifficulty(int);

    void read(const QJsonObject &json);
    void write(QJsonObject &json) const;
    void print();

    static int NBMAXVIE;

private :
    QString username;
    QString startDate;
    QString saveDate;
    QString gameTime;
    QString loadDate;
    int level;
    QList<int> power;
    int nbLive;
    int difficulty;
};

#endif // PROFIL_H
