#ifndef E_LOUP_H
#define E_LOUP_H

#include "ennemi.h"

class E_Loup : public Ennemi
{
public:
    E_Loup(QList<QPoint> path);
};

#endif // E_LOUP_H
