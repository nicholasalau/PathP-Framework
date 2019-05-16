#ifndef RRT_H
#define RRT_H

#include <vector>
#include <math.h>
#include <eigen3/Eigen/Dense>

using namespace Eigen;

struct Node {
    Node *parent;
    Vector2f position;
    std::vector<Node *>children;
}; //TODO : Criar proprio node ou tentar reutilizar A*?


class rrt
{

    public:
        rrt();
        Node *root;
        Node *lastNode;
        int max_iter;
        int step_size;
        std::vector<Node *> nodes;
        std::vector<Node *> path;
        void init_arvore(); //Qini = raíz da árvore
        Node *setRandomNode(); //Qale <- Estado aleatório (loop até fim)
        bool findDest(); //Verifica se achou destino
        int distance(Vector2f &p, Vector2f &q);
        Node *closest(Vector2f pos); //Acha Qpai
        Vector2f newConfig(Node *q, Node *qClosest);
        void add(Node *qClosest, Node *qNew);
        void setStepSize(int stepS);
        void setMaxIter(int maxI);
        void deleteNodes(Node *root);
        void printPath(Node *lastNode,rrt *RRT);
};

#endif // RRT_H
