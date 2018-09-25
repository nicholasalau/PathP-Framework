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

    start->HCost = calculateHCost(&start, &end);
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
            //Lista aberta vazia, logo nao temos caminho
            path.status = Path::IMPOSSIBLE;
            break;
        }
        //Ordena lista aberta pelo menor FCost
        std::sort(openList.begin(), openList.end(), [](Node *a, Node *b)
        {
            return a->FCost < b->FCost;
        });

        //Ordenando a lista em ordem crescente, logo primeiro valor eh o com menor custo F
        Node *actual = openList[0];

        if(actual == end)
        {
            path.status = Path::FOUND;
            break;
        }

        //Remove no(actual) com menor custo F da lista aberta
        openList.erase(openList.begin());

        //Add no actual na lista fechada
        closedList.push_back(actual);

        //Processar nos vizinhos

        //TODO : Adicionar os nos vizinhos no vector de neighbors e atualizar neighborCount   [  ]
        //       e calcular o custo F, G e H de cada um e adiciona-los na openList            [OK]

        for(int i = 0; i < actual->neighborCount; i++)
        {
            Node *neighbor = actual->neighbors[i];
            //Se o vizinho for bloqueado,
            //ou se o vizinho esta na lista fechada, ignora
            //comando : find -> parametros : (comeco,fim,procuro)
            if((neighbor->isOccupied == 1.00) || std::find(closedList.begin(), closedList.end(), neighbor) != closedList.end())
            {
                continue;
            }

            //Calcula custo de movimento do no atual em relacao ao vizinho
            int neighborCost = movementCost(actual, neighbor);

            //Se vizinho do no atual ja estiver na lista aberta, verificar se o caminho pode ser encurtado se usarmos
            //o no atual como pai
            if(std::find(openList.begin(), openList.end(), neighbor) != openList.end())
            {
                int betterGCost = actual->GCost + neighborCost;

                if(betterGCost < neighbor->GCost)
                {
                    neighbor->parent = actual;
                    neighbor->GCost = betterGCost;
                    neighbor->FCost = neighbor->HCost + neighbor->GCost;
                }

            }
            else
            {
                //Se o vizinho nao esta na lista aberta, insere ele
                //depois de calcular seus custos e apontar seu pai
                neighbor->parent = actual;
                neighbor->GCost = actual->GCost + neighborCost;
                neighbor->HCost = calculateHCost(neighbor, end);
                neighbor->FCost = neighbor->HCost + neighbor->GCost;
                openList.push_back(neighbor);

            }
        }
    }

    return path;
}

//TODO: Ajeitar .x de cada nodo
int AStar::movementCost(Node *actual, Node *neighbor)
{
    int movementCost = 0;
    //Diagonal
    if(actual->x != neighbor->x && actual->y != neighbor->y)
    {
        movementCost = 14;
        return movementCost;
    }
    //Horizontal
    else
    {
        movementCost = 10;
        return movementCost;
    }
}

int AStar::calculateHCost(Node *actual, Node *final)
{
    int absX = 0;
    int absY = 0;
    int h = 0;
    absX = abs(actual->x - final->x);
    absY = abs(actual->y - final->y);

    //Distancia de Manhattan considerando diagonais
    if (absX > absY)
    {
        h = 14 * absY + 10 * (absX - absY);
    }
    else
    {
        h = 14 * absX + 10 * (absY - absX);
    }

    return h;
}






