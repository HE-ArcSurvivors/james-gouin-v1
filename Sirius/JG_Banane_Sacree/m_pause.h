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
    M_Pause();

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
