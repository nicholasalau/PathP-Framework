#include "algorithms/astar/node.h"

Node::Node()
{

}

Node::~Node()
{
    std::vector<Node*>().swap(neighbors);
    Node *parent = nullptr;
}
