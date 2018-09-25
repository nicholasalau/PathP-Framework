#ifndef CELL_H
#define CELL_H

class Cell
{
    public:
        double isOccupied;   /*
                               0 - Free
                               1 - Block
                             0.5 - No knowledge   */
        int x;
        int y; //Coordenadas x e y
};

#endif // CELL_H
