#include "e_renard.h"
#include "gameboard.h"

E_Renard::E_Renard(QList<QPoint> path) : Ennemi(path)
{
    //vitesse entre 1 et 100
    // 1 étant très rapide, 100 étant très lent
    speed = 30; //vitesse par défaut

    leftSkin = ":/characters/characters/renard_left.png";
    rightSkin = ":/characters/characters/renard_right.png";
    upSkin = ":/characters/characters/renard_back.png";
    downSkin = ":/characters/characters/renard_front.png";

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

}
