void solveMazePledge(struct Maze maze)
{
    int destination = maze.cells[maze.height-1][maze.width-1].number;    
    int currentLine = rand() % maze.height;
    int currentColumn = rand() % maze.width;

    int currentPosition = maze.cells[currentLine][currentColumn].number;    
    push(maze.cells[currentLine][currentColumn].number);
    
    while (currentPosition != destination)
    {
        printf("Current position : [%d][%d]\n", currentLine, currentColumn);
        int counter = 1;
        printf("Counter : %d\n", counter);
        
        while (counter != 0)
        {
            printf("Counter : %d\n", counter);
            
            if (!maze.cells[currentLine][currentColumn].north)
            {
                push(maze.cells[currentLine-1][currentColumn].number);
                currentPosition = maze.cells[currentLine-1][currentColumn].number;
                printf("Element at top of the stack : %d\n", peek());
                currentLine--;
            }
            else
            {
                if (!maze.cells[currentLine][currentColumn].est)
                {
                    push(maze.cells[currentLine][currentColumn+1].number);
                    currentPosition = maze.cells[currentLine][currentColumn+1].number;
                    printf("Element at top of the stack : %d\n", peek());
                    currentColumn++;
                    
                    counter += 89;
                    printf("Counter : %d\n", counter);
                }
                else
                {
                    if (!maze.cells[currentLine][currentColumn].west)
                    {
                        push(maze.cells[currentLine][currentColumn-1].number);
                        currentPosition = maze.cells[currentLine][currentColumn-1].number;
                        printf("Element at top of the stack : %d\n", peek());
                        currentColumn--;
                        
                        counter -= 91;
                        printf("Counter : %d\n", counter);
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
                }
            }
        }
    }
}
