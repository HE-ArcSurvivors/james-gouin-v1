#ifndef M_PAUSE_H
#define M_PAUSE_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QGroupBox>
#include <QFormLayout>



class M_Pause : public QWidget
{
    Q_OBJECT
public:
    M_Pause(QWidget *parent = 0, int viewStartPostionX=0, int viewStartPostionY=0, int windowSizeX=0, int windowSizeY=0, int menuPauseSizeX=0, int menuPauseSizeY=0);

private:
    QFormLayout *layoutMenuPause;
    QGroupBox *groupBoxMenuPause;
    QLabel *titleMenuPause;

    QPushButton *btnMenuPauseResume;
    QPushButton *btnMenuPauseConfigure;
    QPushButton *btnMenuPauseQuit;

signals:

public slots:

};

#endif // M_PAUSE_H
