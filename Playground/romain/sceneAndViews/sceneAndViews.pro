#-------------------------------------------------
#
# Project created by QtCreator 2014-11-19T19:01:08
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = sceneAndViews
TEMPLATE = app


SOURCES += main.cpp\
    player.cpp \
    gameboard.cpp \
    viewtransitionsurface.cpp

HEADERS  += \
    player.h \
    gameboard.h \
    viewtransitionsurface.h

RESOURCES += \
    images.qrc
