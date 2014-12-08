#ifndef PLAYER_H
#define PLAYER_H

#include <QString>
#include <QDataStream>
#include <QJsonObject>

class QTextEdit;

class Player
{
    public:
        Player();

        friend QDataStream &operator>> (QDataStream&, Player&);
        friend QDataStream &operator<< (QDataStream&, const Player&);

        QString getUsername();
        QString getStartDate();
        QString getSaveDate();
        QString getGameTime();
        int getLevel();
        int* getPower();
        int getNbLive();
        int getDifficulty();

        void setUsername(QString);
        void setStartDate(QString);
        void setSaveDate(QString);
        void setGameTime(QString);
        void setLevel(int);
        void setPower(int*);
        void setNbLive(int);
        void setDifficulty(int);

        void read(const QJsonObject &json);
        void write(QJsonObject &json) const;

    //private :
        QString username;
        QString startDate;
        QString saveDate;
        QString gameTime;
        int level;
        int* power;
        int nbLive;
        int difficulty;
};

#endif // PLAYER_H
