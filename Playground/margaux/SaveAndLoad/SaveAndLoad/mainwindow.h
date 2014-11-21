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

    QPushButton* buttonCreate;
    QPushButton* buttonSave;
    QPushButton* buttonLoad;
    QPushButton* buttonExit;

    // DATA TEST
    int level_number;
    QString username;

public slots:
    void save();
    void load();

    void createIni();
    void saveIni();
    void loadIni();
    void exit();
};

#endif // MAINWINDOW_H
