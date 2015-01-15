#ifndef E_RENARD_H
#define E_RENARD_H

#include "ennemi.h"

/**
 * \brief Classe enfant de Enemie. Il se deplace et
 * voie.
 *
 * Il se deplace dans un patern généré entre
 * automatiquement entre deux points. Il regarde
 * devant lui dans un champ 3x2. Si le joueur entre
 * dans le change de vue du Renard, la partie est perdue.
 *
 */
class E_Renard : public Ennemi
{
public:
    E_Renard(QList<QPoint> path);
};

#endif // E_RENARD_H
