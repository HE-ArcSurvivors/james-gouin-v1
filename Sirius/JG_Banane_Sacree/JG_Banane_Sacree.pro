#-------------------------------------------------
#
# Project created by QtCreator 2014-12-07T15:48:29
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = JG_Banane_Sacree
TEMPLATE = app


SOURCES += \
    block.cpp \
    player.cpp \
    surface.cpp \
    gameboard.cpp \
    main.cpp \
    b_movable.cpp \
    s_snow.cpp \
    s_viewtransition.cpp \
    b_wall.cpp \
    p_penguin.cpp

HEADERS  += \
    block.h \
    player.h \
    surface.h \
    gameboard.h \
    b_movable.h \
    b_wall.h \
    s_viewtransition.h \
    s_snow.h \
    p_penguin.h

RESOURCES += \
    images.qrc