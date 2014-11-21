#include "mainwindow.h"

#include <QPushButton>
#include <QFile>
#include <QDataStream>
#include <QMessageBox>
#include <QDebug>
#include <QByteArray>
#include <QGridLayout>
#include <QTextStream>
#include <QDateTime>
#include <QSettings>

MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{
    QGridLayout* layout = new QGridLayout(this);

    buttonCreate = new QPushButton();
    buttonCreate->setText("Commencer de jouer");

    buttonLoad = new QPushButton();
    buttonLoad->setText("Charger une partie");

    buttonSave = new QPushButton();
    buttonSave->setText("Sauver la partie en cours");
    buttonSave->setDisabled(true);

    buttonExit = new QPushButton();
    buttonExit->setText("Quitter la partie");
    buttonExit->setDisabled(true);

    layout->addWidget(buttonCreate,0,0);
    layout->addWidget(buttonLoad,0,1);
    layout->addWidget(buttonSave,0,2);
    layout->addWidget(buttonExit,0,3);

    //QObject::connect(buttonSave, SIGNAL(clicked()), this, SLOT(save()));
    //QObject::connect(buttonLoad, SIGNAL(clicked()), this, SLOT(load()));

    QObject::connect(buttonCreate, SIGNAL(clicked()), this, SLOT(createIni()));
    QObject::connect(buttonSave, SIGNAL(clicked()), this, SLOT(saveIni()));
    QObject::connect(buttonLoad, SIGNAL(clicked()), this, SLOT(loadIni()));
    QObject::connect(buttonExit, SIGNAL(clicked()), this, SLOT(exit()));
}

MainWindow::~MainWindow()
{

}

void MainWindow::save()
{
    qDebug() << "SAVE";

    QFile file("save");
    file.open(QIODevice::ReadWrite);
    QTextStream out(&file);

    // Write a header with a "magic number" and a version
    /*out << (quint32)0xA0B0C0D0;
    out << (qint32)123;
    out.setVersion(QDataStream::Qt_4_0);*/

    // Write the data
    QString new_content = "";
    QDateTime current = QDateTime::currentDateTime();
    new_content.append("SaveTime=");
    new_content.append(current.toString("dd:MM:yyyy:hh:mm"));
    qDebug() << new_content;
    out << new_content;

    file.close();
}

void MainWindow::load()
{
    qDebug() << "LOAD";

    QFile file("save");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Not open";
        return;
    }

    QTextStream in(&file);
    while (!in.atEnd())
    {
        QString line = in.readLine();
        qDebug() << line;
    }
    file.close();
}

void MainWindow::loadIni()
{
    QSettings settings("save.ini", QSettings::IniFormat);

    // GRAB ONE VALUE
    //QString value = settings.value("SaveTime","00:00:0000:00:00").toString();

    // GRAB ALL VALUES
    settings.beginGroup(username);
    foreach (const QString &key, settings.childKeys()) {
        //groupString.append(QString("%1 : %2\n").arg(key, settings.value(key).toString()));
        qDebug() << key << ":\t" << settings.value(key).toString();
    }
    settings.endGroup();

    // NOT TESTED YET - GRAB ALL VALUES DIVIDED BY GROUPS
    /*QString allGroupsString;
    foreach (const QString &group, settings.childGroups())
    {
        QString groupString = QString("Groupe: %1").arg(group);

        settings.beginGroup(group);
        foreach (const QString &key, settings.childKeys()) {
            groupString.append(QString("%1 : %2\n").arg(key, settings.value(key).toString()));
        }
        settings.endGroup();

        groupString.append("\n\n");

        allGroupsString.append(groupString);
    }
    qDebug() << allGroupsString;*/
}

void MainWindow::saveIni()
{
    QSettings settings("save.ini", QSettings::IniFormat);
    QDateTime current = QDateTime::currentDateTime();

    settings.setValue("SaveTime",current.toString("dd:MM:yyyy:hh:mm"));
    settings.setValue("Level",level_number);
}

void MainWindow::createIni()
{
    QSettings settings("save.ini", QSettings::IniFormat);
    username = "Himi";
    settings.beginGroup(username);
    settings.setValue("Username",username);

    QDateTime current = QDateTime::currentDateTime();
    settings.setValue("StartTime",current.toString("dd:MM:yyyy:hh:mm"));
    settings.setValue("SaveTime",current.toString("dd:MM:yyyy:hh:mm"));

    level_number = 0;
    settings.setValue("Level",level_number);

    settings.endGroup();

    buttonSave->setDisabled(false);
    buttonCreate->setDisabled(true);
    buttonLoad->setDisabled(true);
    buttonExit->setDisabled(false);
}

void MainWindow::exit()
{
    buttonSave->setDisabled(true);
    buttonCreate->setDisabled(false);
    buttonLoad->setDisabled(false);
    buttonExit->setDisabled(true);
}
