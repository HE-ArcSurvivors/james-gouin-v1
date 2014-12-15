#include "m_pause.h"

M_Pause::M_Pause(QWidget *parent, int viewStartPostionX, int viewStartPostionY, int windowSizeX, int windowSizeY, int menuPauseSizeX, int menuPauseSizeY) :
    QWidget(parent)
{
    layoutMenuPause = new QFormLayout;
    groupBoxMenuPause = new QGroupBox;
    titleMenuPause = new QLabel(tr("Menu PAUSE"));
    titleMenuPause->setAlignment(Qt::AlignCenter);
    titleMenuPause->setStyleSheet("margin-left: auto; margin-right : auto; color: blue; font: bold 20px;");
    groupBoxMenuPause->setStyleSheet("text-align: center; color: blue; background-color: lightblue;");
    groupBoxMenuPause->setGeometry(viewStartPostionX+windowSizeX/2-menuPauseSizeX/2,viewStartPostionY+windowSizeY/2-menuPauseSizeY/2,menuPauseSizeX,menuPauseSizeY);
    layoutMenuPause->addRow(titleMenuPause);
    btnMenuPauseResume = new QPushButton(tr("Resume"));
    btnMenuPauseConfigure = new QPushButton(tr("Configure"));
    btnMenuPauseQuit = new QPushButton(tr("Quit"));
    connect(btnMenuPauseQuit, SIGNAL(clicked()),this, SLOT(close()));
    connect(btnMenuPauseResume, SIGNAL(clicked()),this, SLOT(resumeGame()));
    layoutMenuPause->addRow(btnMenuPauseResume);
    layoutMenuPause->addRow(btnMenuPauseConfigure);
    layoutMenuPause->addRow(btnMenuPauseQuit);
    groupBoxMenuPause->setLayout(layoutMenuPause);
}
