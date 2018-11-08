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
    map.setPixelRepresentation(1);
    map.setMap();        //TODO : Verificar final obstaculo na coordenada final de mapa.
    qDebug() << "Saiu setMap.";
    AStar astar;
    Path path;          // TODO: Criar "algorithmInit(&map)" para inicializar os algoritmos escolhidos
    Node start;
    Node end;
    path = astar.findPath(&start, &end, &map);  //TODO : Verificar chamando sempre vizinho igual no loop da leitura de vizinhos ja definidos.
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
