#include "mainwindow.h"
#include "menustart.h"
#include "player.h"
#include "game.h"
#include <QApplication>
#include <QCoreApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //QCoreApplication app(argc, argv);

    //MainWindow w;
    //MenuStart w;
    //w.show();

    Game game;
    game.newGame();

    /*if (!game.saveGame(Game::Json))
    {
        return 1;
    }
    if (!game.saveGame(Game::Binary))
    {
        return 1;
    }

    Game fromJsonGame;
    if (!fromJsonGame.loadGame(Game::Json))
    {
        return 1;
    }
    Game fromBinaryGame;
    if (!fromBinaryGame.loadGame(Game::Binary))
    {
        return 1;
    }*/

    return a.exec();
}
