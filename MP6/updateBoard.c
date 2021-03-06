/*
 *	This class contains the functions necessary to update the game board. It allows checking for live neighbors for a given cell
 *	loops through the board and updates the board, and can detect when the game has entered a stable state i.e no more changes.
 *  This class completes the logic of Game of Life.
 * 	My implementation makes use of standard library functions (malloc, memcpy, memcmp) 
 */


#include <stdlib.h>
#include <string.h>
#include "updateBoard.h"
/*
 * countLiveNeighbor
 * Inputs:
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * row: the row of the cell that needs to count alive neighbors.
 * col: the col of the cell that needs to count alive neighbors.
 * Output:
 * return the number of alive neighbors. There are at most eight neighbors.
 * Pay attention for the edge and corner cells, they have less neighbors.
 */

int countLiveNeighbor(int* board, int boardRowSize, int boardColSize, int row, int col)
{
	int r = boardRowSize;
	int c = boardColSize;
	if (row == 0)
	{
		if (col == 0)						// top left corner
		{
			return(	/*      current        */	isAlive(r,c, board, 0, 1) + 
					isAlive(r,c, board, 1, 0) + isAlive(r,c, board, 1, 1));
		} else if (col == boardColSize-1)	// top right corner
		{
			return(isAlive(r,c, board, 0, col-1)      +   /*      current        */
				   isAlive(r,c, board, row+1 , col-1) + isAlive(r,c, board, row+1, col));
		}else 								// top row not corner
		{
			return(isAlive(r,c, board, 0, col-1) + /*      current        */      isAlive(r,c, board, 0, col+1) + 
				   isAlive(r,c, board, 1, col-1) + isAlive(r,c, board, 1, col) +  isAlive(r,c, board, 1 , col+1));
		}
	}
	if (row == boardRowSize-1)
	{
		if (col == 0)						// bottom left corner
		{
			return(isAlive(r,c, board, row-1, 0) + isAlive(r,c, board, row-1 , 1) + 
				   /*      current        */	   isAlive(r,c, board, row, 1));
		} else if (col == boardColSize-1)		// bottom right corner
		{
			return(isAlive(r,c, board, row-1, col-1) + isAlive(r,c, board, row-1 , col) + 
				   isAlive(r,c, board, row, col-1));
		}else 								// bottom row not corner
		{
			return(isAlive(r,c, board, row, col-1) + 									isAlive(r,c, board, row, col+1) + 
				isAlive(r,c, board, row-1, col-1) + isAlive(r,c, board, row-1 , col) + isAlive(r,c, board, row-1, col+1));
		}

	}

	if (col == 0)							// left colomn not corner
	{
		return(isAlive(r,c, board, row-1, col) + isAlive(r,c, board, row-1, col+1) + 
			isAlive(r,c, board, row, col+1) + isAlive(r,c, board, row+1, col) + isAlive(r,c, board, row+1, col+1));
	} else if (col == boardColSize-1)
	{
		return(isAlive(r,c, board, row-1, col-1) + isAlive(r,c, board, row-1, col) + 
			isAlive(r,c, board, row, col-1) + isAlive(r,c, board, row+1, col-1) + isAlive(r,c, board, row+1, col));
	}
	// not edge case
	return(isAlive(r,c, board, row-1, col-1) + isAlive(r,c, board, row-1, col) + isAlive(r,c, board, row-1, col+1) + 
		   isAlive(r,c, board, row, col-1)   + 	/*      current        */		 isAlive(r,c, board, row, col+1) + 
		   isAlive(r,c, board, row+1, col-1) + isAlive(r,c, board, row+1, col) + isAlive(r,c, board, row+1, col+1));									
	
}
/*
 * Update the game board to the next step.
 * Input: 
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: board is updated with new values for next step.
 */
void updateBoard(int* board, int boardRowSize, int boardColSize) {
	int i, len, currNeighbor;
	int r, c;
	len = boardRowSize * boardColSize;
	int* refboard = malloc(len * sizeof(int));
	memcpy(refboard, board, len * sizeof(int));		// perserve current board 
	for (i = 0; i < len; i++)
	{
		r = i / boardColSize;		// get row number
		c = i % boardColSize;		// get col number
		currNeighbor = countLiveNeighbor(board, boardRowSize, boardColSize, r, c);
		if(board[i])				// current cell = 1
		{
			if(currNeighbor != 2 && currNeighbor != 3)

				refboard[i] = 0;
		}
		else						// current cell = 0
		{
			if(currNeighbor == 3)

				refboard[i] = 1;
		}
	}
	memcpy(board, refboard, len * sizeof(int));		// write the updated board to board
}

/*
 * aliveStable
 * Checks if the alive cells stay the same for next step
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: return 1 if the alive cells for next step is exactly the same with 
 * current step or there is no alive cells at all.
 * return 0 if the alive cells change for the next step.
 */ 
int aliveStable(int* board, int boardRowSize, int boardColSize){
	int len;
	len = boardRowSize * boardColSize;
	int* newboard = malloc(len * sizeof(int));			// make a new board
	memcpy(newboard, board, len * sizeof(int));
	updateBoard(newboard, boardRowSize, boardColSize);	// update the new board

	if (memcmp(board, newboard, len* sizeof(int)) == 0)	// if new board = board, we are done
		return 1;
	return 0;
}

// helper function to determine if a cell is alive
int isAlive(int r, int c, int* board, int row, int col)
{
	return board[row*c + col];
}				
				
			

