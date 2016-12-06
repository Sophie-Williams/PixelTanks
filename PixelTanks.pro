#-------------------------------------------------
#
# Project created by QtCreator 2016-11-13T07:28:58
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PixelTanks
TEMPLATE = app


SOURCES += main.cpp\
        game.cpp \
    strategy.cpp \
    tank.cpp \
    world.cpp \
    move.cpp \
    object.cpp \
    defaultstrategy.cpp \
    bullet.cpp \
    helper.cpp \
    attack.cpp \
    wall.cpp \
    playerstrategy.cpp \
    paintwidget.cpp \
    neuralnetwork.cpp \
    neuron.cpp \
    synapse.cpp

HEADERS  += game.h \
    strategy.h \
    tank.h \
    world.h \
    move.h \
    object.h \
    defaultstrategy.h \
    bullet.h \
    helper.h \
    attack.h \
    wall.h \
    playerstrategy.h \
    paintwidget.h \
    neuralnetwork.h \
    neuron.h \
    synapse.h

FORMS    += game.ui

CONFIG += c++11

QMAKE_CXXFLAGS+= -fopenmp
QMAKE_LFLAGS +=  -fopenmp
