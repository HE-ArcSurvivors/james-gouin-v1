#include "player.h"

#include <QTextEdit>

Player::Player()
{

}

QDataStream &operator>>(QDataStream &in, Player &o)
{
    //in >> o.level_number >> o.username;
    return in;
}

QDataStream &operator<<(QDataStream &out, const Player &o)
{
    //out << o.level_number << o.username;
    return out;
}

QString Player::getUsername()
{
    return this->username;
}

QString Player::getStartDate()
{
    return this->startDate;
}

QString Player::getSaveDate()
{
    return this->saveDate;
}

QString Player::getGameTime()
{
    return this->gameTime;
}

int Player::getLevel()
{
    return this->level;
}

int* Player::getPower()
{
    return this->power;
}

int Player::getNbLive()
{
    return this->nbLive;
}

int Player::getDifficulty()
{
    return this->difficulty;
}


void Player::setUsername(QString dataUsername)
{
    this->username = dataUsername;
}

void Player::setStartDate(QString dataStartDate)
{
    this->startDate = dataStartDate;
}

void Player::setSaveDate(QString dataSaveDate)
{
    this->saveDate = dataSaveDate;
}

void Player::setGameTime(QString dataGameTime)
{
    this->gameTime = dataGameTime;
}

void Player::setLevel(int dataLevel)
{
    this->level = dataLevel;
}

void Player::setPower(int* dataPower)
{
    this->power = dataPower;
}

void Player::setNbLive(int dataNbLive)
{
    this->nbLive = dataNbLive;
}

void Player::setDifficulty(int dataDifficulty)
{
    this->difficulty = dataDifficulty;
}

void Player::read(const QJsonObject &json)
{
    this->username = json["username"].toString();
    this->level = json["level"].toInt();
}

void Player::write(QJsonObject &json) const
{
    json["username"] = username;
    json["level"] = level;
}
