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
    Core/AbstractGrid.cpp \
    Core/AbstractSolver.cpp \
    Core/NS_Grid.cpp \
    Core/NS_Solver.cpp \
    Animetry/SmokeGrid.cpp \
    Animetry/FlameGrid.cpp \
    Animetry/Adjustable.cpp \
    Animetry/Fluid.cpp

HEADERS  += UserInterface.h \
    includes.h \
    Scene.h \
    Geometry/Drawable.h \
    Geometry/Obstacle.h \
    Geometry/Prims3d.h \
    Core/AbstractGrid.h \
    Core/AbstractSolver.h \
    Core/NS_Grid.h \
    Core/NS_Solver.h \
    Animetry/SmokeGrid.h \
    Animetry/FlameGrid.h \
    Task.h \
    Animetry/Adjustable.h \
    Animetry/Fluid.h

FORMS    += UserInterface.ui

RESOURCES += \
    adjusts.qrc
