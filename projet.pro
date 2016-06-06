#-------------------------------------------------
#
# Project created by QtCreator 2016-05-21T19:12:11
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = projet
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    operande.cpp \
    litterale.cpp \
    litteraleentiere.cpp \
    litteralereelle.cpp \
    litteralerationnelle.cpp \
    litteralecomplexe.cpp \
    litteraleprogramme.cpp \
    operateur.cpp \
    pile.cpp \
    manager.cpp \
    litteraleexpression.cpp \
    litteralenumerique.cpp \
    computerexception.cpp

HEADERS  += mainwindow.h \
    operande.h \
    litterale.h \
    litteraleentiere.h \
    litteralereelle.h \
    litteralerationnelle.h \
    litteralecomplexe.h \
    litteraleprogramme.h \
    operateur.h \
    pile.h \
    manager.h \
    litteraleexpression.h \
    litteralenumerique.h \
    computerexception.h

FORMS    += mainwindow.ui
