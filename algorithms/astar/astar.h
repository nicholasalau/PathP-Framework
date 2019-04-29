#ifndef ASTAR_H
#define ASTAR_H

#include "src/constants.h"
#include "src/map.h"
#include "src/cell.h"
#include "node.h"
#include <vector>
#include <algorithm>

struct Path
{
    Node *start;
    Node *end;
    enum Status {UNPROCCESSED, FOUND, IMPOSSIBLE};
    Status status;
    std::vector<Node*> foundedPath;
};

class AStar
{
    public:
        AStar();
        ~AStar();
        void defineNeighbors(Node *actual, Map *map);
        int calculateHCost(Node *actual, Node *final);
        int movementCost(Node *actual, Node *neighbor);
        void initAStar(Path *path, Node *start, Node *end, Map *map);
        Path* findPath(Map *map);
        Node *findNode(std::vector<Node*> list, Node *nodeToFind);
        std::vector<Node*> openList; //Verificar alocaçao correta mem. - faz auto
        std::vector<Node*> closedList;
        //Node *start;
        //Node *end;
};

#endif // ASTAR_H
