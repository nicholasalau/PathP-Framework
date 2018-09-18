#include "astar.h"

AStar::AStar()
{

}

void AStar::initAStar(Path *path, Node *start, Node *end)
{
    //Inicializa path
    path->start = start;
    path->end = end;
    path->status = Path::UNPROCCESSED;

    //Inicializa listas
    openList.clear(); //Nodos a serem analisados
    closedList.clear(); //Nodos ja analisados

    //Inicializa o no start
    start->FCost = start->GCost = 0;
    start->HCost = calculateHCost(start, end);
    start->parent = nullptr;

}

Path AStar::findPath(Node *start, Node *end)
{
    Path path;

    initAStar(&path, start, end);

    openList.push_back(start);
    while(path.status == Path::UNPROCCESSED)
    {
        //Procura path
    }

    return path;
}



