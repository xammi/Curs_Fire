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
    Point3d.cpp \
    Drawable.cpp

HEADERS  += UserInterface.h \
    includes.h \
    Scene.h \
    Drawable.h \
    Point3d.h

FORMS    += UserInterface.ui
