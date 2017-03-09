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
	int boardRowSize = r;
	int boardColSize = c;
	if (row == 0)
	{
		if (col == 0)						// top left corner
		{
			return(isAlive(r,c, board, 0, 1) + isAlive(r,c, board, row+1 , 0) + isAlive(r,c, board, row+1, col+1));
		} else if (col == boardColSize)		// top right corner
		{
			return(isAlive(r,c, board, 0, col-1) + isAlive(r,c, board, row+1 , col) + isAlive(r,c, board, row-1, col-1));
		}else 								// top row not corner
		{
			return(isAlive(r,c, board, 0, col-1) + isAlive(r,c, board, 0, col+1) + 
				isAlive(r,c, board, 1, col-1) + isAlive(r,c, board, 1, col+1) +isAlive(r,c, board, 1 , col));
		}
	}
	if (row == boardRowSize)
	{
		if (col == 0)						// bottom left corner
		{
			return(isAlive(r,c, board, row-1, 0) + isAlive(r,c, board, row-1 , 1) + isAlive(r,c, board, row, 1));
		} else if (col == boardColSize)		// bottom right corner
		{
			return(isAlive(r,c, board, row-1, col) + isAlive(r,c, board, row-1 , col-1) + isAlive(r,c, board, row, col-1));
		}else 								// bottom row not corner
		{
			return(isAlive(r,c, board, row, col-1) + isAlive(r,c, board, row, col+1) + 
				isAlive(r,c, board, row-1, col-1) + isAlive(r,c, board, row-1, col+1) +isAlive(r,c, board, row-1 , col));
		}

	}

	if (col == 0)							// left colomn not corner
	{
		return(isAlove(r,c, board, row-1, col) + isAlove(r,c, board, row+1, col) + 
			isAlove(r,c, board, row-1, col+1) + isAlove(r,c, board, row, col+1) + isAlove(r,c, board, row+1, col+1));
	} else if (col == boardColSize)
	{
		return(isAlove(r,c, board, row-1, col) + isAlove(r,c, board, row+1, col) + 
			isAlove(r,c, board, row-1, col-1) + isAlove(r,c, board, row, col-1) + isAlove(r,c, board, row+1, col-1));
	}
	// not edge case
	return(isAlive(r,c, board, row-1, col-1) + isAlive(r,c, board, row-1, col) + isAlive(r,c, board, row-1, col+1) + 
		   isAlive(r,c, board, row, col-1)   + 							   isAlive(r,c, board, row, col+1) + 
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
	int i, len, curr;
	int r, c;
	len = boardRowSize * boardColSize;
	for (i = 0; i < len; i++)
	{
		r = i / boardRowSize;
		c = i % boardColSize;
		curr = board[i];
		switch(curr)
		{
			case 0:
				if(countLiveNeighbor(board, boardRowSize, boardColSize, r, c) == 3)
				{
					board[i] = 1;
					break;
				}
			case 1:
				if(countLiveNeighbor(board, boardRowSize, boardColSize, r, c) != 2 ||
					countLiveNeighbor(board, boardRowSize, boardColSize, r, c) != 3)
				{
					board[i] = 0;
					break;
				}
		}
	}
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
int aliveStable(int b, int c, int* board, int boardRowSize, int boardColSize){
}

int isAlive(int r, int c, int* board, int row, int col)
{
	return board(row*c + col);
}				
				
			

