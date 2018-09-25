#ifndef MAP_H
#define MAP_H

#include "constants.h"
#include "cell.h"
#include <QTextStream>
#include <QFile>
#include <QString>
#include <QStringList>
#include <QDebug>
#include <vector>
#include <utility> //pair,make_pair,etc
#include <eigen3/Eigen/Dense> //Vector2f
#include <QtGlobal> //qInfo()

class Map
{
    public:
        Map();//int pr;
        void setMap();  //Set mapMatrix
        void readFile(); //Set QStringList coordinates
        void initMapMatrix();
        void printMatrix();
        void setPixelRepresentation(int pr);
        void defineCells(Cell *begin, Cell *end);
        QStringList coordinates;
        std::vector<std::pair<Eigen::Vector2f, Eigen::Vector2f> > obstacles;
        Cell mapMatrix[WORLD_HEIGHT][WORLD_WIDTH];
        int pixelRepresentation;   /*(i.e. 1 cell = 3x3 square pixel, instead of 1 cell = 1 pixel)*/
        //https://www.tutorialspoint.com/cplusplus/cpp_constructor_destructor.html
        Cell begin;
        Cell end;

    private:
        /*Ler arquivo*/
        const char * filename = "/home/phi/file/maps";
        QFile file;
        QTextStream stream;
        QString line;
};

#endif // MAP_H
