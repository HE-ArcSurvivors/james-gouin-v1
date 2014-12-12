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
    player.cpp \
    surface.cpp \
    gameboard.cpp \
    main.cpp \
    b_movable.cpp \
    s_snow.cpp \
    s_viewtransition.cpp \
    b_wall.cpp \
    p_penguin.cpp \
    b_water.cpp \
    m_pause.cpp \
    s_ice.cpp

HEADERS  += \
    player.h \
    surface.h \
    gameboard.h \
    b_movable.h \
    b_wall.h \
    s_viewtransition.h \
    s_snow.h \
    p_penguin.h \
    b_water.h \
    m_pause.h \
    s_ice.h

RESOURCES += \
    images.qrc \
    ItemsPopulation.qrc
