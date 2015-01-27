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

#include "m_pause.h"
#include <QGraphicsDropShadowEffect>
#include <QGraphicsEffect>
#include <QFrame>
#include <QStyleOption>
#include <QPainter>
#include <QLabel>
#include <QPushButton>
#include <QFormLayout>


M_Pause::M_Pause(QWidget *parent)
{
    this->setStyleSheet(
                        "text-align: center;"
                        "color: #2e2e2e;"
                        "background-color: #ffffff;"
                        "border-style: solid;"
                        "border-color: #d3d3d3;"
                        "border-width: 1px;"
                        "border-radius: 8px;"
                        );

    styleBtn = "border-style: none;"
                       "border-radius: 5px;"
                       "padding: 6px;"
                       "margin: 5px;"
                       "font-family: Century Gothic;"
                       "background-color: white;"
                       "color: white;"
                       "font-weight: bold;"
                       "background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #00A5FF, stop: 1 #3087F2);";

    layoutMenuPause = new QFormLayout;
    titleMenuPause = new QLabel(tr("Pause"));
    titleMenuPause->setAlignment(Qt::AlignCenter);
    titleMenuPause->setStyleSheet(
                                  "margin-left: auto;"
                                  "font-family: Century Gothic;"
                                  "margin-right : auto;"
                                  "color: #2e2e2e;"
                                  "font: bold 50px;"
                                  "border-style: none;"
                                  );


   undertitleMenuPause = new QLabel(tr("James Gouin prend sa pause..."));
   undertitleMenuPause->setAlignment(Qt::AlignCenter);
   undertitleMenuPause->setStyleSheet(
                                 "margin-left: auto;"
                                 "font-family: Century Gothic;"
                                 "margin-right : auto;"
                                 "color: #2e2e2e;"
                                 "font: bold 12px;"
                                 "border-style: none;"
                                 );


//    QGraphicsOpacityEffect * effect = new QGraphicsOpacityEffect(this);
//    effect->setOpacity(0.5);
//    this->setGraphicsEffect(effect);

    btnMenuPauseResume = new QPushButton(tr("Reprendre la Partie"));
    btnMenuPauseRestartEnigma = new QPushButton(tr("Retourner au dernier checkpoint"));
    btnMenuPauseRestartLevel = new QPushButton(tr("Redémarrer la partie"));
    btnMenuPauseIsland = new QPushButton(tr("Aller sur l'île"));
    btnMenuPauseQuit = new QPushButton(tr("Menu Principal"));

    btnMenuPauseResume->setStyleSheet(styleBtn);
    btnMenuPauseRestartEnigma->setStyleSheet(styleBtn);
    btnMenuPauseQuit->setStyleSheet(styleBtn);
    btnMenuPauseIsland->setStyleSheet(styleBtn);
    btnMenuPauseRestartLevel->setStyleSheet(styleBtn);

//    btnMenuPauseResume->setGraphicsEffect(shadowbtn());
//    btnMenuPauseRestartLevel->setGraphicsEffect(shadowbtn());
//    btnMenuPauseQuit->setGraphicsEffect(shadowbtn());
//    btnMenuPauseConfigure->setGraphicsEffect(shadowbtn());


    connect(btnMenuPauseQuit, SIGNAL(clicked()),parent, SLOT(exitGame()));
    connect(btnMenuPauseResume, SIGNAL(clicked()),parent, SLOT(resumeGame()));
    connect(btnMenuPauseRestartEnigma, SIGNAL(clicked()),parent, SLOT(restartEnigma()));
    connect(btnMenuPauseRestartLevel, SIGNAL(clicked()),parent, SLOT(restartLevel()));
    connect(btnMenuPauseIsland, SIGNAL(clicked()),parent, SLOT(returnIsland()));

    layoutMenuPause->addRow(titleMenuPause);
    layoutMenuPause->addRow(undertitleMenuPause);
    layoutMenuPause->addRow(btnMenuPauseResume);
    layoutMenuPause->addRow(btnMenuPauseRestartEnigma);
    layoutMenuPause->addRow(btnMenuPauseRestartLevel);
    layoutMenuPause->addRow(btnMenuPauseIsland);
    layoutMenuPause->addRow(btnMenuPauseQuit);

    this->resize(400,400);
    this->setLayout(layoutMenuPause);
}

QGraphicsDropShadowEffect* M_Pause::shadowbtn()
{
    QGraphicsDropShadowEffect* shadow = new QGraphicsDropShadowEffect();
    shadow->setBlurRadius(3);
    shadow->setColor(Qt::black);
    shadow->setOffset(0, 1);

    return shadow;
}

void M_Pause::paintEvent(QPaintEvent *pe)
{
  QStyleOption o;
  o.initFrom(this);
  QPainter p(this);
  style()->drawPrimitive(
  QStyle::PE_Widget, &o, &p, this);
}

void M_Pause::setUnableMenu(int levelValue)
{
    QString styleBtnUnable = "border-style: none;"
                       "border-radius: 5px;"
                       "padding: 6px;"
                       "margin: 5px;"
                       "font-family: Century Gothic;"
                       "background-color: white;"
                       "color: white;"
                       "font-weight: bold;"
                       "background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #c6c6c6, stop: 1 #b3b3b3);";

    switch(levelValue)
    {
    case 0: btnMenuPauseIsland->setDisabled(true);
            btnMenuPauseIsland->setStyleSheet(styleBtnUnable);
            break;
    case 1: btnMenuPauseIsland->setDisabled(true);
            btnMenuPauseIsland->setStyleSheet(styleBtnUnable);
            btnMenuPauseRestartLevel->setDisabled(true);
            btnMenuPauseRestartLevel->setStyleSheet(styleBtnUnable);
            btnMenuPauseRestartEnigma->setDisabled(true);
            btnMenuPauseRestartEnigma->setStyleSheet(styleBtnUnable);
            break;
    default:
        btnMenuPauseResume->setDisabled(false);
        btnMenuPauseRestartEnigma->setDisabled(false);
        btnMenuPauseQuit->setDisabled(false);
        btnMenuPauseIsland->setDisabled(false);
        btnMenuPauseRestartLevel->setDisabled(false);
        btnMenuPauseResume->setStyleSheet(styleBtn);
        btnMenuPauseRestartEnigma->setStyleSheet(styleBtn);
        btnMenuPauseQuit->setStyleSheet(styleBtn);
        btnMenuPauseIsland->setStyleSheet(styleBtn);
        btnMenuPauseRestartLevel->setStyleSheet(styleBtn);
    }
}
