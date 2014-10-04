#-------------------------------------------------
#
# Project created by QtCreator 2014-06-18T20:08:26
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CG_Curs_Fire
TEMPLATE = app
CONFIG += c++11

SOURCES += main.cpp\
        UserInterface.cpp \
    Scene.cpp \
    Geometry/Drawable.cpp \
    Geometry/Obstacle.cpp \
    Geometry/Prims3d.cpp \
    Animetry/AbstractGrid.cpp \
    Animetry/AbstractSolver.cpp \
    Animetry/NS_Grid.cpp \
    Animetry/NS_Solver.cpp \
    Animetry/Flame.cpp \
    Animetry/Smoke.cpp

HEADERS  += UserInterface.h \
    includes.h \
    Scene.h \
    Geometry/Drawable.h \
    Geometry/Obstacle.h \
    Geometry/Prims3d.h \
    Animetry/AbstractGrid.h \
    Animetry/AbstractSolver.h \
    Animetry/NS_Grid.h \
    Animetry/NS_Solver.h \
    Animetry/Flame.h \
    Animetry/Smoke.h

FORMS    += UserInterface.ui
