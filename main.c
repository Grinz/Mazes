#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//#include "excairo.c"
#include <maze.h>
#include <randomMouseSolving.h>

int main(int argc, char **argv)
{
    Cell cellValue;    
    cellValue.north = true;
    cellValue.south = true;
    cellValue.west = true;
    cellValue.est = true;
    cellValue.isVisited = false;
    
    int width;
    int height;
    
    printf("Entrez la longueur du labyrinthe :\n");
    scanf("%d", &width);
    printf("Entrez la hauteur du labyrinthe : \n");
    scanf("%d", &height);
    
    Maze *maze = mazeInit(width, height, cellValue);
    srand(time(NULL));    
    DeepFirstSearch(*maze);

	return 0;
}
