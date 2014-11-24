#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <player.h>

class QPushButton;
class QGridLayout;
class QLineEdit;
class QComboBox;

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

    QGridLayout* layout;
    QLineEdit* username_insert;
    QComboBox* username_select;
    Player* current_player;

public slots:
    void save();
    void load();

    void createIni();
    void saveIni();
    void loadIni();
    void exit();
};

#endif // MAINWINDOW_H
