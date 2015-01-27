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

#include "e_renard.h"
#include "gameboard.h"

E_Renard::E_Renard(QList<QPoint> path, Gameboard *g) : Ennemi(path, g)
{
    //vitesse entre 1 et 100
    // 1 étant très rapide, 100 étant très lent
    speed = 10; //vitesse par défaut

    leftSkin = ":/characters/characters/renard_left.png";
    rightSkin = ":/characters/characters/renard_right.png";
    upSkin = ":/characters/characters/renard_back.png";
    downSkin = ":/characters/characters/renard_front.png";

        setZValue(2);

    //Création du champs de vue
    int gs = Gameboard::getGameSquares();
    for(int i=1; i<=2; i++)
    {
        for(int j=-1; j<=1; j++)
        {
            ViewBloc vb;
            vb.bloc = new QGraphicsRectItem(0,0, gs-2, gs-2);
            vb.bloc->setZValue(2);
            vb.colonne=i;
            vb.ligne=j;

            champVue.append(vb);
        }
    }

    //il lui faut une orientation de base
    setOrientation_top();
}
