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
    usual/ns_solver.cpp \
    usual/ns_grid.cpp \
    integral/int_solver.cpp \
    asolver.cpp \
    integral/int_grid.cpp \
    agrid.cpp

HEADERS  += mainwindow.h \
    usual/ns_solver.h \
    usual/ns_grid.h \
    exception.h \
    integral/int_solver.h \
    asolver.h \
    integral/int_grid.h \
    agrid.h

FORMS    += mainwindow.ui
