#include "astar.h"
#include "src/map.h"

AStar::AStar()
{

}

void AStar::initAStar(Path *path, Node *start, Node *end, Map *map)
{
    //Inicializa path
    path->start = start;
    path->end = end;
    path->status = Path::UNPROCCESSED;

    //Inicializa listas
    openList.clear();   //Nodos a serem analisados
    closedList.clear(); //Nodos ja analisados

    //Inicializa o nó end
    //end->cellptr = map->end;

    //Inicializa o nó start
    start->FCost = start->GCost = 0;
    start->HCost = calculateHCost(start, end);
    start->parent = nullptr;
    //start->cellptr = map->begin;

    //qDebug() << "end.x = " << end->cellptr.x;
    //qDebug() << "end.y = " << end->cellptr.y;

    qDebug() << "Map chegou:";
    //qDebug() << map->pixelRepresentation;


}

Path AStar::findPath(Node *start, Node *end, Map *map)
{
    Path path;

    int n = 0; //Debug

    initAStar(&path, start, end, map);

    openList.push_back(start);

    while(path.status == Path::UNPROCCESSED)
    {
        qDebug() << "**********LOOP "<< n << "**********" << "(número iterações do while: " << n << ")";

        //Procura path
        if(openList.size() == 0)
        {
            qDebug() << "[DEBUG] openList vazia -> IMPOSSIBLE.";
            //Lista aberta vazia, logo nao temos caminho
            path.status = Path::IMPOSSIBLE;
            break;
        }
        //Ordena lista aberta pelo menor FCost
        std::sort(openList.begin(), openList.end(), [](Node *a, Node *b)
        {
            return a->FCost < b->FCost;
        });

        qDebug() << "[DEBUG]Teste reordenamento: ";
        //Ordenando a lista em ordem crescente, logo primeiro valor eh o com menor custo F
        Node *actual = new Node();
        actual = openList[0];

        Node *scnd = new Node(); //Debug
        qDebug() << "Coordenadas do PRIMEIRO nodo da openList e seu custo F: X[" << actual->cellptr.x << "] Y[" << actual->cellptr.y << "] Custo F = " << actual->FCost; //Debug
        if(openList[1]) //Debug
        { //Debug
            scnd = openList[1]; //Debug
            qDebug() << "Coordenads e custo F do SEGUNDO nodo da openList: X[" << scnd->cellptr.x << "]" << "Y[" << scnd->cellptr.y << "] Custo F" << scnd->FCost; //Debug
        } //Debug

        if((actual->cellptr.x == end->cellptr.x) && (actual->cellptr.y == end->cellptr.y))
        {
            qDebug() << "[DEBUG]Entrou IF do FOUND.";
            path.status = Path::FOUND;
            break;
        }

        //Remove no(actual) com menor custo F da lista aberta
        openList.erase(openList.begin());
        qDebug() << "[DEBUG]Verifica removeu openList: " << openList.size();
        qDebug() << openList[0]->FCost;

        //Add no actual na lista fechada
        closedList.push_back(actual);
        qDebug() << "[DEBUG]Verifica add closedList: " << closedList.size();

        //Definir os nós vizinhos
        defineNeighbors(actual);
        qDebug() << "[DEBUG]Saiu defineNeigbors.";

        int f2 = 0; //Debug

        int i = 0;

        for(i = 0; i < actual->neighborCount; i++)
        {
            qDebug() << "[DEBUG]Percorrendo os vizinhos do nodo. Número de iterações:" << f2;

            Node *neighbor = new Node();
            neighbor = actual->neighbors[i];

            qDebug() << "Vizinho a ser analisado:" << i;
            qDebug() << "x[" << neighbor->cellptr.x <<"]" <<"y["<<neighbor->cellptr.y << "]";
            qDebug() << "isOccupied:" << neighbor->cellptr.isOccupied;
            qDebug() << "FCost:" << neighbor->FCost;

            //Se o vizinho for bloqueado,
            //ou se o vizinho esta na lista fechada, ignora
            //comando : find -> parametros : (comeco,fim,procuro)
            if((neighbor->cellptr.isOccupied == 1.00) || std::find(closedList.begin(), closedList.end(), neighbor) != closedList.end())
            {
                continue;
            }

            //Calcula custo de movimento do no atual em relacao ao vizinho
            int neighborCost = movementCost(actual, neighbor);
            qDebug() << "Movement Cost = " << neighborCost;

            //Se vizinho do no atual ja estiver na lista aberta, verificar se o caminho pode ser encurtado se usarmos
            //o no atual como pai
            if(std::find(openList.begin(), openList.end(), neighbor) != openList.end())
            {
                qDebug() << "Nó já está na lista aberta!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!.";
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
                qDebug() << "NAO estava na lista aberta. Define-se ele e o insere na openList";
                //Se o vizinho nao esta na lista aberta, insere ele
                //depois de calcular seus custos e apontar seu pai
                qDebug() << "--Definindo neighbor--";
                neighbor->parent = actual;
                neighbor->GCost = actual->GCost + neighborCost;
                neighbor->HCost = calculateHCost(neighbor, end);
                neighbor->FCost = neighbor->HCost + neighbor->GCost;
                qDebug() << "FCost:" << neighbor->FCost;
                qDebug() << "GCost:" << neighbor->GCost;
                qDebug() << "HCost:" << neighbor->HCost;
                openList.push_back(neighbor);         
            }
            f2++;
        }
        n++; //Debug while
    }
    return path;
}

