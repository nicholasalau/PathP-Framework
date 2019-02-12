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
    //qDebug() << "[MAIN]Saiu set map.";
    AStar astar;
    Path path;          // TODO: Criar "algorithmInit(&map)" para inicializar os algoritmos escolhidos
    Node start;
    Node end;
    //qDebug() << "[MAIN]Vai chamar A*.";
    path = astar.findPath(&start, &end, &map);      // TODO : Verificar loop infinito while A*.
                                                    // TODO : Veirificar nodo na openList apos att o GCost passando por outro vizinho.
    switch(path.status)
    {
        case Path::FOUND : qDebug() << "FOUND"; break;
        case Path::UNPROCCESSED : qDebug() << "UNPROCESSED"; break;
        case Path::IMPOSSIBLE : qDebug() << "IMPOSSIBLE"; break;
    }
    MainWindow w(&map);  //TODO : Printar trajeto AStar.
    w.show();

    return a.exec();
}
//TODO : Inserir RRT.
//TODO : Printar trajetos.
//TODO : Verificar comparacoes a serem realizadas.
