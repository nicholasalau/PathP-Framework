#-------------------------------------------------
#
# Project created by QtCreator 2018-07-19T13:23:33
#
#-------------------------------------------------

QT       += core gui
CONFIG += console
QMAKE_CXXFLAGS += -std=c++0x

greaterThan(QT_MAJOR_VERSION, 4)
{
    QT += widgets
}
TARGET = base_map
TEMPLATE = app


SOURCES += src/main.cpp\
        src/mainwindow.cpp \
    src/renderarea.cpp \
    src/map.cpp \
    algorithms/astar/astar.cpp \
    algorithms/astar/node.cpp \
    src/cell.cpp

HEADERS  += src/mainwindow.h \
    src/renderarea.h \
    src/map.h \
    src/constants.h \
    algorithms/astar/astar.h \
    src/cell.h \
    algorithms/astar/node.h

FORMS    += src/mainwindow.ui
