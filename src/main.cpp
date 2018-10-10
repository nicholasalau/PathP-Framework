#include "mainwindow.h"
#include "map.h"
#include "renderarea.h"
#include "algorithms/astar/astar.h"
#include "algorithms/astar/node.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Map map;
    map.setPixelRepresentation(10);
    map.setMap();
    AStar astar;
    Path path;
    Node start;
    Node end;
    astar.initAStar(&path, &start, &end);

    MainWindow w(&map);
    w.show();

    return a.exec();
}
/*
 *-> Passar para main
 *    map = area->map;
 *    map->setMap();
 *   e passar como parâmetro para a mainwindow, pois o mapa independe de rodar a mainwindow [OK]
 *
 *-> Fazer cada célula 3x3, ou seja, aumentar a "escala" de cada pixel [OK]
 *
 *-> Incluir A* [75%]
*/
