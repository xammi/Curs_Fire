#-------------------------------------------------
#
# Project created by QtCreator 2014-06-27T19:38:33
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CG_2D_Engine
TEMPLATE = app
CONFIG += c++11


SOURCES += main.cpp\
        mainwindow.cpp \
    ns_solver.cpp

HEADERS  += mainwindow.h \
    ns_solver.h

FORMS    += mainwindow.ui
