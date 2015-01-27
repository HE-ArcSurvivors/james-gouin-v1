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
