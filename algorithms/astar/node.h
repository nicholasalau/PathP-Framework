#ifndef NODE_H
#define NODE_H

#include "src/constants.h"
#include "src/cell.h"
#include "src/map.h"

class Node
{
    public:
        int neighborCount = 0;
        int GCost = 0, HCost = 0, FCost = 0;
        Node *parent = nullptr;
        Node *neighbors[MAX_NEIGHBORS] = {};
        Map *map;
        Cell cellptr;
        inline void addNeighbor(Node *n)
        {
            qDebug() << "[DEBUG]Funçao addNeighbor.";
            Node** ptr = neighbors + neighborCount;
            qDebug() << "[DEBUG]Vizinho: " << neighbors[neighborCount];
            neighborCount++;
            *ptr = n;

        }
};


#endif // NODE_H
