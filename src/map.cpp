#include "map.h"
#include "cell.h"

//extern Map *map;

Map::Map()
{
    qDebug() << endl << "Map constructor.";
    //map = new Map();
    pixelRepresentation = 0;
    Cell **mapMatrix = new Cell*[WORLD_HEIGHT-1];
    for(int i = 0; i <= WORLD_HEIGHT; i++)
    {
        mapMatrix[i] = new Cell[WORLD_WIDTH-1];
    }
//https://stackoverflow.com/questions/16001803/pointer-to-pointer-dynamic-two-dimensional-array
//https://stackoverflow.com/questions/1403150/how-do-you-dynamically-allocate-a-matrix
    //mapMatrix[0][0].x = 1;

    initMapMatrix();
    setMap();
}

Map::~Map()
{
//    for (int i = 0; i < WORLD_HEIGHT; ++i)
//    {
//        delete [] mapMatrix[i];
//    }
//    delete [] mapMatrix;
}


void Map::setMap()
{
    int aux_pos_x1 = 0, aux_pos_y1 = 1;
    int aux_pos_x2 = 0, aux_pos_y2 = 0;
    int matrix_x = 0, matrix_y = 0;
    int diff_x = 0, diff_y = 0;
    int i = 0, j = 0;

    readFile();

    begin = new Cell();
    end = new Cell();

    defineCells(begin, end);

    //qDebug() << begin.x << "POS X INICIO";
    //qDebug() << begin.y << "POS Y INICIO";
    //qDebug() << end.x << "POS X FIM";
    //qDebug() << end.y << "POS Y FIM";
    //qDebug() << "Coordenadas chegou: "<<coordinates;
    int size = coordinates.size();
    int obj_count = size / 4;

    while(obj_count != 0)
    {
        aux_pos_x2 = aux_pos_x1 + 2; //+2 para apontar para a coordenada x do bottom right
        aux_pos_y2 = aux_pos_y1 + 2;
        diff_x = abs(coordinates.at(aux_pos_x1).toInt() - coordinates.at(aux_pos_x2).toInt());
        diff_y = abs(coordinates.at(aux_pos_y1).toInt() - coordinates.at(aux_pos_y2).toInt());
//        qDebug() << "DIFERENCA X = " << diff_x;
//        qDebug() << "DIFERENCA Y = " << diff_y;

        matrix_x = coordinates.at(aux_pos_x1).toInt();
        matrix_y = coordinates.at(aux_pos_y1).toInt();

        for(i = 0; i <= diff_y; i++)
        {
            for(j = 0; j <= diff_x; j++)
            {
                mapMatrix[matrix_x+j][matrix_y+i].isOccupied = 1.0;
                mapMatrix[matrix_x+j][matrix_y+i].x = matrix_x+j;
                mapMatrix[matrix_x+j][matrix_y+i].y = matrix_y+i;
                //qDebug() << "mapMatrix["<< matrix_x+j << "]" << "[" << matrix_y+i << "]";
            }
        }
        aux_pos_x1 = aux_pos_x1 + 4; //+4 para avancar para o proximo objeto na lista das coordenadas
        aux_pos_y1 = aux_pos_y1 + 4;
        obj_count--;
    }
    printMatrix();
    //qDebug() << "pixelRepresentation" << pixelRepresentation;
}

void Map::readFile()
{
    file.setFileName(filename);
    stream.setDevice(&file);

    if(!file.exists())
    {
        qDebug() << "Arquivo não existe "<<filename;
        return;
    }
    else
    {
        qDebug() << filename<<" -> Arquivo encontrado";
    }
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        qDebug() << "Nao abriu";

    while (!stream.atEnd())
    {
        QString line = stream.readLine();
        coordinates << line.split(',');
        qDebug() << "Linha: "<<line;
        qDebug() << "Coordenadas: "<<coordinates;
    }
}

void Map::initMapMatrix()
{
    int rows = WORLD_HEIGHT-1;
    int columns = WORLD_WIDTH-1;
    int i = 0;
    int j = 0;


    for (i = 0; i <= rows; i++)
    {
        for(j = 0; j <= columns; j++)
        {
            mapMatrix[j][i].isOccupied = 0.0;
            mapMatrix[j][i].x = j;
            mapMatrix[j][i].y = i;
        }
    }
}

void Map::printMatrix()
{
    int rows = WORLD_HEIGHT-1;
    int columns = WORLD_WIDTH-1;
    int i = 0;
    int j = 0;
    QDebug info = qInfo(); //Remover \n automatico que QDebug usa
    info << "\n ";

    for (i = 0; i <= rows; i++)
    {
        for(j = 0; j <= columns; j++)
        {
            info << mapMatrix[j][i].isOccupied;
        }
        info.noquote() << "\n ";
    }
}

void Map::setPixelRepresentation(int pr)
{
    pixelRepresentation = pr;
}

void Map::defineCells(Cell *begin, Cell *end)
{
    begin->x = START_POS_X;
    begin->y = START_POS_Y;
    end->x = END_POS_X;
    end->y = END_POS_Y;
}
