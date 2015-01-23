#include "e_loup.h"
#include "gameboard.h"

E_Loup::E_Loup(QList<QPoint> path, Gameboard *g) : Ennemi(path, g)
{
    //vitesse entre 1 et 100
    // 1 étant très rapide, 100 étant très lent
    speed = 8; //vitesse par défaut

    leftSkin = ":/characters/characters/loup_left.png";
    rightSkin = ":/characters/characters/loup_right.png";
    upSkin = ":/characters/characters/loup_back.png";
    downSkin = ":/characters/characters/loup_front.png";

        setZValue(2);

    //Création du champs de vue
    int gs = Gameboard::getGameSquares();
    for(int i=1; i<=5; i++)
    {
        ViewBloc vb;
        vb.bloc = new QGraphicsRectItem(0,0, gs-2, gs-2);
        vb.bloc->setZValue(2);
        vb.colonne=i;
        vb.ligne=0;

        champVue.append(vb);
    }

    //il lui faut une orientation de base
    setOrientation_top();

}
