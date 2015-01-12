#ifndef E_RENARD_H
#define E_RENARD_H

#include "ennemi.h"


class E_Renard : public Ennemi
{
public:
    E_Renard(QList<QPoint> path);
};

#endif // E_RENARD_H
