#include "mainwindow.h"

#include <QPushButton>
#include <QFile>
#include <QDataStream>
#include <QMessageBox>
#include <QDebug>
#include <QByteArray>
#include <QGridLayout>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{
    QGridLayout* layout = new QGridLayout(this);

    buttonSave = new QPushButton();
    buttonSave->setText("Sauver");

    buttonLoad = new QPushButton();
    buttonLoad->setText("Charger");

    layout->addWidget(buttonSave,0,0);
    layout->addWidget(buttonLoad,0,1);

    QObject::connect(buttonSave, SIGNAL(clicked()), this, SLOT(save()));
    QObject::connect(buttonLoad, SIGNAL(clicked()), this, SLOT(load()));
}

MainWindow::~MainWindow()
{

}

void MainWindow::save()
{
    qDebug() << "SAVE";

    QFile file("save");
    file.open(QIODevice::WriteOnly);
    QTextStream out(&file);

    // Write a header with a "magic number" and a version
    /*out << (quint32)0xA0B0C0D0;
    out << (qint32)123;
    out.setVersion(QDataStream::Qt_4_0);*/

    // Write the data
    out << "Information";

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
    while ( !in.atEnd() ) {
        QString line = in.readLine();
        qDebug() << line;
    }
    file.close();
}
