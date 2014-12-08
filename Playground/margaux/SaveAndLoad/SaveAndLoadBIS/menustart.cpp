#include "menustart.h"
#include "game.h"

#include <QPushButton>
#include <QList>
#include <QVBoxLayout>
#include <QFile>
#include <qDebug>
#include <QByteArray>
#include <QJsonDocument>
#include <QSignalMapper>
#include <iterator>
#include <QLabel>
#include <QLineEdit>
#include <QHBoxLayout>

MenuStart::MenuStart(QWidget *parent) :
    QWidget(parent)
{
    listButtonProfil = new QList<QPushButton*>();
    buttonNew = new QPushButton("Nouvelle partie");

    layoutMenu = new QVBoxLayout;

    getProfil();
    signalMapper = new QSignalMapper();
    for(int i = 0; i < listButtonProfil->size(); i++)
    {
       layoutMenu->addWidget(listButtonProfil->at(i));
       QObject::connect(listButtonProfil->at(i), SIGNAL(clicked()), signalMapper, SLOT(map()));
       signalMapper->setMapping(listButtonProfil->at(i),listButtonProfil->at(i)->text());
    }

    validate = new QPushButton("Créer");

    QObject::connect(signalMapper, SIGNAL(mapped(QString)),this, SLOT(loadGame(QString)));
    QObject::connect(buttonNew,SIGNAL(clicked()),this,SLOT(newGameForm()));
    QObject::connect(validate,SIGNAL(clicked()),this,SLOT(newGame()));

    layoutMenu->addWidget(buttonNew);
    setLayout(layoutMenu);
}

bool MenuStart::getProfil()
{
    QFile loadFile("save.json");

    if (!loadFile.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open save file.");
        return false;
    }

    QByteArray saveData = loadFile.readAll();
    //qDebug() << saveData;

    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));
    QStringList listeProfil = loadDoc.object().keys();
    for (int i = 0; i < listeProfil.size(); i++)
    {
        listButtonProfil->append(new QPushButton(listeProfil.at(i)));
        //qDebug() << listeProfil.at(i) << endl;
    }
    return true;
}

void MenuStart::loadGame(QString value)
{
    qDebug() << "LOAD";

    QFile loadFile("save.json");

    if (!loadFile.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open save file.");
        return;
    }

    QByteArray saveData = loadFile.readAll();
    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));
    QJsonObject object = loadDoc.object();
    Profil user;

    user.read(object[value].toObject());
    user.print();

}

void MenuStart::newGameForm()
{
    username = new QLineEdit();
    QLabel* text = new QLabel("Surnom : ");

    QHBoxLayout* layoutNewGame = new QHBoxLayout;
    layoutNewGame->addWidget(text);
    layoutNewGame->addWidget(username);
    layoutNewGame->addWidget(validate);
    layoutMenu->addLayout(layoutNewGame);
}

void MenuStart::newGame()
{
    qDebug() << "NEW";
    Profil newProfil;
    newProfil.setUsername(username->text());

    // LIS LE FICHIER POUR GARDER LES DONNEES
    QFile loadFile("save.json");
    if (!loadFile.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open save file.");
        return;
    }

    QByteArray loadData = loadFile.readAll();
    QJsonDocument loadDoc(QJsonDocument::fromJson(loadData));
    QJsonObject object = loadDoc.object();

    // LIS LE FICHIER POUR ENREGISTRER
    QFile saveFile(QStringLiteral("save.json"));

    if (!saveFile.open(QIODevice::WriteOnly)) {
        qWarning("Couldn't open save file.");
    }

    QJsonObject gameObject;
    QJsonObject playerObject;
    newProfil.write(playerObject);
    newProfil.print();

    gameObject = object;
    gameObject[newProfil.getUsername()] = playerObject;

    QJsonDocument saveDoc(gameObject);
    saveFile.write(saveDoc.toJson());

}
