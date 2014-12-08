#ifndef GAME_H
#define GAME_H

#include <QJsonObject>
#include <QList>

#include "profil.h"
//#include "level.h"

class Game
{
public:
    Game();

    enum SaveFormat {
        Json, Binary
    };

    const Profil &player() const;
    //const QList<Level> &levels() const;

    void newGame();
    bool loadGame(SaveFormat saveFormat);
    bool saveGame(SaveFormat saveFormat) const;

    void read(const QJsonObject &json);
    void write(QJsonObject &json) const;
private:
    Profil mPlayer;
    //QList<Level> mLevels;
};

#endif // GAME_H
