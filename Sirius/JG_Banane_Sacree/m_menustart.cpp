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
#include "m_pause.h"
#include "gameboard.h"

MenuStart::MenuStart(QWidget *parent) :
    QWidget(parent)
{
    maxTotalForms = 5;
    listButtonProfil = new QList<QPushButton*>();

    buttonNew = new QPushButton("Nouvelle partie");

    layoutMenu = new QVBoxLayout;

    getProfil();
    signalMapper = new QSignalMapper();
    totalForms = listButtonProfil->size();
    for(int i = 0; i < totalForms; i++)
    {
       layoutMenu->addWidget(listButtonProfil->at(i));
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
    Profil user;

    user.read(object[value].toObject());
    user.print();

    loadFile.close();

    emit startGame(0,1,2);

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
        Profil newProfil;
        newProfil.setUsername(username->text());

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
        newProfil.write(playerObject);
        newProfil.print();

        gameObject = object;
        gameObject[newProfil.getUsername()] = playerObject;

        QJsonDocument saveDoc(gameObject);
        saveFile.write(saveDoc.toJson());
        saveFile.close();
        loadFile.close();

        username->releaseKeyboard();

        validate->hide();
        username->hide();
        textPseudo->hide();

        emit startGame(1,2,3);

    }
}

