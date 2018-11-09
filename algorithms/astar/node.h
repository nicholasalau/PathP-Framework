#ifndef NODE_H
#define NODE_H

#include "src/constants.h"
#include "src/cell.h"
#include "src/map.h"
#include <vector>


class Node
{
    public:
        int neighborCount = 0;
        int GCost = 0, HCost = 0, FCost = 0;
        Node *parent = nullptr;
        std::vector<Node*> neighbors;
        Map *map;
        Cell cellptr;
};


#endif // NODE_H
