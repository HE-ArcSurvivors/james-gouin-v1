#include "m_pause.h"

M_Pause::M_Pause(QWidget *parent)
{

    layoutMenuPause = new QFormLayout;
    titleMenuPause = new QLabel(tr("Menu PAUSE"));
    titleMenuPause->setAlignment(Qt::AlignCenter);
    titleMenuPause->setStyleSheet("margin-left: auto; margin-right : auto; color: blue; font: bold 40px;");
    this->setStyleSheet("text-align: center; color: blue; background-color: lightblue;");
    layoutMenuPause->addRow(titleMenuPause);
    btnMenuPauseResume = new QPushButton(tr("Resume"));
    btnMenuPauseRestartLevel = new QPushButton(tr("Restart Level"));
    btnMenuPauseRestartGame = new QPushButton(tr("Restart Game"));
    btnMenuPauseConfigure = new QPushButton(tr("Configure"));
    btnMenuPauseQuit = new QPushButton(tr("Quit"));
    connect(btnMenuPauseQuit, SIGNAL(clicked()),parent, SLOT(exitGame()));
    connect(btnMenuPauseResume, SIGNAL(clicked()),parent, SLOT(resumeGame()));
    connect(btnMenuPauseRestartLevel, SIGNAL(clicked()),parent, SLOT(restartLevel()));
    connect(btnMenuPauseRestartGame, SIGNAL(clicked()),parent, SLOT(restartGame()));
    layoutMenuPause->addRow(btnMenuPauseResume);
    layoutMenuPause->addRow(btnMenuPauseRestartLevel);
    layoutMenuPause->addRow(btnMenuPauseRestartGame);
    layoutMenuPause->addRow(btnMenuPauseConfigure);
    layoutMenuPause->addRow(btnMenuPauseQuit);
    this->setLayout(layoutMenuPause);

}
