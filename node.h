#ifndef NODE_H
#define NODE_H

#include "constants.h"
#include "cell.h"

class Node : public Cell
{
    public:
        //bool isBlocked;
        int neighborCount;
        int GCost = 0, HCost = 0, FCost = 0;
        Node *parent = nullptr;
        Node *neighbors[MAX_NEIGHBORS] = {};
};


#endif // NODE_H
