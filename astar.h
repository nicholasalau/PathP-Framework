#ifndef ASTAR_H
#define ASTAR_H

#include "constants.h"
#include "map.h"
#include <vector>

struct Node
{
    bool isBlocked;
    int x, y; //Coordenadas do nodo
    int GCost = 0, HCost = 0, FCost = 0;
    Node *parent = nullptr;                 //Essas estruturas deveriam ir para a struct Cell?
    Node *neighbors[MAX_NEIGHBORS] = {};
};

struct Path
{
    Node *start;
    Node *end;
    enum {UNPROCCESSED, FOUND, IMPOSSIBLE} status;
};

class AStar
{
    public:
        AStar();
        void addNeighbors(Node *n);
        int calculateHCost(Node *actual, Node *final);
        void initAStar(Path *path, Node *start, Node *end);
        Path findPath(Node *start, Node *end);

        std::vector<Node*> openList;
        std::vector<Node*> closedList;
        Map *map;

};

#endif // ASTAR_H
