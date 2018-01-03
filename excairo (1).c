/*
 installation:
   apt-get install libgtk-3-dev

 compilation:
   gcc -std=c99 excairo.c -o excairo `pkg-config --cflags gtk+-3.0 --libs gtk+-3.0`
*/


#include <math.h>
#include <time.h>
#include <unistd.h>
//#include <cairo.h>
//#include <gtk/gtk.h>
#include <stdlib.h>
#include <stdio.h>


typedef struct _maze_cell 
{
    int wallAbove, wallLeft, cellValue;
} MazeCell;

/* define maze structure */
typedef struct _maze_t 
{
    /* maze size = m lines * n columns */
    int row, column;
    /* array of cells */
    MazeCell* *array;
} Maze;

MazeCell* initMazeCell()
{
    MazeCell* cell = malloc(sizeof(MazeCell));
    cell->wallAbove = 1;
    cell->wallLeft = 1;
    cell->cellValue = 0;
    return cell;
}

int rand_a_b(int a, int b)
{
    return rand()%(b-a) +a;
}

Maze* initMaze(int m, int n)
{
    Maze* oMaze= malloc(sizeof(Maze));
    int nbCells=m*n;
    printf("%d \n", nbCells);
    oMaze->array = malloc(nbCells*sizeof(MazeCell));

    int counter=1;
    int i;
    
    for(i=0;i<m*n;i++)
    {
        if(i%m==0)
        {
            printf("\n");
        }
        
        oMaze->array[i]= initMazeCell();
        oMaze->array[i]->cellValue=counter++;
        printf("%4d", oMaze->array[i]->cellValue);
    }

    printf("\n");
    
    //------------------------loop debut
    int done=0;
	while(done==0)
	{
        done=1;
        int sizeofTab=m*n;
        int nbAl=rand_a_b( 0, sizeofTab);
        int wallChoosen=rand_a_b( 1, 3);
        
		if(wallChoosen==1)
        {
            if(nbAl>n)
            {
                int b=nbAl-n;
                int oldValue=oMaze->array[b]->cellValue;
                int newValue=oMaze->array[nbAl]->cellValue;

                if(oldValue!=newValue)
                {
                    oMaze->array[nbAl]->wallAbove=0;
                    for(i=0;i<m*n;i++)
                    {
                        if(oMaze->array[i]->cellValue==oldValue)
                        {
                            //printf("old: %d ",oMaze->array[i]->cellValue);
                            oMaze->array[i]->cellValue=newValue;
                            // printf("new: %d \n",oMaze->array[i]->cellValue);
                        }
                    }
                }
            }
		}
        
        if(nbAl%m!=0)
        {
            if(wallChoosen==2)
            {
                if(nbAl>0)
                {
                    int b=nbAl-1;
                    int oldValue=oMaze->array[b]->cellValue;
                    int newValue=oMaze->array[nbAl]->cellValue;

                    if(oldValue!=newValue)
                    {
                        oMaze->array[nbAl]->wallLeft=0;
                        
                        for(i=0;i<m*n;i++)
                        {
                            if(oMaze->array[i]->cellValue==oldValue)
                            {
                                //printf("old: %d ",oMaze->array[i]->cellValue);
                                oMaze->array[i]->cellValue=newValue;
                                //printf("new: %d \n",oMaze->array[i]->cellValue);
                            }
                        }
                    }
                }
            }
        }

        int firstCellValue=0;
        int z;
        
        for(z=0;z<m*n;z++)
        {
            if(z==0)
            {
                firstCellValue=oMaze->array[z]->cellValue;
            }
            if(z!=0 && oMaze->array[z]->cellValue!=oMaze->array[0]->cellValue)
            {
                done=0;
            }
        }
	}
	//--------------------------------loop end
    
	printf("\n The end!!");
	int y;
    
	for(y=0;y<m*n;y++)
    {
        if(y%m==0)
        {
            printf("\n");
        }
        printf("%4d", oMaze->array[y]->cellValue);
    }

    printf("\n");
    
    for(y=0;y<m*n;y++)
    {
        if(y%m==0)
        {
            printf("\n");
        }
        printf("%4d", oMaze->array[y]->wallAbove);
    }

    printf("\n");
    
    for(y=0;y<m*n;y++)
    {
        if(y%m==0)
        {
            printf("\n");
        }
        printf("%4d", oMaze->array[y]->wallLeft);
    }
    
    int StartPosition=0;
    int whileCounter=0;
    int position=0;
    int lastDir=0;

    //TO DO : Resolve infinite loop
    while(position!=((m*n)-1))
    {
        if(whileCounter==0)
        {
        for(y=0;y<m*n;y++)
        {
        oMaze->array[y]->cellValue=0;
        }

        printf("\nFind the way out: Start!  ");
        printf("\nYour position: %d ",position);
        oMaze->array[0]->cellValue=1;

        }
        whileCounter++;

        if(oMaze->array[position+1]->wallLeft==0&&oMaze->array[position+1]->cellValueStart<m*n&&oMaze->array[position+1]->cellValue!=3)
        {
            if(position==0 ||  position%m!=0)
            {
                oMaze->array[position]->cellValue=oMaze->array[position]->cellValue+1;
                position=position+1;
                printf("\nYou went to the right, Your position: %d ",position);
                lastDir=2;
            }
        }
        else if((position+n<=m*n)&&oMaze->array[position+n]->wallAbove==0&&oMaze->array[position+n]->cellValue!=3)
        {
            oMaze->array[position]->cellValue=oMaze->array[position]->cellValue+1;
            position=position+n;
            printf("\nYou went down, Your position: %d ",position);
            lastDir=3;
        }
        else if(position-n>=0&&oMaze->array[position]->wallAbove==0&&oMaze->array[position-n]->cellValue!=3)
        {
            oMaze->array[position]->cellValue=oMaze->array[position]->cellValue+1;
            position=position-n;
            printf("\nYou went up, Your position: %d ",position);
            lastDir=4;
        }
        else if((position-1>=0)&&oMaze->array[position]->wallLeft==0)
        {
            printf("\nThis is a dead-end, let s go back...");
            oMaze->array[position]->cellValue=3;
            position=position-1;
            printf("\nYou went to the left, Your position: %d ",position);
            lastDir=1;
        }
    }
    
    printf("you have reached the exit, congratulations!!");

    return oMaze;
}

int main()
{
    srand(time(NULL));
    int n;
    int m;
    printf("Enter a number of column: ");
    scanf("%d",&n);
    printf("\nEnter a number of lines:");
    scanf("%d",&m);
    printf("\n");
    Maze* myMaze=initMaze(n,m);
    return 0;
}
