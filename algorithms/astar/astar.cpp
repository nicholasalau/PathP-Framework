#include "algorithms/astar/astar.h"
#include "src/map.h"
#include <iostream>
#include <cstddef>


AStar::AStar()
{
    qDebug() << "AStar constructor.";
}

AStar::~AStar()
{
    qDebug() << "AStar destructor.";
    //delete start;
    //delete end;
}

void AStar::initAStar(Path *path, Node *start, Node *end, Map *map)
{
    //qDebug() << "[A*]Entrou A*.";

    //Inicializa listas
    openList.clear();   //Nodos a serem analisados
    closedList.clear(); //Nodos ja analisados
    path->foundedPath.clear();


    //qDebug() << "SDASADADDADASDASD" << map->end->x;
    //map->printMatrix();
    //qDebug() << map->end->x << " | " << map->end->y;

    //Inicializa o nó end
    end->cellptr = map->mapMatrix[map->end->x][map->end->y];
    end->FCost = end->GCost = 0;
    end->HCost = calculateHCost(end, end);
    end->parent = nullptr;



    qDebug() << "atribui end";

    //Inicializa o nó start
    start->cellptr = map->mapMatrix[map->begin->x][map->begin->y];
    start->FCost = start->GCost = 0;
    start->HCost = calculateHCost(start, end);
    start->parent = nullptr;
    qDebug() << "atribui end";


    //Inicializa path
    path->start = start;
    path->end = end;
    path->status = Path::UNPROCCESSED;
    qDebug() << "atribui end";


}

