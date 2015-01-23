#ifndef M_PAUSE_H
#define M_PAUSE_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QFormLayout>
#include <QGraphicsDropShadowEffect>



class M_Pause : public QWidget
{
    Q_OBJECT
public:
    M_Pause(QWidget *parent);

    void setUnableMenu(int levelValue);

private:
    QFormLayout *layoutMenuPause;
    QLabel *titleMenuPause;
    QLabel *undertitleMenuPause;

    QPushButton *btnMenuPauseResume;
    QPushButton *btnMenuPauseIsland;
    QPushButton *btnMenuPauseQuit;
    QPushButton *btnMenuPauseRestartLevel;
    QPushButton *btnMenuPauseRestartGame;

    QString styleBtn;

    QGraphicsDropShadowEffect* shadowbtn();
    void paintEvent(QPaintEvent *pe);

signals:

public slots:

};

#endif // M_PAUSE_H
