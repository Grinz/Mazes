#include <stdio.h>
#include <stdbool.h>
#include <cell.h>
#include <stack.h>

typedef struct Maze {
    int width;
    int height;
    Cell **cells;
} Maze;

Maze *mazeInit(int width, int height, struct Cell cellValue) {
    Maze *maze = malloc(sizeof(Maze));
    Cell **cells = malloc(height * sizeof(Cell));
    
    for (int i=0;i<height;i++)
        cells[i] = malloc(width * sizeof(Cell));
        
    int cellNumber = 0;
    for (int i=0;i<height;i++)
        for (int j=0;j<width;j++)
        {
            cellValue.number = ++cellNumber;
            cells[i][j] = cellValue;
        }
        
    maze->width = width;
    maze->height = height;
    maze->cells = cells;
    
    return maze;
}

void drawMaze(struct Maze maze)
{
    for (int i=0;i<maze.height;i++)
    {
        for (int j=0;j<maze.width;j++)
        {
            if (!maze.cells[i][j].isVisited)
                printf("0");
            else
                printf("1");
        }
        printf("\n");
    }
    
    printf("\n");
    
    for (int i=0;i<maze.height;i++)
    {
        for (int j=0;j<maze.width;j++)
        {
            if (maze.cells[i][j].north)
                printf("####");
        }
        
        printf("\n");
        
        for (int j=0;j<maze.width;j++)
        {            
            if (maze.cells[i][j].west)
                printf("# ");
                
            if (maze.cells[i][j].est)
                printf(" #");
        }
        
        printf("\n");
        
        for (int j=0;j<maze.width;j++)
        {
            if (maze.cells[i][j].south)
                printf("####");
        }
        
        printf("\n");
    }
}

void DeepFirstSearch(struct Maze maze)
{
    int currentLine = rand() % maze.height;
    int currentColumn = rand() % maze.width;
    
    maze.cells[currentLine][currentColumn].isVisited = true;
    push(maze.cells[currentLine][currentColumn].number);
    printf("Element at top of the stack : %d\n", peek());
    
    int totalCells = (maze.height)*(maze.width);
    printf("Total cells : %d\n", totalCells);
    int visitedCells = 1;
    
    drawMaze(maze);
    getchar();
    
    while (visitedCells < totalCells)
    {
        printf("Current position : [%d][%d]\n", currentLine, currentColumn);
        bool neighbours[4];
    
        if (currentLine > 0)
        {
            if (!maze.cells[currentLine-1][currentColumn].isVisited)
                neighbours[0] = true;
            else
                neighbours[0] = false;
        }
        else
            neighbours[0] = false;
        
            
        if (currentColumn < maze.width-1)
        {
            if (!maze.cells[currentLine][currentColumn+1].isVisited)
                neighbours[1] = true;
            else
                neighbours[1] = false;
        }
        else
            neighbours[1] = false;
        
        if (currentLine < maze.height-1)
        {
            if (!maze.cells[currentLine+1][currentColumn].isVisited)
                neighbours[2] = true;
            else
                neighbours[2] = false;
        }
        else
            neighbours[2] = false;
        
        if (currentColumn > 0)
        {
            if (!maze.cells[currentLine][currentColumn-1].isVisited)
                neighbours[3] = true;
            else
                neighbours[3] = false;
        }
        else
            neighbours[3] = false;
        
        
        if (neighbours[0] || neighbours[1] || neighbours[2] || neighbours[3])
        {
            int randomSide = rand() % 4;
            
            if (!neighbours[randomSide])
            {
                if (neighbours[0])
                    randomSide = 0;
                else if (neighbours[1])
                    randomSide = 1;
                else if (neighbours[2])
                    randomSide = 2;
                else if (neighbours[3])
                    randomSide = 3;
            }
            
            if (randomSide == 0)
            {
                maze.cells[currentLine][currentColumn].north = false;
                maze.cells[currentLine-1][currentColumn].south = false;
                maze.cells[currentLine-1][currentColumn].isVisited = true;
                push(maze.cells[currentLine-1][currentColumn].number);
                currentLine--;
            }
            else if (randomSide == 1)
            {
                maze.cells[currentLine][currentColumn].est = false;
                maze.cells[currentLine][currentColumn+1].west = false;
                maze.cells[currentLine][currentColumn+1].isVisited = true;
                push(maze.cells[currentLine][currentColumn+1].number);
                currentColumn++;
            }
            else if (randomSide == 2)
            {
                maze.cells[currentLine][currentColumn].south = false;
                maze.cells[currentLine+1][currentColumn].north = false;
                maze.cells[currentLine+1][currentColumn].isVisited = true;
                push(maze.cells[currentLine+1][currentColumn].number);
                currentLine++;
            }
            else if (randomSide == 3)
            {
                maze.cells[currentLine][currentColumn].west = false;
                maze.cells[currentLine][currentColumn-1].est = false;
                maze.cells[currentLine][currentColumn-1].isVisited = true;
                push(maze.cells[currentLine][currentColumn-1].number);
                currentColumn--;
            }
            visitedCells++;
            
            printf("Element at top of the stack : %d\n", peek());
            printf("Visited cells : %d\n", visitedCells);
        }
        else
        {
            int value = pop();
            
            for (int i=0; i<maze.height; i++) 
            {
                for (int j=0;j<maze.width;j++)
                {
                    if (value == maze.cells[i][j].number)
                    {
                        currentLine = i;
                        currentColumn = j;
                        break;
                    }
                }
            }
        }
        
        drawMaze(maze);
        getchar();
    }
    
    while (!isEmpty()) 
    {
        pop();
    }
    
    printf("Stack empty: %s\n", isEmpty() ? "true":"false");
    solveMazeRandomMouse(maze);
}