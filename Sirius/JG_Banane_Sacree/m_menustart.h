#ifndef MENUSTART_H
#define MENUSTART_H

#include <QWidget>

class QPushButton;
class QVBoxLayout;
class QSignalMapper;
class QLineEdit;
class QLabel;

class MenuStart : public QWidget
{
    Q_OBJECT
public:
    explicit MenuStart(QWidget *parent = 0);

    QList<QPushButton*> *listButtonProfil;
    QPushButton* buttonNew;
    QVBoxLayout* layoutMenu;
    QLineEdit* username;
    QPushButton* validate;
    QLabel *textPseudo;


    bool getProfil();

signals:
    void startGame(int,int,int);
    void refreshGameMenu();

public slots:
    void loadGame(QString value);
    void newGame();
    void newGameForm();

private :
    QSignalMapper* signalMapper;
    int totalForms;
    int maxTotalForms;

};

#endif // MENUSTART_H
