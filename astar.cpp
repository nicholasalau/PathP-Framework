#include "astar.h"

AStar::AStar()
{

}

void AStar::initAStar(Path *path, Node *start, Node *end)
{
    //Inicializa path
    path->start = start;
    path->end = end;
    path->status = Path::UNPROCCESSED;

    //Inicializa listas
    openList.clear(); //Nodos a serem analisados
    closedList.clear(); //Nodos ja analisados

    //Inicializa o no start
    start->FCost = start->GCost = 0;

    //start->HCost = calculateHCost(start, end);
    //TODO: Create calculateHCost function
    start->parent = nullptr;

}

Path AStar::findPath(Node *start, Node *end)
{
    Path path;

    initAStar(&path, start, end);

    openList.push_back(start);
    while(path.status == Path::UNPROCCESSED)
    {
        //Procura path
        if(openList.size() == 0)
        {
            //Acabou a lista, logo nao temos caminho
            path.status = Path::IMPOSSIBLE;
            break;
        }
        std::sort(openList.begin(), openList.end());
        Node* actual = openList[0]; //Ordenar a lista em ordem crescente, logo primeiro valor eh o menor
        /*Remove no(actual) com menor custo F da lista aberta
          Add na lista fechada
          Processar nos vizinhos actual
          Define no pai de cada vizinho
          Se vizinho do no atual ja estiver na lista aberta, verificar se o caminho pode ser encurtado se usarmos
          o no atual como pai
                    Se encurtar
                        Atualiza o pai do novo vizinho p atual
                        Atualiza custo o novo custo F*/
    }

    return path;
}



