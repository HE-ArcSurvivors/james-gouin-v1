#include <QApplication>
#include "game.h"
#include "menustart.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MenuStart menuStart;
    menuStart.resize(500,200);
    menuStart.show();

    return a.exec();

    //QCoreApplication app(argc, argv);

    Game game;
    /*game.newGame();
    // Game is played; changes are made...
    if (!game.saveGame(Game::Json))
        return 1;

    if (!game.saveGame(Game::Binary))
        return 1;
    */

    Game fromJsonGame;
    if (!fromJsonGame.loadGame(Game::Json))
        return 1;

    Game fromBinaryGame;
    if (!fromBinaryGame.loadGame(Game::Binary))
        return 1;

    return 0;
}
