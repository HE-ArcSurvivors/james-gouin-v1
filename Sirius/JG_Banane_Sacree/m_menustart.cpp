/*********************************************************************************
* Copyright © Haute-Ecole ARC - All Rights Reserved
* Copyright © Banana Rocket - All Rights Reserved
*
* This file is part of <P2 Qt Project: James Gouin et la Banane Sacrée>.
*
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Claret-Yakovenko Roman <romain.claret@rocla.ch>, 27 January 2015
* Written by Divernois Margaux <margaux.divernois@gmail.com>, 27 January 2015
* Written by Visinand Steve <visinandst@gmail.com>, 27 January 2015
**********************************************************************************/

#include "m_menustart.h"
#include "profil.h"

#include <QPushButton>
#include <QList>
#include <QVBoxLayout>
#include <QFile>
#include <qDebug>
#include <QByteArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QSignalMapper>
#include <iterator>
#include <QLabel>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QDir>
#include <QDateTime>

#include "m_pause.h"
#include "gameboard.h"

MenuStart::MenuStart(QWidget *parent) :
    QWidget(parent)
{

    this->setStyleSheet(
                        "color: #2e2e2e;"
                        "font-family: Century Gothic;"
                        );

    QString styleBtn = "border-style: none;"
                       "border-radius: 5px;"
                       "padding: 6px;"
                       "margin: 5px;"

                       "background-color: white;"
                       "color: white;"
                       "font-weight: bold;"
                       "background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #00A5FF, stop: 1 #3087F2);";

    user = new Profil();
    maxTotalForms = 5;
    listButtonProfil = new QList<QPushButton*>();

    buttonNew = new QPushButton("Nouvelle partie");
    buttonNew->setStyleSheet(styleBtn);

    layoutMenu = new QVBoxLayout;

    getProfil();
    signalMapper = new QSignalMapper();
    totalForms = listButtonProfil->size();
    for(int i = 0; i < totalForms; i++)
    {
       layoutMenu->addWidget(listButtonProfil->at(i));
       listButtonProfil->at(i)->setStyleSheet(styleBtn);
       QObject::connect(listButtonProfil->at(i), SIGNAL(clicked()), signalMapper, SLOT(map()));
       signalMapper->setMapping(listButtonProfil->at(i),listButtonProfil->at(i)->text());
    }

    validate = new QPushButton("Créer");
    textPseudo = new QLabel("Surnom : ");

    QObject::connect(signalMapper, SIGNAL(mapped(QString)),this, SLOT(loadGame(QString)));
    QObject::connect(buttonNew,SIGNAL(clicked()),this,SLOT(newGameForm()));
    QObject::connect(validate,SIGNAL(clicked()),this,SLOT(newGame()));

    if (totalForms < maxTotalForms)
    {
        layoutMenu->addWidget(buttonNew);
    }
    setLayout(layoutMenu);
}

bool MenuStart::getProfil()
{
    QFile loadFile("save.json");

    loadFile.open(QIODevice::ReadOnly);

    QByteArray saveData = loadFile.readAll();
    //qDebug() << saveData;

    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));
    QStringList listeProfil = loadDoc.object().keys();
    totalForms = listeProfil.size();
    for (int i = 0; i < totalForms; i++)
    {
        listButtonProfil->append(new QPushButton(listeProfil.at(i)));
        //qDebug() << listeProfil.at(i) << endl;
    }
    loadFile.close();
    return true;
}

void MenuStart::loadGame(QString value)
{
    qDebug() << "LOAD";

    QFile loadFile("save.json");

    loadFile.open(QIODevice::ReadOnly);

    QByteArray saveData = loadFile.readAll();
    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));
    QJsonObject object = loadDoc.object();
    Profil* user = new Profil();

    user->read(object[value].toObject());
    user->print();

    loadFile.close();

    emit startGame(user);

}