int AStar::movementCost(Node *actual, Node *neighbor)
{
    int movementCost = 0;
    //Diagonal
    if(actual->cellptr.x != neighbor->cellptr.x && actual->cellptr.y != neighbor->cellptr.y)
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
    absX = abs(actual->cellptr.x - final->cellptr.x);
    absY = abs(actual->cellptr.y - final->cellptr.y);

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

void AStar::defineNeighbors(Node *actual)
{

    qDebug() << "[DEBUG]Definindo os vizinhos.";
    /*
     * Gerar 8 vizinhos do nó visitado (i, j)
     * N -> (i-1, j)
     * S -> (i+1, j)
     * L -> (i, j+1)
     * O -> (i, j-1)
     * NE -> (i-1. j+1)
     * NO -> (i-1, j-1)
     * SE -> (i+1, j+1)
     * SO -> (i+1, j-1)
     */
    int d = 0; //Debug.
    int nc = 0;

    int initX = 0, initY = 0, endX = 0, endY = 0, row = 0, col = 0;
    //Define variaveis para varrer todos vizinhos de um nodo
    initX = ((actual->cellptr.x - 1) < MIN_X) ? actual->cellptr.x : actual->cellptr.x - 1;
    endX = ((actual->cellptr.x + 1) > MAX_X) ? actual->cellptr.x : actual->cellptr.x + 1;
    initY = ((actual->cellptr.y - 1) < MIN_Y) ? actual->cellptr.y : actual->cellptr.y - 1;
    endY = ((actual->cellptr.y + 1) > MAX_Y) ? actual->cellptr.y : actual->cellptr.y + 1;
    qDebug() << "[DEBUG]Verificando limites vizinho:" << "initX:" << initX << "endX:" << endX << "initY" << initY << "endY" << endY;

    for(row = initY; row <= endY; row++)
    {
        for(col = initX; col <= endX; col++)
        {
            d++;
            //qDebug() << "[DEBUG]Entrou no FOR do defineNeighbors.";
            if((row == actual->cellptr.y) && (col == actual->cellptr.x))
            {
                continue;
            }
            else
            {
            //Definir neighbor
                Node *n = new Node();
                n->cellptr.x = col;
                n->cellptr.y = row;
                n->parent = nullptr;
                n->FCost = n->GCost = n->HCost = 0;
                nc = actual->neighborCount; //Debug
                qDebug() << "Inserindo neighbor -> " << "X:" << n->cellptr.x << "Y:" << n->cellptr.y << "(" << actual->neighborCount << ")";
                actual->neighbors.push_back(n);
                qDebug() << "Testando se inseriu o vizinho ok -> " << "X:" << actual->neighbors[nc]->cellptr.x << "Y:" << actual->neighbors[nc]->cellptr.y;
                qDebug() << "Neighbors[" << nc << "]:" << actual->neighbors[nc]->cellptr.x << actual->neighbors[nc]->cellptr.y;
                actual->neighborCount++;
            }
        }
    }
}
