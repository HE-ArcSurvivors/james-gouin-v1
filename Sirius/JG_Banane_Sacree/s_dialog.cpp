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

#include "s_dialog.h"

#include <QBrush>

S_Dialog::S_Dialog(int xpos, int ypos, QGraphicsItem *parent) : Surface(xpos, ypos, parent)
{
    setDesign();
}
S_Dialog::S_Dialog(QGraphicsItem *parent) : Surface(0, 0, parent)
{
    setDesign();
}

void S_Dialog::setDesign()
{
//    QBrush brush;
//    brush.setStyle(Qt::SolidPattern);
//    brush.setColor(Qt::red);

//    setBrush(brush);


}

void S_Dialog::setDialogNumber(int value)
{
    this->dialogNumber = value;
}

int S_Dialog::getDialogNumber()
{
    return this->dialogNumber;
}
