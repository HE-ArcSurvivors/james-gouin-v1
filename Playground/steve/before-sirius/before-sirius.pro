#-------------------------------------------------
#
# Project created by QtCreator 2014-11-19T19:01:08
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = before-sirius
TEMPLATE = app


SOURCES += main.cpp\
    player.cpp \
    gameboard.cpp \
    pingouin.cpp \
    neige.cpp \
    surface.cpp \
    blocdeplacable.cpp

HEADERS  += \
    player.h \
    gameboard.h \
    pingouin.h \
    neige.h \
    surface.h \
    blocdeplacable.h

RESOURCES += \
    images.qrc
