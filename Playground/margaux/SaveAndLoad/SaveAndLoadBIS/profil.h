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

//private :
    QString username;
    QString startDate;
    QString saveDate;
    QString gameTime;
    int level;
    QList<int> power;
    int nbLive;
    int difficulty;
};

#endif // PROFIL_H
