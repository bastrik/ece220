#include <stdio.h>
#include <stdlib.h>
#include "maze.h"


/*
 * createMaze -- Creates and fills a maze structure from the given file
 * INPUTS:       fileName - character array containing the name of the maze file
 * OUTPUTS:      None 
 * RETURN:       A filled maze structure that represents the contents of the input file
 * SIDE EFFECTS: None
 */
maze_t * createMaze(char * fileName)
{
    maze_t * newMaze = malloc(sizeof(maze_t));

    FILE * file;
	int i, j, width, height;
	char c;
	file = fopen(fileName, "r");
    fscanf(file, "%d", &width);
    fscanf(file, "%d", &height);
    fgetc(file);

    newMaze->width = width;
    newMaze->height = height;

    newMaze->cells = (char **)malloc(sizeof(char *) * height);
    for(i = 0; i < height; i++)
    	newMaze->cells[i] = (char *)malloc(sizeof(char) * width);

    i = 0;
    j = 0;
    while ((c = fgetc(file)) != EOF)
    {
    	if (c == '\n')
    	{
    		i++;
    		j = 0;
    	}
    	else
    	{
    		newMaze->cells[i][j] = c;
    		j++;
    		if (c == 'S')
    		{
    			newMaze->startColumn = j;
    			newMaze->startRow = i;
    		}
    		if (c == 'E')
    		{
    			newMaze->endColumn = j;
    			newMaze->endRow = i;
    		}
    	}
    }
    fclose(file);
    return newMaze;
}

/*
 * destroyMaze -- Frees all memory associated with the maze structure, including the structure itself
 * INPUTS:        maze -- pointer to maze structure that contains all necessary information 
 * OUTPUTS:       None
 * RETURN:        None
 * SIDE EFFECTS:  All memory that has been allocated for the maze is freed
 */
void destroyMaze(maze_t * maze)
{
    int i;
    for (i = 0; i < maze->height; i++)
    	free(maze->cells[i]);
    free(maze->cells);
    free(maze);
}

/*
 * printMaze --  Prints out the maze in a human readable format (should look like examples)
 * INPUTS:       maze -- pointer to maze structure that contains all necessary information 
 *               width -- width of the maze
 *               height -- height of the maze
 * OUTPUTS:      None
 * RETURN:       None
 * SIDE EFFECTS: Prints the maze to the console
 */
void printMaze(maze_t * maze)
{
    int r, c;
    for (r = 0; r < maze->height; r++)
    {
    	for (c = 0; c < maze->width; c++)
    	{
    		printf("%c", maze->cells[r][c]);
    	}
    	printf("\n");
    }
}

/*
 * solveMazeManhattanDFS -- recursively solves the maze using depth first search,
 * INPUTS:               maze -- pointer to maze structure with all necessary maze information
 *                       col -- the column of the cell currently beinging visited within the maze
 *                       row -- the row of the cell currently being visited within the maze
 * OUTPUTS:              None
 * RETURNS:              0 if the maze is unsolvable, 1 if it is solved
 * SIDE EFFECTS:         Marks maze cells as visited or part of the solution path
 */ 
int solveMazeManhattanDFS(maze_t * maze, int col, int row)
{
    // Your code here. Make sure to replace following line with your own code.
    return 0;
}
