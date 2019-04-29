#include "src/mainwindow.h"
#include "src/map.h"
#include "src/renderarea.h"
#include "algorithms/astar/astar.h"
#include "algorithms/astar/node.h"
#include <QApplication>

#include <pthread.h>
#include <thread>

Map *map = new Map();
Path *path = nullptr;// = new Path;

void *startPathsThread(void *ref)
{
    qDebug() << endl << "Entrou thread.";
    AStar *astar = (AStar*) ref;

    map->setPixelRepresentation(1);
    //map->setMap(); ->Dentro constructor do map

    //widget->resize(165, widget->height()); Utilizar para setar tamanho do mapa automaticamente sem precisar mudar mainwindow manualmente!

    //AStar *astar = new AStar;
    // TODO: Criar "algorithmInit(&map)" para verificar e inicializar os algoritmos escolhidos

    path = astar->findPath(map);

    ///***Teste trajetoria A* - [OK]***/
        int i = 0;
        qDebug() << path->foundedPath.size();
        for(i = 0; i < path->foundedPath.size(); i++)
        {
            qDebug() << path->foundedPath[i]->cellptr.x << path->foundedPath[i]->cellptr.y;
        }
    ///********************************/


    qDebug() << endl << "Acabou thread.";

    return NULL;

}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qDebug() << endl << "main";

//    Map *map = new Map;

//    map->setPixelRepresentation(1);
//    map->setMap();
//    switch(path->status)
//    {
//        case Path::FOUND : qDebug() << "FOUND"; break;
//        case Path::UNPROCCESSED : qDebug() << "UNPROCESSED"; break;
//        case Path::IMPOSSIBLE : qDebug() << "IMPOSSIBLE"; break;
//    }



    //std::thread t1(thread_paths);
    AStar *as = new AStar();

    pthread_t pathsThread;
    pthread_create(&(pathsThread),NULL,startPathsThread,(void*)as);
    pthread_join(pathsThread, 0);

    qDebug() << "Volta mainwindow.";

    MainWindow w(map, path);

    w.show();

    w.setThings(map, path);

    return a.exec();
}
//TODO : Inserir RRT.
//TODO : Comparar os tempos dos algoritmos.
