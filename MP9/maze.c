/*
 *  File containing methods for building, printing, solving, destroying an arbitary maze.
 *  Create maze will make a maze on the heap, and solving maze uses DFS to find a solution
 *  for the maze. If there is no solution for the current maze, will return "unsolvable"
 *  This file contains declaration for helper method getPath b/c we cannot modify maze.h
 */

#include <stdio.h>
#include <stdlib.h>
#include "maze.h"

/*
 * getPath -- Helper method for DFS
 */
char getPath(maze_t * maze, int x, int y);

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
	file = fopen(fileName, "r");   // read file, assume file is valid
    fscanf(file, "%d", &width);
    fscanf(file, "%d", &height);
    fgetc(file);

    newMaze->width = width;
    newMaze->height = height;

    newMaze->cells = (char **)malloc(sizeof(char *) * height);      // allocating 2d array
    for(i = 0; i < height; i++)
    	newMaze->cells[i] = (char *)malloc(sizeof(char) * width);

    i = 0;
    j = 0;
    while ((c = fgetc(file)) != EOF)
    {
    	if (c == '\n')     // if at end of line, reset row counter
    	{
    		i++;
    		j = 0;
    	}
    	else
    	{
    		newMaze->cells[i][j] = c;
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
    		j++;
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
    for (i = 0; i < maze->height; i++)      // free ** cells before maze
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
// helper that checks conditions and return char value at a cell location
char getPath(maze_t * maze, int col, int row)
{
	if (col > -1 && col < maze->width && row > -1 && row < maze->height)
		return maze->cells[row][col];
	else return '*';	// out of bound
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
    if (getPath(maze, col, row-1) == 'E' || getPath(maze, col, row+1) == 'E'
    	|| getPath(maze, col-1, row) == 'E' || getPath(maze, col+1, row) == 'E')
    {
    	return 1;		// base case
    }
    
    if (getPath(maze, col-1, row) == ' ')		// Left
    {
    	maze->cells[row][col-1] = '.';
    	if (solveMazeManhattanDFS(maze, col-1, row) == 1)
    	{
    		return 1;
    	}
    }
    if (getPath(maze, col, row+1) == ' ')		// Down
    {
    	maze->cells[row+1][col] = '.';
    	if (solveMazeManhattanDFS(maze, col, row+1) == 1)
    	{
    		return 1;
    	}
    }
    if (getPath(maze, col+1, row) == ' ')		// Right
    {
    	maze->cells[row][col+1] = '.';
    	if (solveMazeManhattanDFS(maze, col+1, row) == 1)
    	{
    		return 1;
    	}
    }
    if (getPath(maze, col, row-1) == ' ')		// Up
    {
    	maze->cells[row-1][col] = '.';
    	if (solveMazeManhattanDFS(maze, col, row-1) == 1)
    	{
    		return 1;
    	}
    }
    maze->cells[row][col] = '~';
    return 0;
}