void MenuStart::newGameForm()
{
    if (totalForms < maxTotalForms)
    {
        buttonNew->hide();
        totalForms++;
        username = new QLineEdit(this);
        username->grabKeyboard();

        QHBoxLayout* layoutNewGame = new QHBoxLayout;
        layoutNewGame->addWidget(textPseudo);
        layoutNewGame->addWidget(username);
        layoutNewGame->addWidget(validate);
        layoutMenu->addLayout(layoutNewGame);
    }else{
//        buttonNew->hide();
    }
}

void MenuStart::newGame()
{
//    qDebug() << "NEW";
    if (username->text() != "")
    {
        Profil* newProfil = new Profil();
        newProfil->setUsername(username->text());

        // LIS LE FICHIER POUR GARDER LES DONNEES
        QFile loadFile("save.json");
        loadFile.open(QIODevice::ReadOnly);

        QByteArray loadData = loadFile.readAll();
        QJsonDocument loadDoc(QJsonDocument::fromJson(loadData));
        QJsonObject object = loadDoc.object();

        // LIS LE FICHIER POUR ENREGISTRER
        QFile saveFile(QStringLiteral("save.json"));
        saveFile.open(QIODevice::WriteOnly);

        QJsonObject gameObject;
        QJsonObject playerObject;
        newProfil->write(playerObject);
        newProfil->print();

        gameObject = object;
        gameObject[newProfil->getUsername()] = playerObject;

        QJsonDocument saveDoc(gameObject);
        saveFile.write(saveDoc.toJson());
        saveFile.close();
        loadFile.close();

        username->releaseKeyboard();

        validate->hide();
        username->hide();
        textPseudo->hide();

        emit startGame(newProfil);

    }
}

void MenuStart::saveGame(Profil* currentUser)
{
    qDebug() << "SAVE";

    // LIS LE FICHIER POUR GARDER LES DONNEES
    QFile loadFile("save.json");
    loadFile.open(QIODevice::ReadOnly);

    QByteArray loadData = loadFile.readAll();
    QJsonDocument loadDoc(QJsonDocument::fromJson(loadData));
    QJsonObject object = loadDoc.object();

    QStringList loadDate = currentUser->getLoadDate().split(":");
    qDebug() << "LoadDate :" << loadDate;
    QStringList saveDate = currentUser->getGameTime().split(":");
    qDebug() << "SaveDate :" << saveDate;

    QDateTime current = QDateTime::currentDateTime();
    QStringList currentDate = current.toString("dd:MM:yyyy:hh:mm").split(":");
    qDebug() << "CurrentDate" << currentDate;

    int dd = saveDate.at(0).toInt() + currentDate.at(0).toInt() - loadDate.at(0).toInt();
    int MM = saveDate.at(1).toInt() + currentDate.at(1).toInt() - loadDate.at(1).toInt();
    int yyyy = saveDate.at(2).toInt() + currentDate.at(2).toInt() - loadDate.at(2).toInt();
    int hh = saveDate.at(3).toInt() + currentDate.at(3).toInt() - loadDate.at(3).toInt();
    int mm = saveDate.at(4).toInt() + currentDate.at(4).toInt() - loadDate.at(4).toInt();
    qDebug() << dd << ":" << MM << ":" << yyyy << ":" << hh << ":" << mm;

    QString newGameTime = QString("%1:%2:%3:%4:%5").arg(dd,2,2, QLatin1Char('0')).arg(MM,2,2,QLatin1Char('0')).arg(yyyy,4,4, QLatin1Char('0')).arg(hh,2,2, QLatin1Char('0')).arg(mm,2,2, QLatin1Char('0'));
    qDebug() << newGameTime;

    currentUser->setGameTime(newGameTime);

    //    Profil* user = new Profil();
    //    user->read(object[currentUser->getUsername()].toObject());

    // LIS LE FICHIER POUR ENREGISTRER
    QFile saveFile(QStringLiteral("save.json"));
    saveFile.open(QIODevice::WriteOnly);

    QJsonObject gameObject;
    QJsonObject playerObject;

    currentUser->write(playerObject);
    currentUser->print();

    gameObject = object;
    gameObject[currentUser->getUsername()] = playerObject;

    QJsonDocument saveDoc(gameObject);
    saveFile.write(saveDoc.toJson());
    saveFile.close();
    loadFile.close();

}

