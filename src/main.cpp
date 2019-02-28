#include "src/mainwindow.h"
#include "src/map.h"
#include "src/renderarea.h"
#include "algorithms/astar/astar.h"
#include "algorithms/astar/node.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Map map;
    map.setPixelRepresentation(1);
    map.setMap();

    AStar astar;
    Path path;          // TODO: Criar "algorithmInit(&map)" para inicializar os algoritmos escolhidos
    Node start;
    Node end;

    path = astar.findPath(&start, &end, &map);

    switch(path.status)
    {
        case Path::FOUND : qDebug() << "FOUND"; break;
        case Path::UNPROCCESSED : qDebug() << "UNPROCESSED"; break;
        case Path::IMPOSSIBLE : qDebug() << "IMPOSSIBLE"; break;
    }
//    int i = 0;
//    for(i = 0; i <= path.foundedPath.size(); i++)
//    {
//        qDebug() << path.foundedPath[i]->cellptr.x << path.foundedPath[i]->cellptr.y;
//    }
    MainWindow w(&map);  //TODO : Printar trajeto AStar.
    w.show();

    return a.exec();
}

//TODO : Inserir RRT.
//TODO : Verificar comparacoes a serem realizadas.
