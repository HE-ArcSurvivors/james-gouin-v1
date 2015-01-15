#include "m_pause.h"
#include <QGraphicsDropShadowEffect>
#include <QGraphicsEffect>
#include <QFrame>
#include <QStyleOption>
#include <QPainter>

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

    QString styleBtn = "border-style: none;"
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


    btnMenuPauseResume = new QPushButton(tr("Resume"));
    btnMenuPauseRestartLevel = new QPushButton(tr("Restart Level"));
    btnMenuPauseRestartGame = new QPushButton(tr("Restart Game"));
    btnMenuPauseConfigure = new QPushButton(tr("Configure"));
    btnMenuPauseQuit = new QPushButton(tr("Quit"));


    btnMenuPauseResume->setStyleSheet(styleBtn);
    btnMenuPauseRestartLevel->setStyleSheet(styleBtn);
    btnMenuPauseQuit->setStyleSheet(styleBtn);
    btnMenuPauseConfigure->setStyleSheet(styleBtn);
    btnMenuPauseRestartGame->setStyleSheet(styleBtn);



//    btnMenuPauseResume->setGraphicsEffect(shadowbtn());
//    btnMenuPauseRestartLevel->setGraphicsEffect(shadowbtn());
//    btnMenuPauseQuit->setGraphicsEffect(shadowbtn());
//    btnMenuPauseConfigure->setGraphicsEffect(shadowbtn());


    connect(btnMenuPauseQuit, SIGNAL(clicked()),parent, SLOT(exitGame()));
    connect(btnMenuPauseResume, SIGNAL(clicked()),parent, SLOT(resumeGame()));
    connect(btnMenuPauseRestartLevel, SIGNAL(clicked()),parent, SLOT(restartLevel()));
    connect(btnMenuPauseRestartGame, SIGNAL(clicked()),parent, SLOT(restartGame()));

    layoutMenuPause->addRow(titleMenuPause);
    layoutMenuPause->addRow(undertitleMenuPause);
    layoutMenuPause->addRow(btnMenuPauseResume);
    layoutMenuPause->addRow(btnMenuPauseRestartLevel);
    layoutMenuPause->addRow(btnMenuPauseRestartGame);
    layoutMenuPause->addRow(btnMenuPauseConfigure);
    layoutMenuPause->addRow(btnMenuPauseQuit);

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
