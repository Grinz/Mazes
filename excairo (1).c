#include <math.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

//structure des cases du labyrinte
typedef struct _maze_cell {
	int wallAbove, wallLeft, cellValue, cellValueStart;
} MazeCell;

//structure du labyrinte
typedef struct _maze_t {
	/* maze size = m lines * n columns */
	int row, column;
	/* array of cells */
	MazeCell* *array;
} Maze;


// initialisation des case du labyrinte
MazeCell* initMazeCell() {
	MazeCell* cell = malloc(sizeof(MazeCell));
	cell->wallAbove = 1; //création du mur du haut
	cell->wallLeft = 1; //création du mur de gauche
	cell->cellValue = 0;
	cell->cellValueStart = 0;
	return cell;

}

//fonction pour obtenir une valeure aléatoire
int rand_a_b(int a, int b) {


	return rand() % (b - a) + a;

}

//creation du labyrinte(fusion aléatoire de chemin) et résolution(de trémaux)
Maze* initMaze(int m, int n)
{
	Maze* oMaze = malloc(sizeof(Maze));
	int nbCells = m * n;
	printf("%d \n", nbCells);
	oMaze->array = malloc(nbCells * sizeof(MazeCell));

	int counter = 1;
	int i;
	//affichage du tableau qui deviendra le labyrinte
	for (i = 0;i < m*n;i++)
	{
		if (i%m == 0)
		{
			printf("\n");
		}
		oMaze->array[i] = initMazeCell();
		oMaze->array[i]->cellValue = counter++;
		oMaze->array[i]->cellValueStart = counter;


		printf("%4d", oMaze->array[i]->cellValue);
	}

	printf("\n");
	//------------------------loop debut
	//Fusion des chemins
	int done = 0;
	while (done == 0)
	{
		done = 1;
		int sizeofTab = m * n;
		int nbAl = rand_a_b(0, sizeofTab);//choisit une case
		int wallChoosen = rand_a_b(1, 3);// choisit un mur



		if (wallChoosen == 1)
		{
			if (nbAl > n)
			{
				int b = nbAl - n;
				int oldValue = oMaze->array[b]->cellValue;
				int newValue = oMaze->array[nbAl]->cellValue;

				if (oldValue != newValue)
				{
					oMaze->array[nbAl]->wallAbove = 0;
					for (i = 0;i < m*n;i++)
					{
						if (oMaze->array[i]->cellValue == oldValue)
						{
							oMaze->array[i]->cellValue = newValue;
						}

					}
				}
			}
		}
		if (nbAl%m != 0)
		{
			if (wallChoosen == 2)
			{
				if (nbAl > 0)
				{
					int b = nbAl - 1;
					int oldValue = oMaze->array[b]->cellValue;
					int newValue = oMaze->array[nbAl]->cellValue;


					if (oldValue != newValue)
					{
						oMaze->array[nbAl]->wallLeft = 0;
						for (i = 0;i < m*n;i++)
						{
							if (oMaze->array[i]->cellValue == oldValue)
							{
								oMaze->array[i]->cellValue = newValue;
							}

						}

					}
				}
			}
		}
		int firstCellValue = 0;
		int z;
		for (z = 0;z < m*n;z++)
		{
			if (z == 0)//on récupère la valeure de la premiere case
			{
				firstCellValue = oMaze->array[z]->cellValue;
			}
			if (z != 0 && oMaze->array[z]->cellValue != oMaze->array[0]->cellValue)//si la valeur de toute les cases et la même  que celle de la première case, la résolution est fini
			{
				done = 0;
			}

		}
	}
	//--------------------------------loop end
	printf("\n The maze is done!!");
	int y;
	//j affiche le labyrinte: toute les valeurs sont identiques
	for (y = 0;y < m*n;y++)
	{
		if (y%m == 0)
		{
			printf("\n");
		}
		printf("%4d", oMaze->array[y]->cellValue);
	}
	printf("\n");
	//j affiche les murs du haut
	for (y = 0;y < m*n;y++)
	{
		if (y%m == 0)
		{
			printf("\n");
		}
		printf("%4d", oMaze->array[y]->wallAbove);
	}
	printf("\n");
	//j affiche les murs de gauche
	for (y = 0;y < m*n;y++)
	{
		if (y%m == 0)
		{
			printf("\n");
		}
		printf("%4d", oMaze->array[y]->wallLeft);
	}

    //je remet les valeurs de mon labyrinte maintenant créé à zero
	for (y = 0;y < m*n;y++)
	{
		oMaze->array[y]->cellValue = 0;
	}
	int exit = ((m*n) - 1);

    //From here, the resolution
	printf("\n\nFind the way out: Start!  ");
	printf("\nYour position: 0 ");

	int lastDir = 1;//Last direction:  1=left, 2=right, 3=up, 4=down
	int position = 0;
    //ici commence ma résolution, l entrée est la premiere case de oMaze(en haut à gauche) et la sortie la dernière(en bas à droite)
	while (position != exit)
	{
		printf("\nYour position is cell number: %d ", position);

		if (lastDir == 4) {

			//go right
			if (position + 1 <= exit && oMaze->array[position + 1]->wallLeft == 0 && oMaze->array[position + 1]->cellValue != 3)
			{
				int nextPosition = position + 1;
				if (nextPosition == exit)
				{
					position = exit;
					printf("\nYou went to the right and reached the exit");
					lastDir = 2;
				}
				else if (nextPosition + 1 <= exit && oMaze->array[nextPosition + 1]->wallLeft == 0 && oMaze->array[nextPosition + 1]->cellValue != 3)//r
				{
					position = nextPosition;
					printf("\nYou went to the right");
					lastDir = 2;
				}
				else if (nextPosition + n <= exit && oMaze->array[nextPosition + n]->wallAbove == 0 && oMaze->array[nextPosition + n]->cellValue != 3)//d
				{
					position = nextPosition;
					printf("\nYou went to the right");
					lastDir = 2;
				}
				else if (nextPosition - n >= 0 && oMaze->array[nextPosition]->wallAbove == 0 && oMaze->array[nextPosition - n]->cellValue != 3)//u
				{
					position = nextPosition;
					printf("\nYou went to the right");
					lastDir = 2;
				}
				else
				{
					oMaze->array[nextPosition]->cellValue = 3;
					printf("\nThe path to the right is a dead end...");
				}
			}
			//go down
			else if (position + n <= exit && oMaze->array[position + n]->wallAbove == 0 && oMaze->array[position + n]->cellValue != 3)
			{

				int nextPosition = position + n;
				if (nextPosition == exit)
				{
					position = exit;
					printf("\nYou went down and reached the exit");
					lastDir = 4;

				}
				else if (nextPosition + 1 <= exit && oMaze->array[nextPosition + 1]->wallLeft == 0 && oMaze->array[nextPosition + 1]->cellValue != 3)//r
				{
					position = nextPosition;
					printf("\nYou went down");
					lastDir = 4;
				}
				else if (nextPosition + n <= exit && oMaze->array[nextPosition + n]->wallAbove == 0 && oMaze->array[nextPosition + n]->cellValue != 3)//d
				{
					position = nextPosition;
					printf("\nYou went down");
					lastDir = 4;
				}
				else if (nextPosition - 1 >= 0 && oMaze->array[nextPosition]->wallLeft == 0 && oMaze->array[nextPosition - 1]->cellValue != 3)//l
				{
					position = nextPosition;
					printf("\nYou went down");
					lastDir = 4;
				}
				else
				{
					oMaze->array[nextPosition]->cellValue = 3;
					printf("\nThe path going down is a dead end...");
				}
			}
			//go left
			else if (position - 1 >= 0 && oMaze->array[position]->wallLeft == 0 && oMaze->array[position - 1]->cellValue != 3)
			{

				int nextPosition = position - 1;
				if (nextPosition - n >= 0 && oMaze->array[nextPosition]->wallAbove == 0 && oMaze->array[nextPosition - n]->cellValue != 3)//u
				{
					position = nextPosition;
					printf("\nYou went to the left");
					lastDir = 1;
				}
				else if (nextPosition + n <= exit && oMaze->array[nextPosition + n]->wallAbove == 0 && oMaze->array[nextPosition + n]->cellValue != 3)//d
				{
					position = nextPosition;
					printf("\nYou went to the left");
					lastDir = 1;
				}
				else if (nextPosition - 1 >= 0 && oMaze->array[nextPosition]->wallLeft == 0 && oMaze->array[nextPosition - 1]->cellValue != 3)//l
				{
					position = nextPosition;
					printf("\nYou went to the left");
					lastDir = 1;
				}
				else
				{
					oMaze->array[nextPosition]->cellValue = 3;
					printf("\nThe path going left is a dead end...");
				}
			}
			//go up
			else if (position - n >= 0 && oMaze->array[position]->wallAbove == 0 && oMaze->array[position - n]->cellValue != 3)
			{

				int nextPosition = position - n;
				if (nextPosition - n >= 0 && oMaze->array[nextPosition]->wallAbove == 0 && oMaze->array[nextPosition - n]->cellValue != 3)//u
				{
					position = nextPosition;
					printf("\nYou went up");
					lastDir = 3;
				}
				else if (nextPosition + 1 <= exit && oMaze->array[nextPosition + 1]->wallLeft == 0 && oMaze->array[nextPosition + 1]->cellValue != 3)//r
				{
					position = nextPosition;
					printf("\nYou went up");
					lastDir = 3;
				}
				else if (nextPosition - 1 >= 0 && oMaze->array[nextPosition]->wallLeft == 0 && oMaze->array[nextPosition - 1]->cellValue != 3)//l
				{
					position = nextPosition;
					printf("\nYou went up");
					lastDir = 3;
				}
				else
				{
					oMaze->array[nextPosition]->cellValue = 3;
					printf("\nThe path going up is a dead end...");
				}
			}
		}
		else if (lastDir == 2)
		{
			//go right
			if (position + 1 <= exit && oMaze->array[position + 1]->wallLeft == 0 && oMaze->array[position + 1]->cellValue != 3)
			{
				int nextPosition = position + 1;
				if (nextPosition == exit)
				{
					position = exit;
					printf("\nYou went to the right and reached the exit");
					lastDir = 2;
				}
				else if (nextPosition + 1 <= exit && oMaze->array[nextPosition + 1]->wallLeft == 0 && oMaze->array[nextPosition + 1]->cellValue != 3)//r
				{
					position = nextPosition;
					printf("\nYou went to the right");
					lastDir = 2;
				}
				else if (nextPosition + n <= exit && oMaze->array[nextPosition + n]->wallAbove == 0 && oMaze->array[nextPosition + n]->cellValue != 3)//d
				{
					position = nextPosition;
					printf("\nYou went to the right");
					lastDir = 2;
				}
				else if (nextPosition - n >= 0 && oMaze->array[nextPosition]->wallAbove == 0 && oMaze->array[nextPosition - n]->cellValue != 3)//u
				{
					position = nextPosition;
					printf("\nYou went to the right");
					lastDir = 2;
				}
				else
				{
					oMaze->array[nextPosition]->cellValue = 3;
					printf("\nThe path to the right is a dead end...");
				}
			}
			//go down
			else if (position + n <= exit && oMaze->array[position + n]->wallAbove == 0 && oMaze->array[position + n]->cellValue != 3)
			{

				int nextPosition = position + n;
				if (nextPosition == exit)
				{
					position = exit;
					printf("\nYou went down and reached the exit");
					lastDir = 4;

				}
				else if (nextPosition + 1 <= exit && oMaze->array[nextPosition + 1]->wallLeft == 0 && oMaze->array[nextPosition + 1]->cellValue != 3)//r
				{
					position = nextPosition;
					printf("\nYou went down");
					lastDir = 4;
				}
				else if (nextPosition + n <= exit && oMaze->array[nextPosition + n]->wallAbove == 0 && oMaze->array[nextPosition + n]->cellValue != 3)//d
				{
					position = nextPosition;
					printf("\nYou went down");
					lastDir = 4;
				}
				else if (nextPosition - 1 >= 0 && oMaze->array[nextPosition]->wallLeft == 0 && oMaze->array[nextPosition - 1]->cellValue != 3)//l
				{
					position = nextPosition;
					printf("\nYou went down");
					lastDir = 4;
				}
				else
				{
					oMaze->array[nextPosition]->cellValue = 3;
					printf("\nThe path going down is a dead end...");
				}
			}
			//go up
			else if (position - n >= 0 && oMaze->array[position]->wallAbove == 0 && oMaze->array[position - n]->cellValue != 3)
			{

				int nextPosition = position - n;
				if (nextPosition - n >= 0 && oMaze->array[nextPosition]->wallAbove == 0 && oMaze->array[nextPosition - n]->cellValue != 3)//u
				{
					position = nextPosition;
					printf("\nYou went up");
					lastDir = 3;
				}
				else if (nextPosition + 1 <= exit && oMaze->array[nextPosition + 1]->wallLeft == 0 && oMaze->array[nextPosition + 1]->cellValue != 3)//r
				{
					position = nextPosition;
					printf("\nYou went up");
					lastDir = 3;
				}
				else if (nextPosition - 1 >= 0 && oMaze->array[nextPosition]->wallLeft == 0 && oMaze->array[nextPosition - 1]->cellValue != 3)//l
				{
					position = nextPosition;
					printf("\nYou went up");
					lastDir = 3;
				}
				else
				{
					oMaze->array[nextPosition]->cellValue = 3;
					printf("\nThe path going up is a dead end...");
				}
			}
			//go left
			else if (position - 1 >= 0 && oMaze->array[position]->wallLeft == 0 && oMaze->array[position - 1]->cellValue != 3)
			{

				int nextPosition = position - 1;
				if (nextPosition - n >= 0 && oMaze->array[nextPosition]->wallAbove == 0 && oMaze->array[nextPosition - n]->cellValue != 3)//u
				{
					position = nextPosition;
					printf("\nYou went to the left");
					lastDir = 1;
				}
				else if (nextPosition + n <= exit && oMaze->array[nextPosition + n]->wallAbove == 0 && oMaze->array[nextPosition + n]->cellValue != 3)//d
				{
					position = nextPosition;
					printf("\nYou went to the left");
					lastDir = 1;
				}
				else if (nextPosition - 1 >= 0 && oMaze->array[nextPosition]->wallLeft == 0 && oMaze->array[nextPosition - 1]->cellValue != 3)//l
				{
					position = nextPosition;
					printf("\nYou went to the left");
					lastDir = 1;
				}
				else
				{
					oMaze->array[nextPosition]->cellValue = 3;
					printf("\nThe path going left is a dead end...");
				}
			}

		}
		else if (lastDir == 3)
		{
			//go right
			if (position + 1 <= exit && oMaze->array[position + 1]->wallLeft == 0 && oMaze->array[position + 1]->cellValue != 3)
			{
				int nextPosition = position + 1;
				if (nextPosition == exit)
				{
					position = exit;
					printf("\nYou went to the right and reached the exit");
					lastDir = 2;
				}
				else if (nextPosition + 1 <= exit && oMaze->array[nextPosition + 1]->wallLeft == 0 && oMaze->array[nextPosition + 1]->cellValue != 3)//r
				{
					position = nextPosition;
					printf("\nYou went to the right");
					lastDir = 2;
				}
				else if (nextPosition + n <= exit && oMaze->array[nextPosition + n]->wallAbove == 0 && oMaze->array[nextPosition + n]->cellValue != 3)//d
				{
					position = nextPosition;
					printf("\nYou went to the right");
					lastDir = 2;
				}
				else if (nextPosition - n >= 0 && oMaze->array[nextPosition]->wallAbove == 0 && oMaze->array[nextPosition - n]->cellValue != 3)//u
				{
					position = nextPosition;
					printf("\nYou went to the right");
					lastDir = 2;
				}
				else
				{
					oMaze->array[nextPosition]->cellValue = 3;
					printf("\nThe path to the right is a dead end...");
				}
			}
			//go up
			else if (position - n >= 0 && oMaze->array[position]->wallAbove == 0 && oMaze->array[position - n]->cellValue != 3)
			{

				int nextPosition = position - n;
				if (nextPosition - n >= 0 && oMaze->array[nextPosition]->wallAbove == 0 && oMaze->array[nextPosition - n]->cellValue != 3)//u
				{
					position = nextPosition;
					printf("\nYou went up");
					lastDir = 3;
				}
				else if (nextPosition + 1 <= exit && oMaze->array[nextPosition + 1]->wallLeft == 0 && oMaze->array[nextPosition + 1]->cellValue != 3)//r
				{
					position = nextPosition;
					printf("\nYou went up");
					lastDir = 3;
				}
				else if (nextPosition - 1 >= 0 && oMaze->array[nextPosition]->wallLeft == 0 && oMaze->array[nextPosition - 1]->cellValue != 3)//l
				{
					position = nextPosition;
					printf("\nYou went up");
					lastDir = 3;
				}
				else
				{
					oMaze->array[nextPosition]->cellValue = 3;
					printf("\nThe path going up is a dead end...");
				}
			}
			//go left
			else if (position - 1 >= 0 && oMaze->array[position]->wallLeft == 0 && oMaze->array[position - 1]->cellValue != 3)
			{

				int nextPosition = position - 1;
				if (nextPosition - n >= 0 && oMaze->array[nextPosition]->wallAbove == 0 && oMaze->array[nextPosition - n]->cellValue != 3)//u
				{
					position = nextPosition;
					printf("\nYou went to the left");
					lastDir = 1;
				}
				else if (nextPosition + n <= exit && oMaze->array[nextPosition + n]->wallAbove == 0 && oMaze->array[nextPosition + n]->cellValue != 3)//d
				{
					position = nextPosition;
					printf("\nYou went to the left");
					lastDir = 1;
				}
				else if (nextPosition - 1 >= 0 && oMaze->array[nextPosition]->wallLeft == 0 && oMaze->array[nextPosition - 1]->cellValue != 3)//l
				{
					position = nextPosition;
					printf("\nYou went to the left");
					lastDir = 1;
				}
				else
				{
					oMaze->array[nextPosition]->cellValue = 3;
					printf("\nThe path going left is a dead end...");
				}
			}
			//go down
			else if (position + n <= exit && oMaze->array[position + n]->wallAbove == 0 && oMaze->array[position + n]->cellValue != 3)
			{

				int nextPosition = position + n;
				if (nextPosition == exit)
				{
					position = exit;
					printf("\nYou went down and reached the exit");
					lastDir = 4;

				}
				else if (nextPosition + 1 <= exit && oMaze->array[nextPosition + 1]->wallLeft == 0 && oMaze->array[nextPosition + 1]->cellValue != 3)//r
				{
					position = nextPosition;
					printf("\nYou went down");
					lastDir = 4;
				}
				else if (nextPosition + n <= exit && oMaze->array[nextPosition + n]->wallAbove == 0 && oMaze->array[nextPosition + n]->cellValue != 3)//d
				{
					position = nextPosition;
					printf("\nYou went down");
					lastDir = 4;
				}
				else if (nextPosition - 1 >= 0 && oMaze->array[nextPosition]->wallLeft == 0 && oMaze->array[nextPosition - 1]->cellValue != 3)//l
				{
					position = nextPosition;
					printf("\nYou went down");
					lastDir = 4;
				}
				else
				{
					oMaze->array[nextPosition]->cellValue = 3;
					printf("\nThe path going down is a dead end...");
				}
			}

		}
		else if (lastDir == 1)
		{
			//go up
			if (position - n >= 0 && oMaze->array[position]->wallAbove == 0 && oMaze->array[position - n]->cellValue != 3)
			{

				int nextPosition = position - n;
				if (nextPosition - n >= 0 && oMaze->array[nextPosition]->wallAbove == 0 && oMaze->array[nextPosition - n]->cellValue != 3)//u
				{
					position = nextPosition;
					printf("\nYou went up");
					lastDir = 3;
				}
				else if (nextPosition + 1 <= exit && oMaze->array[nextPosition + 1]->wallLeft == 0 && oMaze->array[nextPosition + 1]->cellValue != 3)//r
				{
					position = nextPosition;
					printf("\nYou went up");
					lastDir = 3;
				}
				else if (nextPosition - 1 >= 0 && oMaze->array[nextPosition]->wallLeft == 0 && oMaze->array[nextPosition - 1]->cellValue != 3)//l
				{
					position = nextPosition;
					printf("\nYou went up");
					lastDir = 3;
				}
				else
				{
					oMaze->array[nextPosition]->cellValue = 3;
					printf("\nThe path going up is a dead end...");
				}
			}
			//go left
			else if (position - 1 >= 0 && oMaze->array[position]->wallLeft == 0 && oMaze->array[position - 1]->cellValue != 3)
			{

				int nextPosition = position - 1;
				if (nextPosition - n >= 0 && oMaze->array[nextPosition]->wallAbove == 0 && oMaze->array[nextPosition - n]->cellValue != 3)//u
				{
					position = nextPosition;
					printf("\nYou went to the left");
					lastDir = 1;
				}
				else if (nextPosition + n <= exit && oMaze->array[nextPosition + n]->wallAbove == 0 && oMaze->array[nextPosition + n]->cellValue != 3)//d
				{
					position = nextPosition;
					printf("\nYou went to the left");
					lastDir = 1;
				}
				else if (nextPosition - 1 >= 0 && oMaze->array[nextPosition]->wallLeft == 0 && oMaze->array[nextPosition - 1]->cellValue != 3)//l
				{
					position = nextPosition;
					printf("\nYou went to the left");
					lastDir = 1;
				}
				else
				{
					oMaze->array[nextPosition]->cellValue = 3;
					printf("\nThe path going left is a dead end...");
				}
			}
			//go down
			else if (position + n <= exit && oMaze->array[position + n]->wallAbove == 0 && oMaze->array[position + n]->cellValue != 3)
			{

				int nextPosition = position + n;
				if (nextPosition == exit)
				{
					position = exit;
					printf("\nYou went down and reached the exit");
					lastDir = 4;

				}
				else if (nextPosition + 1 <= exit && oMaze->array[nextPosition + 1]->wallLeft == 0 && oMaze->array[nextPosition + 1]->cellValue != 3)//r
				{
					position = nextPosition;
					printf("\nYou went down");
					lastDir = 4;
				}
				else if (nextPosition + n <= exit && oMaze->array[nextPosition + n]->wallAbove == 0 && oMaze->array[nextPosition + n]->cellValue != 3)//d
				{
					position = nextPosition;
					printf("\nYou went down");
					lastDir = 4;
				}
				else if (nextPosition - 1 >= 0 && oMaze->array[nextPosition]->wallLeft == 0 && oMaze->array[nextPosition - 1]->cellValue != 3)//l
				{
					position = nextPosition;
					printf("\nYou went down");
					lastDir = 4;
				}
				else
				{
					oMaze->array[nextPosition]->cellValue = 3;
					printf("\nThe path going down is a dead end...");
				}
			}
			//go right
			else if (position + 1 <= exit && oMaze->array[position + 1]->wallLeft == 0 && oMaze->array[position + 1]->cellValue != 3)
			{
				int nextPosition = position + 1;
				if (nextPosition == exit)
				{
					position = exit;
					printf("\nYou went to the right and reached the exit");
					lastDir = 2;
				}
				else if (nextPosition + 1 <= exit && oMaze->array[nextPosition + 1]->wallLeft == 0 && oMaze->array[nextPosition + 1]->cellValue != 3)//r
				{
					position = nextPosition;
					printf("\nYou went to the right");
					lastDir = 2;
				}
				else if (nextPosition + n <= exit && oMaze->array[nextPosition + n]->wallAbove == 0 && oMaze->array[nextPosition + n]->cellValue != 3)//d
				{
					position = nextPosition;
					printf("\nYou went to the right");
					lastDir = 2;
				}
				else if (nextPosition - n >= 0 && oMaze->array[nextPosition]->wallAbove == 0 && oMaze->array[nextPosition - n]->cellValue != 3)//u
				{
					position = nextPosition;
					printf("\nYou went to the right");
					lastDir = 2;
				}
				else
				{
					oMaze->array[nextPosition]->cellValue = 3;
					printf("\nThe path to the right is a dead end...");
				}
			}

		}
		counter++;
	}
	printf("\nyou have reached the exit, congratulations!!");


	return oMaze;
}

int main()
{
	srand(time(NULL));
	int n;
	int m;
	printf("Enter a number of column: ");
	scanf("%d", &n);
	printf("\nEnter a number of lines:");
	scanf("%d", &m);
	printf("\n");
	Maze* myMaze = initMaze(n, m);

	return 0;
}

