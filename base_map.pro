#-------------------------------------------------
#
# Project created by QtCreator 2018-07-19T13:23:33
#
#-------------------------------------------------

QT       += core gui
CONFIG += console
QMAKE_CXXFLAGS += -std=c++0x

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = base_map
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    renderarea.cpp \
    map.cpp \
    astar.cpp

HEADERS  += mainwindow.h \
    renderarea.h \
    map.h \
    constants.h \
    astar.h \
    cell.h

FORMS    += mainwindow.ui
