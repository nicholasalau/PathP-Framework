#ifndef NODE_H
#define NODE_H

#include "src/constants.h"
#include "src/cell.h"
#include "src/map.h"

class Node
{
    public:
        //bool isBlocked;
        int neighborCount;
        int GCost = 0, HCost = 0, FCost = 0;
        Node *parent = nullptr;
        Node *neighbors[MAX_NEIGHBORS] = {};
        Map *map;
        Cell *cellptr = nullptr;
};


#endif // NODE_H
