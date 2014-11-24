#-------------------------------------------------
#
# Project created by QtCreator 2014-10-06T19:15:32
#
# QGraphicsItem bouger avec les keys sur une map en
# background dans une scene
# Penser à changer l'adresse de l'image du background!
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = View2
TEMPLATE = app


SOURCES += main.cpp\
        dialog.cpp \
    mysquare.cpp

HEADERS  += dialog.h \
    mysquare.h

FORMS    += dialog.ui

OTHER_FILES +=

RESOURCES += \
    images.qrc

