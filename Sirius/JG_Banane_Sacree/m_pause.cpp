#include "m_pause.h"

M_Pause::M_Pause()
{
    resize(200,200);
//    layoutMenuPause = new QFormLayout;
//    groupBoxMenuPause = new QGroupBox;
//    titleMenuPause = new QLabel(tr("Menu PAUSE"));
//    titleMenuPause->setAlignment(Qt::AlignCenter);
//    titleMenuPause->setStyleSheet("margin-left: auto; margin-right : auto; color: blue; font: bold 20px;");
//    groupBoxMenuPause->setStyleSheet("text-align: center; color: blue; background-color: lightblue;");
//    groupBoxMenuPause->setGeometry(QRect(0,0,200,200));
//    titleMenuPause->setGeometry(QRect(0,0,200,200));
//    layoutMenuPause->addRow(titleMenuPause);
//    btnMenuPauseResume = new QPushButton(tr("Resume"));
//    btnMenuPauseConfigure = new QPushButton(tr("Configure"));
//    btnMenuPauseQuit = new QPushButton(tr("Quit"));
//    connect(btnMenuPauseQuit, SIGNAL(clicked()),this, SLOT(close()));
//    connect(btnMenuPauseResume, SIGNAL(clicked()),this, SLOT(resumeGame()));
//    layoutMenuPause->addRow(btnMenuPauseResume);
//    layoutMenuPause->addRow(btnMenuPauseConfigure);
//    layoutMenuPause->addRow(btnMenuPauseQuit);
//    groupBoxMenuPause->setLayout(layoutMenuPause);
    QLabel *testLabel = new QLabel("test");
    testLabel->setGeometry(100,100,100,100);
}
