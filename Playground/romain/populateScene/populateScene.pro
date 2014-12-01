#-------------------------------------------------
#
# Project created by QtCreator 2014-12-01T114:40
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = populateScene
TEMPLATE = app


SOURCES += main.cpp\
    player.cpp \
    gameboard.cpp \
    viewtransitionsurface.cpp \
    bloques.cpp \
    surfaces.cpp

HEADERS  += \
    player.h \
    gameboard.h \
    viewtransitionsurface.h \
    bloques.h \
    surfaces.h

RESOURCES += \
    images.qrc
