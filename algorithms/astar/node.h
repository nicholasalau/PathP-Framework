#ifndef NODE_H
#define NODE_H

#include "constants.h"
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
        Cell *cellptr = mapMatrix[0][0];
};


#endif // NODE_H
