void solveMazeRandomMouse(struct Maze maze)
{
    //TO DO : Infinite loop to solve
    
    int destination = maze.cells[maze.height-1][maze.width-1].number;
    printf("Destination : %d\n", destination);
    getchar();
    
    int currentLine = rand() % maze.height;
    int currentColumn = rand() % maze.width;
    printf("Current position : [%d][%d]\n", currentLine, currentColumn);
    getchar();
    int currentPosition = maze.cells[currentLine][currentColumn].number;
    printf("Current position number : %d\n", currentPosition);
    getchar();
    
    push(maze.cells[currentLine][currentColumn].number);
    printf("Element at top of the stack : %d\n", peek());
    getchar();
    
    for (int i=0;i<10;i++)
    {
        printf("Current position : [%d][%d]\n", currentLine, currentColumn);
        bool destinations[4];
            
        if (!maze.cells[currentLine][currentColumn].north)
            destinations[0] = true;
        else
            destinations[0] = false;
            
        if (!maze.cells[currentLine][currentColumn].est)
            destinations[1] = true;
        else
            destinations[1] = false;
        
        if (!maze.cells[currentLine][currentColumn].south)
            destinations[2] = true;
        else
            destinations[2] = false;
        
        if (!maze.cells[currentLine][currentColumn].west)
            destinations[3] = true;
        else
            destinations[3] = false;


        int randomSide = rand() % 4;            
        if (!destinations[randomSide])
        {
            if (destinations[0])
                randomSide = 0;
            else if (destinations[1])
                randomSide = 1;
            else if (destinations[2])
                randomSide = 2;
            else if (destinations[3])
                randomSide = 3;
        }
        
        if (randomSide == 0)
        {
            push(maze.cells[currentLine-1][currentColumn].number);
            currentPosition = maze.cells[currentLine-1][currentColumn].number;
            printf("Element at top of the stack : %d\n", peek());
            currentLine--;
        }
        else if (randomSide == 1)
        {
            push(maze.cells[currentLine][currentColumn+1].number);
            currentPosition = maze.cells[currentLine][currentColumn+1].number;
            printf("Element at top of the stack : %d\n", peek());
            currentColumn++;
        }
        else if (randomSide == 2)
        {
            push(maze.cells[currentLine+1][currentColumn].number);
            currentPosition = maze.cells[currentLine+1][currentColumn].number;
            printf("Element at top of the stack : %d\n", peek());
            currentLine++;
        }
        else if (randomSide == 3)
        {
            push(maze.cells[currentLine][currentColumn-1].number);
            currentPosition = maze.cells[currentLine][currentColumn-1].number;
            printf("Element at top of the stack : %d\n", peek());
            currentColumn--;
        }
        
        
        if (!(destinations[0] || destinations[1] || destinations[2] || destinations[3]))
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
                        currentPosition = maze.cells[currentLine][currentColumn].number;
                        break;
                    }
                }
            }
        }
    }
}