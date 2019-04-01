#include "src/mainwindow.h"
#include "src/map.h"
#include "src/renderarea.h"
#include "algorithms/astar/astar.h"
#include "algorithms/astar/node.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Map *map = new Map;
    map->setPixelRepresentation(1);
    map->setMap();

//    widget->resize(165, widget->height()); Utilizar para setar tamanho do mapa automaticamente sem precisar mudar mainwindow manualmente!

    AStar *astar = new AStar;
    Path *path = new Path;          // TODO: Criar "algorithmInit(&map)" para verificar e inicializar os algoritmos escolhidos
    Node *start = new Node;
    Node *end = new Node;

    *path = astar->findPath(start, end, map);

    switch(path->status)
    {
        case Path::FOUND : qDebug() << "FOUND"; break;
        case Path::UNPROCCESSED : qDebug() << "UNPROCESSED"; break;
        case Path::IMPOSSIBLE : qDebug() << "IMPOSSIBLE"; break;
    }

//Teste trajetoria A* - [OK]
    int i = 0;
    qDebug() << path->foundedPath.size();
    for(i = 0; i < path->foundedPath.size(); i++)
    {
        qDebug() << path->foundedPath[i]->cellptr.x << path->foundedPath[i]->cellptr.y;
    }

    MainWindow w(map, path);

    w.show();

    return a.exec();
}
//TODO : Criar destructors.
//TODO : Inserir RRT.
//TODO : Comparar os algoritmos.
