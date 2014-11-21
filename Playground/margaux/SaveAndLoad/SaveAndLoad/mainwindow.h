#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>

class QPushButton;

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QPushButton* buttonSave;
    QPushButton* buttonLoad;

public slots:
    void save();
    void load();
};

#endif // MAINWINDOW_H
