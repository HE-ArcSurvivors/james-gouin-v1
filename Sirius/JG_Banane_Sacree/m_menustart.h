#ifndef MENUSTART_H
#define MENUSTART_H

#include <QWidget>
#include "profil.h"

class QPushButton;
class QVBoxLayout;
class QSignalMapper;
class QLineEdit;
class QLabel;

/**
 * \brief Premier menu (start) que le joueur voie en lancant le jeu.
 *
 * QWidget du menu principal du jeu. Celui-ci permet de
 * créer un profile d'utilisateur et de lancer un partie
 * déjà existante dans un profile existant.
 * Les sauvegardes sont sauvées dans le repertoire :
 * MacOSX : Game.app/Contents/MacOS/save.json
 * Windows : Dans le meme dossier que Game.exe
 * A noter que la sauvegarde est en texte et n'est pas encrypté.
 */

class MenuStart : public QWidget
{
    Q_OBJECT
public:
    explicit MenuStart(QWidget *parent = 0);

    QList<QPushButton*> *listButtonProfil;
    QPushButton* buttonNew;
    QVBoxLayout* layoutMenu;
    QLineEdit* username;
    QPushButton* validate;
    QLabel *textPseudo;

    static void saveGame(Profil* currentUser);
    bool getProfil();

signals:
    void startGame(Profil*);
    void refreshGameMenu();

public slots:
    void loadGame(QString value);
    void newGame();
    void newGameForm();

private :
    QSignalMapper* signalMapper;
    int totalForms;
    int maxTotalForms;
    Profil *user;


};

#endif // MENUSTART_H
