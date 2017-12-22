void solveMazePledge(struct Maze maze)
{
    int destination = maze.cells[maze.height-1][maze.width-1].number;    
    int currentLine = rand() % maze.height;
    int currentColumn = rand() % maze.width;

    printf("Destination : %d\n", destination);

    int currentPosition = maze.cells[currentLine][currentColumn].number;    
    push(maze.cells[currentLine][currentColumn].number);
    printf("Element at top of the stack : %d\n", peek());
    
    int nextDirection = 0;
    
    while (destination != currentPosition)
    {
        printf("Current position : [%d][%d]\n", currentLine, currentColumn);
        printf("Current position number : %d\n", currentPosition);
        
        if (nextDirection == 0)
        {
            printf("nextDirection == 0\n");
            if (maze.cells[currentLine][currentColumn].north)
            {
                if (!maze.cells[currentLine][currentColumn].est)
                    nextDirection = 1;
                else if (!maze.cells[currentLine][currentColumn].west)
                    nextDirection = 3;
                else if (maze.cells[currentLine][currentColumn].est || maze.cells[currentLine][currentColumn].west)
                    nextDirection = 2;
            }
            else
                nextDirection = 0;
                
            printf("Next direction : %d", nextDirection);
        }
        else if (nextDirection == 1)
        {
            printf("nextDirection == 1\n");
            if (maze.cells[currentLine][currentColumn].est)
            {
                if (!maze.cells[currentLine][currentColumn].north)
                    nextDirection = 0;
                else if (!maze.cells[currentLine][currentColumn].south)
                    nextDirection = 2;
                else if (maze.cells[currentLine][currentColumn].north && maze.cells[currentLine][currentColumn].south)
                    nextDirection = 3;
            }
            else
                nextDirection = 1;
                
            printf("Next direction : %d", nextDirection);
        }
        else if (nextDirection == 2)
        {
            printf("nextDirection == 2\n");
            if (maze.cells[currentLine][currentColumn].south)
            {
                if (!maze.cells[currentLine][currentColumn].est)
                    nextDirection = 1;
                else if (!maze.cells[currentLine][currentColumn].west)
                    nextDirection = 3;
                else if (maze.cells[currentLine][currentColumn].est && maze.cells[currentLine][currentColumn].west)
                    nextDirection = 0;
            }
            else
                nextDirection = 2;
                
            printf("Next direction : %d", nextDirection);
        }
        else if (nextDirection == 3)
        {
            printf("nextDirection == 3\n");
            if (maze.cells[currentLine][currentColumn].west)
            {
                if (!maze.cells[currentLine][currentColumn].north)
                    nextDirection = 0;
                else if (!maze.cells[currentLine][currentColumn].south)
                    nextDirection = 2;
                else if (maze.cells[currentLine][currentColumn].north && maze.cells[currentLine][currentColumn].south)
                    nextDirection = 1;
            }
            else
                nextDirection = 3;
                
            printf("Next direction : %d", nextDirection);
        }
        
        
        if (nextDirection == 0)
        {
            push(maze.cells[currentLine-1][currentColumn].number);
            currentPosition = maze.cells[currentLine-1][currentColumn].number;
            printf("Element at top of the stack : %d\n", peek());
            currentLine--;
        }
        else if (nextDirection == 1)
        {
            push(maze.cells[currentLine][currentColumn+1].number);
            currentPosition = maze.cells[currentLine][currentColumn+1].number;
            printf("Element at top of the stack : %d\n", peek());
            currentColumn++;
        }
        else if (nextDirection == 2)
        {
            push(maze.cells[currentLine+1][currentColumn].number);
            currentPosition = maze.cells[currentLine+1][currentColumn].number;
            printf("Element at top of the stack : %d\n", peek());
            currentLine++;
        }
        else if (nextDirection == 3)
        {
            push(maze.cells[currentLine][currentColumn-1].number);
            currentPosition = maze.cells[currentLine][currentColumn-1].number;
            printf("Element at top of the stack : %d\n", peek());
            currentColumn--;
        }
        
        getchar();
    }
    
    printf("Reached !\n");
}
