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
        //Node *neighbors[MAX_NEIGHBORS] = {};
        std::vector<Node*> neighbors;
        Map *map;
        Cell cellptr;
//        inline void addNeighbor(Node *n)
//        {
//            qDebug() << "[DEBUG]Funçao addNeighbor.";
//            qDebug() << "[DEBUG]Neighbor infos: " << n->cellptr.x << n->cellptr.y;
//            Node **ptr = neighbors + neighborCount;
//            //qDebug() << "[DEBUG]Vizinho: " << *neighbors[neighborCount];
//            neighborCount++;
//            *ptr = n;
//            neighbors.push_back(n);
//        }
};


#endif // NODE_H