Path *AStar::findPath(Map *map)
{
    qDebug() << endl << "[Thread.findPath] Entrou.";

    Path *path = new Path; // TODO : usar new Path?

    Node *start = new Node;
    Node *end = new Node;

    int n = 0; //Debug

    initAStar(path,start, end, map);

    qDebug() << start->cellptr.x;
    qDebug() << start->cellptr.y;

    openList.push_back(start);

    while(path->status == Path::UNPROCCESSED)
    {
        qDebug() << "**********LOOP "<< n << "**********" << "(número iterações do while: " << n << ")";

        //Procura path
        if(openList.size() == 0)
        {
            qDebug() << "[DEBUG] openList vazia -> IMPOSSIBLE.";
            //Lista aberta vazia, logo nao temos caminho
            path->status = Path::IMPOSSIBLE;
            break;
        }
        //Ordena lista aberta pelo menor FCost
        std::sort(openList.begin(), openList.end(), [](Node *a, Node *b)
        {
            return a->FCost < b->FCost;
        });

        qDebug() << "[DEBUG]Teste reordenamento: ";
        //Ordenando a lista em ordem crescente, logo primeiro valor eh o com menor custo F
        Node *actual = new Node;
        actual = openList[0];
        qDebug() << "Infos sobre o primeiro nodo da lista a ser analisado:";
        qDebug() << "FCost:" << actual->FCost;
        qDebug() << "GCost:" << actual->GCost;
        qDebug() << "HCost:" << actual->HCost;
        qDebug() << "Posição:" << actual->cellptr.x << actual->cellptr.y;
        qDebug() << "Ocupado:" << actual->cellptr.isOccupied;

        Node *scnd = new Node(); //Debug
        if(openList[1]) //Debug
        { //Debug
            scnd = openList[1]; //Debug
            //qDebug() << "Coordenadas e custo F do SEGUNDO nodo da openList: X[" << scnd->cellptr.x << "]" << "Y[" << scnd->cellptr.y << "] Custo F = " << scnd->FCost; //Debug
        } //Debug

        if((actual->cellptr.x == end->cellptr.x) && (actual->cellptr.y == end->cellptr.y))
        {
            path->status = Path::FOUND;
            while(actual != start)
            {
                path->foundedPath.push_back(actual);
                actual = actual->parent;
            }
            path->foundedPath.push_back(actual);    //Inserir junto o start.
            break;
        }

        //Remove no(actual) com menor custo F da lista aberta
        openList.erase(openList.begin());
        //qDebug() << "[DEBUG]Verifica removeu openList: " << openList.size() << "Custo F do proximo nodo: " << openList[0]->FCost;

        //Add no actual na lista fechada
        closedList.push_back(actual);
        //  qDebug() << "[DEBUG]Verifica add closedList: " << closedList.size();

        //Definir os nós vizinhos
        defineNeighbors(actual, map);
        //qDebug() << "[DEBUG]Saiu defineNeigbors.";

        int f2 = 0; //Debug

        int i = 0;

        for(i = 0; i < actual->neighborCount; i++)
        {           
            qDebug() << "***************Percorrendo os vizinhos do nodo. Número de iterações: " << f2 << "***************";

            Node *neighbor = new Node();
            neighbor = actual->neighbors[i];

//            qDebug() << "Vizinho a ser analisado:" << i;
//            qDebug() << "x[" << neighbor->cellptr.x <<"]" <<"y["<<neighbor->cellptr.y << "]";
//            qDebug() << "isOccupied:" << neighbor->cellptr.isOccupied;
//            qDebug() << "FCost:" << neighbor->FCost;
//            qDebug() << "HCost:" << neighbor->HCost;
//            qDebug() << "\n";

            //Se o vizinho for bloqueado,
            //ou se o vizinho esta na lista fechada, ignora
            //comando : find -> parametros : (comeco,fim,procuro)
            qDebug() << "Verifica closedList ou se e bloqueado.";
            if((neighbor->cellptr.isOccupied == 1.00) || findNode(closedList, neighbor)) //Provavelmente esta verificacao de lista fechada nao precisa mais, ja foi feito no defineNeighbors
            {
                qDebug() << "É bloqueado ou está na lista fechada! Ignora vizinho!";
                qDebug() << "Proximo nodo \n";
                continue;
            }

            //Calcula custo de movimento do no atual em relacao ao vizinho
            int neighborCost = movementCost(actual, neighbor);
            //qDebug() << "Movement Cost = " << neighborCost;

            //Se vizinho do no atual ja estiver na lista aberta, verificar se o caminho pode ser encurtado se usarmos
            //o no atual como pai
            qDebug() << "Verifica se nodo ja se encontra na openList:";
            if(findNode(openList, neighbor))
            {
                qDebug() << "Nó já está na lista aberta!";
                int betterGCost = actual->GCost + neighborCost;

//                qDebug() << "novoGCost = " << betterGCost;
//                qDebug() << "antigoGCost = " << neighbor->GCost;
//                qDebug() << "parent antigo:" << neighbor->parent->cellptr.x << neighbor->parent->cellptr.y;
                if(betterGCost < neighbor->GCost)
                {
                    qDebug() << "Caminho pode ser encurtado! Atualiza pai,";
                    neighbor->parent = actual;
                    neighbor->GCost = betterGCost;
                    neighbor->FCost = neighbor->HCost + neighbor->GCost;
//                    qDebug() << "custo F: " <<  neighbor->FCost;
//                    qDebug() << "e custo G: " << neighbor->GCost;
//                    qDebug() << "novo parente:" << neighbor->parent->cellptr.x << neighbor->parent->cellptr.y;
                }
                else
                {
                    qDebug() << "Caminho nao encurtado!";
                }
            }
            else
            {
                qDebug() << "Nao estava na lista aberta. Define-se ele e o insere na openList";
                //Se o vizinho nao esta na lista aberta, insere ele
                //depois de calcular seus custos e apontar seu pai
                qDebug() << "--Definindo neighbor--";
                neighbor->parent = actual;
                neighbor->GCost = actual->GCost + neighborCost;
                neighbor->HCost = calculateHCost(neighbor, end);
                neighbor->FCost = neighbor->HCost + neighbor->GCost;
//                qDebug() << "FCost:" << neighbor->FCost;
//                qDebug() << "GCost:" << neighbor->GCost;
//                qDebug() << "HCost:" << neighbor->HCost;
//                qDebug() << "Posição:" << neighbor->cellptr.x << neighbor->cellptr.y;
//                qDebug() << "Ocupado:" << neighbor->cellptr.isOccupied;
//                qDebug() << "---------------------";

                openList.push_back(neighbor);
                qDebug() << "Inseriu na openList! openList size = " << openList.size();
            }
            f2++;
            qDebug() << "************************************************************************************************\n";
        }
        n++; //Debug while
//      delete actual;
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
    //h = absX + absY;

    return h*10;
}

void AStar::defineNeighbors(Node *actual, Map *map)
{

    qDebug() << "[defineNeighbors]Definindo os vizinhos.";
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
//    qDebug() << "[DefineNeighbors]Verificando limites vizinho:" << "initX:" << initX << "endX:" << endX << "initY" << initY << "endY" << endY;

    for(row = initY; row <= endY; row++)
    {
        for(col = initX; col <= endX; col++)
        {
            d++;
            //qDebug() << "[DEBUG]Entrou no FOR do defineNeighbors.";
            if((row == actual->cellptr.y) && (col == actual->cellptr.x)) //|| (findNode(closedList, actual) == 1))
            {
                //Caso nodo seja ele mesmo ou algum nodo já inserido na lista fechada, não inserí-lo novamente!
//                qDebug() << "[defineNeighbors]É o próprio nodo!" << actual->cellptr.x << actual->cellptr.y;
                continue;
            }
            else
            {
            //Definir neighbor
                Node *n = new Node();
                n->cellptr = map->mapMatrix[col][row];
                n->parent = nullptr;
                n->FCost = n->GCost = n->HCost = 0;
//                qDebug() << "[defineNeighbors]Verificando se este nodo ja existe na lista aberta:";
                if(findNode(openList, n))
                {
                    Node *temp = new Node();
                    temp = findNode(openList, n);
                    n = temp;
//                    qDebug() << "[defineNeighbors]Nodo ja existe (lista aberta)! Logo ja possui seus custos calculados abaixo:";
//                    qDebug() << "FCost:" << n->FCost;
//                    qDebug() << "GCost:" << n->GCost;
//                    qDebug() << "HCost:" << n->HCost;
//                    qDebug() << "Posição:" << n->cellptr.x << n->cellptr.y;
//                    qDebug() << "Ocupado:" << n->cellptr.isOccupied;
                } else if (findNode(closedList, n) || n->cellptr.isOccupied == 1.0)
                {
//                    qDebug() << "[defineNeighbors]Nodo está na lista fechada ou eh nodo ocupado, logo não inserí-lo.";
                    continue;
                }

                nc = actual->neighborCount; //Debug
//                qDebug() << "[defineNeighbors]Inserindo neighbor -> " << "X:" << n->cellptr.x << "Y:" << n->cellptr.y << "(" << actual->neighborCount << ")";
//                qDebug() << "FCost:" << n->FCost;
//                qDebug() << "GCost:" << n->GCost;
//                qDebug() << "HCost:" << n->HCost;
//                qDebug() << "Ocupado:" << n->cellptr.isOccupied;
                actual->neighbors.push_back(n);
//                qDebug() << "Testando se inseriu o vizinho ok -> " << "X:" << actual->neighbors[nc]->cellptr.x << "Y:" << actual->neighbors[nc]->cellptr.y;
//                qDebug() << "FCost:" << actual->neighbors[nc]->FCost;//n->FCost;
//                qDebug() << "Neighbors[" << nc << "]:" << actual->neighbors[nc]->cellptr.x << actual->neighbors[nc]->cellptr.y;
//                qDebug() << "\n";
                actual->neighborCount++;
            }
        }
    }
}


Node* AStar::findNode(std::vector<Node*> list, Node *nodeToFind)
{
    int i = 0;
    int size = list.size();
    //int found = 0;


//    qDebug() << "---FINDNODE---";
//    qDebug() << "[findNode]List size:" << size;
//    qDebug() << "--------------";
//    qDebug() << "Verificando nodo procurado chegou";
//    qDebug() << "Posição: " << nodeToFind->cellptr.x << nodeToFind->cellptr.y;
//    qDebug() << "--------------";

    for(i = 0; i<size; i++)
    {
//        qDebug() << "[findNode]Nodo procurado: X[" << nodeToFind->cellptr.x << "] Y[" << nodeToFind->cellptr.y << "]";
//        qDebug() << "[findNode]Nodo da lista: X[" << list[i]->cellptr.x << "] Y[" << list[i]->cellptr.y << "]" << "Custo F:" << list[i]->FCost;
        if(list[i]->cellptr.x == nodeToFind->cellptr.x && list[i]->cellptr.y == nodeToFind->cellptr.y)
        {
            //qDebug() << "[findNode]Achou nodo!";
            return list[i];
        }
    }
//    qDebug() << "[findNode]Nao achou nodo!";
//    qDebug() << "---------------\n";
    return NULL;
}
