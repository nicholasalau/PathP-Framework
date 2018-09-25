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
    enum {UNPROCCESSED, FOUND, IMPOSSIBLE} status;
};

class AStar
{
    public:
        AStar();
        void addNeighbors(Node *n);
        int calculateHCost(Node *actual, Node *final);
        int movementCost(Node *actual, Node *neighbor);
        void initAStar(Path *path, Node *start, Node *end);
        Path findPath(Node *start, Node *end);

        std::vector<Node*> openList;
        std::vector<Node*> closedList;
        Map *map;

};

#endif // ASTAR_H
