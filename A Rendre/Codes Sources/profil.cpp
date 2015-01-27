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

#include "profil.h"
#include <qDebug>
#include <QDateTime>

int Profil::NBMAXVIE = 99;

Profil::Profil()
{
    this->username = "Nouveau";
    QDateTime current = QDateTime::currentDateTime();
    this->startDate = current.toString("dd:MM:yyyy:hh:mm");
    this->gameTime = "00:00:0000:00:00:00";
    this->saveDate = current.toString("dd:MM:yyyy:hh:mm");
    this->loadDate = current.toString("dd:MM:yyyy:hh:mm");
    this->level = 0;
    this->nbLive = 1;
    this->difficulty = 1;

    for(int i = 0; i < 8; i++)
    {
        power.append(0);
    }
}

Profil::Profil(const QString &username)
{
    this->username = username;
}

QString Profil::getUsername()
{
    return this->username;
}

QString Profil::getStartDate()
{
    return this->startDate;
}

QString Profil::getSaveDate()
{
    return this->saveDate;
}

QString Profil::getGameTime()
{
    return this->gameTime;
}

QString Profil::getLoadDate()
{
    return this->loadDate;
}

int Profil::getLevel()
{
    return this->level;
}

QList<int> Profil::getPower()
{
    return this->power;
}

int Profil::getNbLive()
{
    return this->nbLive;
}

int Profil::getDifficulty()
{
    return this->difficulty;
}

void Profil::setUsername(QString dataUsername)
{
    this->username = dataUsername;
}

void Profil::setStartDate(QString dataStartDate)
{
    this->startDate = dataStartDate;
}

void Profil::setSaveDate(QString dataSaveDate)
{
    this->saveDate = dataSaveDate;
}

void Profil::setGameTime(QString dataGameTime)
{
    this->gameTime = dataGameTime;
}

void Profil::setLevel(int dataLevel)
{
    this->level = dataLevel;
}

void Profil::setPower(QList<int> dataPower)
{
    this->power = dataPower;
}

void Profil::setNbLive(int dataNbLive)
{
    this->nbLive = dataNbLive;
}

void Profil::setDifficulty(int dataDifficulty)
{
    this->difficulty = dataDifficulty;
}

void Profil::read(const QJsonObject &json)
{
    this->username = json["username"].toString();
    this->startDate = json["startDate"].toString();
    this->gameTime = json["gameTime"].toString();
    this->saveDate = json["saveDate"].toString();
    this->level = json["level"].toInt();
    this->nbLive = json["nbLive"].toInt();
    this->difficulty = json["difficulty"].toInt();

    QString strpower = json["power"].toString();
    QStringList list = strpower.split("");
    power.clear();
    for(int i = 1; i < strpower.length(); i++)
    {
        int value = strpower.at(i).digitValue();
        this->power.append(value);
    }
}

void Profil::print()
{
    qDebug() << "Username : " << this->username;
    qDebug() << "Start Date : " << this->startDate;
    qDebug() << "Game Time : " << this->gameTime;
    qDebug() << "Save Date : " << this->saveDate;
    qDebug() << "Load Date : " << this->loadDate;
    qDebug() << "Level : " << this->level;
    qDebug() << "Nb Live : " << this->nbLive;
    qDebug() << "Difficulté : " << this->difficulty;
    qDebug() << "Power : " << power;
}


void Profil::write(QJsonObject &json) const
{
    json["username"] = username;
    json["startDate"] = startDate;
    json["gameTime"] = gameTime;
    json["saveDate"] = saveDate;
    json["level"] = level;
    json["nbLive"] = nbLive;
    json["difficulty"] = difficulty;

    QString strpower;
    for(int i = 0; i < power.length(); i++)
    {
        int value = power.at(i);
        strpower.append(QString::number(value));
    }
    json["power"] = strpower;
}
