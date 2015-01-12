#include "e_loup.h"
#include "gameboard.h"

E_Loup::E_Loup(QList<QPoint> path) : Ennemi(path)
{
    //vitesse entre 1 et 100
    // 1 étant très rapide, 100 étant très lent
    speed = 20; //vitesse par défaut

    //Création du champs de vue
    int gs = Gameboard::getGameSquares();
    for(int i=1; i<=5; i++)
    {
        ViewBloc vb;
        vb.bloc = new QGraphicsRectItem(0,0, gs-2, gs-2);
        vb.colonne=i;
        vb.ligne=0;

        champVue.append(vb);
    }

}
