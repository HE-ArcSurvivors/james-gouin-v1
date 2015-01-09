#ifndef M_PAUSE_H
#define M_PAUSE_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QFormLayout>



class M_Pause : public QWidget
{
    Q_OBJECT
public:
    M_Pause(QWidget *parent);

private:
    QFormLayout *layoutMenuPause;
    QLabel *titleMenuPause;

    QPushButton *btnMenuPauseResume;
    QPushButton *btnMenuPauseConfigure;
    QPushButton *btnMenuPauseQuit;
    QPushButton *btnMenuPauseRestartLevel;
    QPushButton *btnMenuPauseRestartGame;

signals:

public slots:

};

#endif // M_PAUSE_H
