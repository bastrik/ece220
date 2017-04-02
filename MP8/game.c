 /*
  *   2048
  *   game.c contains the logic functions for the game 2048. The difference in this version is that game is not
  *   limited to a 4x4 grid but rather any MxN grid. Rules and goal of the game are the same, as you can move
  *   up, down, left, right for the goal of getting a 2048 tile, for which you win the game. Game ends when
  *   you haven't reached 2048 and ran out of space on the board.
  *
  *   This class contains functions that make the game, move (up, down, left, right), and check if move is legal.
  */


#include "game.h"


game * make_game(int rows, int cols)
/*! Create an instance of a game structure with the given number of rows
    and columns, initializing elements to -1 and return a pointer
    to it. (See game.h for the specification for the game data structure) 
    The needed memory should be dynamically allocated with the malloc family
    of functions.
*/
{
    //Dynamically allocate memory for game and cells (DO NOT modify this)
    game * mygame = malloc(sizeof(game));
    mygame->cells = malloc(rows*cols*sizeof(cell));

    // initialize game struct 
    mygame->score = 0;
    mygame->rows = rows;
    mygame->cols = cols;
    int i;
    for (i = 0; i < rows * cols; i++)
        mygame->cells[i] = -1;

    return mygame;
}

void remake_game(game ** _cur_game_ptr,int new_rows,int new_cols)
/*! Given a game structure that is passed by reference, change the
	game structure to have the given number of rows and columns. Initialize
	the score and all elements in the cells to -1. Make sure that any 
	memory previously allocated is not lost in this function.	
*/
{
	/*Frees dynamically allocated memory used by cells in previous game,
	 then dynamically allocates memory for cells in new game.  DO NOT MODIFY.*/
	free((*_cur_game_ptr)->cells);
	(*_cur_game_ptr)->cells = malloc(new_rows*new_cols*sizeof(cell));

    game * mygame = * _cur_game_ptr;
    // reinitialize a game
    mygame->score = 0;
    mygame->rows = new_rows;
    mygame->cols = new_cols;
    int i;
    for (i = 0; i < new_rows * new_cols; i++)
    {
        mygame->cells[i] = -1;
    }
}

void destroy_game(game * cur_game)
/*! Deallocate any memory acquired with malloc associated with the given game instance.
    This includes any substructures the game data structure contains. Do not modify this function.*/
{
    free(cur_game->cells);
    free(cur_game);
    cur_game = NULL;
    return;
}

cell * get_cell(game * cur_game, int row, int col)
/*! Given a game, a row, and a column, return a pointer to the corresponding
    cell on the game. (See game.h for game data structure specification)
    This function should be handy for accessing game cells. Return NULL
	if the row and col coordinates do not exist.
*/
{
    if (cur_game == NULL)   // safeguarding
        return NULL;
    if (row < 0 || row > cur_game->rows -1 || col < 0 || col > cur_game->cols -1)   // edge case
        return NULL;
    
    return &(cur_game->cells[row * cur_game->cols + col]);
}

int move_w(game * cur_game)
/*!Slides all of the tiles in cur_game upwards. If a tile matches with the 
   one above it, the tiles are merged by adding their values together. When
   tiles merge, increase the score by the value of the new tile. A tile can 
   not merge twice in one turn. If sliding the tiles up does not cause any 
   cell to change value, w is an invalid move and return 0. Otherwise, return 1. 
*/
{
    int rows = cur_game->rows;
    int cols = cur_game->cols;
    int row, col, currRow;
    int curr, target;
    int valid = 0;
    int mergedCell[rows][cols];   // i like 2d arrays better

    for (row = 1; row < rows; row++)
    {
        for (col = 0; col < cols; col++)
        {
            currRow = row;
            // if curr cell not empty, we iterate from current row (row) upwards
            while (* get_cell(cur_game, currRow, col) != -1 && currRow > 0)
            {
                curr = * get_cell(cur_game, currRow, col);
                target = * get_cell(cur_game, currRow -1, col);
                // if this target cell above is of same value and haven't merged, we merge
                // and add score
                if (curr == target && mergedCell[currRow -1][col] != 1)
                {
                    * get_cell(cur_game, currRow -1, col) = target * 2;
                    cur_game->score += target * 2;
                    * get_cell(cur_game, currRow, col) = -1;
                    mergedCell[currRow -1][col] = 1;    // set target cell as merged
                    valid = 1;
                    break;    // can move onto next cell
                }
                // if target cell is empty, we simply move curr to target
                if (target == -1)
                {
                    * get_cell(cur_game, currRow -1, col) = curr;
                    * get_cell(cur_game, currRow, col) = -1;
                    valid = 1;
                    currRow--;
                }
                else
                  break;
            }
        }
    }
    return valid;
};

int move_s(game * cur_game) //slide down
{
    int rows = cur_game->rows;
    int cols = cur_game->cols;
    int row, col, currRow;
    int curr, target;
    int valid = 0;
    int mergedCell[rows][cols];

    for (row = rows -2; row > -1; row--)
    {
        for (col = 0; col < cols; col++)
        {
            currRow = row;
            while (* get_cell(cur_game, currRow, col) != -1 && currRow < rows -1)
            {
                curr = * get_cell(cur_game, currRow, col);
                target = * get_cell(cur_game, currRow +1, col);
                if (curr == target && mergedCell[currRow +1][col] != 1)
                {
                    * get_cell(cur_game, currRow +1, col) = target * 2;
                    cur_game->score += target * 2;
                    * get_cell(cur_game, currRow, col) = -1;
                    mergedCell[currRow +1][col] = 1;
                    valid = 1;
                    currRow++;
                    break;
                }
                if (target == -1)
                {
                    * get_cell(cur_game, currRow +1, col) = curr;
                    * get_cell(cur_game, currRow, col) = -1;
                    valid = 1;
                    currRow++;
                }
                else
                    break;
            }
        }
    }
    return valid;
};

int move_a(game * cur_game) //slide left
{
    int rows = cur_game->rows;
    int cols = cur_game->cols;
    int row, col, currCol;
    int curr, target;
    int valid = 0;
    int mergedCell[rows][cols];

    for (row = 0; row < rows; row++)
    {
        for (col = 1; col < cols; col++)
        {
            currCol = col;
            while (* get_cell(cur_game, row, currCol) != -1 && currCol > 0)
            {
                curr = * get_cell(cur_game, row, currCol);
                target = * get_cell(cur_game, row, currCol -1);
                if (curr == target && mergedCell[row][currCol -1] != 1)
                {
                    * get_cell(cur_game, row, currCol -1) = target * 2;
                    cur_game->score += target * 2;
                    * get_cell(cur_game, row, currCol) = -1;
                    mergedCell[row][currCol -1] = 1;
                    valid = 1;
                    currCol--;
                    break;
                }
                if (target == -1)
                {
                    * get_cell(cur_game, row, currCol -1) = curr;
                    * get_cell(cur_game, row, currCol) = -1;
                    valid = 1;
                    currCol--;
                }
                else
                    break;
            }
        }
    }
    return valid;
};

int move_d(game * cur_game) //slide to the right
{ 
    int rows = cur_game->rows;
    int cols = cur_game->cols;
    int row, col, currCol;
    int curr, target;
    int valid = 0;
    int mergedCell[rows][cols];

    for (row = 0; row < rows; row++)
    {
        for (col = cols -2; col > -1; col--)
        {
            currCol = col;
            while (* get_cell(cur_game, row, currCol) != -1 && currCol < cols -1)
            {
                curr = * get_cell(cur_game, row, currCol);
                target = * get_cell(cur_game, row, currCol +1);
                if (curr == target && mergedCell[row][currCol +1] != 1)
                {
                    * get_cell(cur_game, row, currCol +1) = target * 2;
                    cur_game->score += target * 2;
                    * get_cell(cur_game, row, currCol) = -1;
                    mergedCell[row][currCol +1] = 1;
                    valid = 1;
                    currCol++;
                    break;
                }
                if (target == -1)
                {
                    * get_cell(cur_game, row, currCol +1) = curr;
                    * get_cell(cur_game, row, currCol) = -1;
                    valid = 1;
                    currCol++;
                }
                else
                    break;
            }
        }
    }
    return valid;
};

int legal_move_check(game * cur_game)
/*! Given the current game check if there are any legal moves on the board. There are
    no legal moves if sliding in any direction will not cause the game to change.
	Return 1 if there are possible legal moves, 0 if there are none.
 */
{
    int row, col, curr, next;
    for (row = 0; row < cur_game->rows; row++)
    {
        for (col = 0; col < cur_game->cols; col++)
        {
            if (cur_game->cells[row * cur_game->cols + col] == -1) 
                return 1;       // return 1 if empty
                                // if all filled, check for adjecent tiles
            if (row < (cur_game->rows - 1)) 
            {
                next = cur_game->cells[(row+1) * cur_game->cols + col];
                curr = cur_game->cells[ row    * cur_game->cols + col];
                if (curr == next)
                    return 1;
            }    
            if (col < (cur_game->cols - 1)) 
            {
                next = cur_game->cells[row * cur_game->cols + col + 1];
                curr = cur_game->cells[row * cur_game->cols + col];
                if (curr == next) 
                    return 1;
            }    
        }
    }

    return 0;
}


/*! code below is provided and should not be changed */

void rand_new_tile(game * cur_game)
/*! insert a new tile into a random empty cell. First call rand()%(rows*cols) to get a random value between 0 and (rows*cols)-1.
*/
{
	
	cell * cell_ptr;
    cell_ptr = 	cur_game->cells;
	
    if (cell_ptr == NULL){ 	
        printf("Bad Cell Pointer.\n");
        exit(0);
    }
	
	
	//check for an empty cell
	int emptycheck = 0;
	int i;
	
	for(i = 0; i < ((cur_game->rows)*(cur_game->cols)); i++){
		if ((*cell_ptr) == -1){
				emptycheck = 1;
				break;
		}		
        cell_ptr += 1;
	}
	if (emptycheck == 0){
		printf("Error: Trying to insert into no a board with no empty cell. The function rand_new_tile() should only be called after tiles have succesfully moved, meaning there should be at least 1 open spot.\n");
		exit(0);
	}
	
    int ind,row,col;
	int num;
    do{
		ind = rand()%((cur_game->rows)*(cur_game->cols));
		col = ind%(cur_game->cols);
		row = ind/cur_game->cols;
    } while ( *get_cell(cur_game, row, col) != -1);
        //*get_cell(cur_game, row, col) = 2;
	num = rand()%20;
	if(num <= 1){
		*get_cell(cur_game, row, col) = 4; // 1/10th chance
	}
	else{
		*get_cell(cur_game, row, col) = 2;// 9/10th chance
	}
}

int print_game(game * cur_game) 
{
    cell * cell_ptr;
    cell_ptr = 	cur_game->cells;

    int rows = cur_game->rows;
    int cols = cur_game->cols;
    int i,j;
	
	printf("\n\n\nscore:%d\n",cur_game->score); 
	
	
	printf("\u2554"); // topleft box char
	for(i = 0; i < cols*5;i++)
		printf("\u2550"); // top box char
	printf("\u2557\n"); //top right char 
	
	
    for(i = 0; i < rows; i++){
		printf("\u2551"); // side box char
        for(j = 0; j < cols; j++){
            if ((*cell_ptr) == -1 ) { //print asterisks
                printf(" **  "); 
            }
            else {
                switch( *cell_ptr ){ //print colored text
                    case 2:
                        printf("\x1b[1;31m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 4:
                        printf("\x1b[1;32m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 8:
                        printf("\x1b[1;33m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 16:
                        printf("\x1b[1;34m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 32:
                        printf("\x1b[1;35m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 64:
                        printf("\x1b[1;36m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 128:
                        printf("\x1b[31m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 256:
                        printf("\x1b[32m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 512:
                        printf("\x1b[33m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 1024:
                        printf("\x1b[34m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 2048:
                        printf("\x1b[35m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 4096:
                        printf("\x1b[36m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 8192:
                        printf("\x1b[31m%04d\x1b[0m ",(*cell_ptr));
                        break;
					default:
						printf("  X  ");

                }

            }
            cell_ptr++;
        }
	printf("\u2551\n"); //print right wall and newline
    }
	
	printf("\u255A"); // print bottom left char
	for(i = 0; i < cols*5;i++)
		printf("\u2550"); // bottom char
	printf("\u255D\n"); //bottom right char
	
    return 0;
}

int process_turn(const char input_char, game* cur_game) //returns 1 if legal move is possible after input is processed
{ 
	int rows,cols;
	char buf[200];
	char garbage[2];
    int move_success = 0;
	
    switch ( input_char ) {
    case 'w':
        move_success = move_w(cur_game);
        break;
    case 'a':
        move_success = move_a(cur_game);
        break;
    case 's':
        move_success = move_s(cur_game);
        break;
    case 'd':
        move_success = move_d(cur_game);
        break;
    case 'q':
        destroy_game(cur_game);
        printf("\nQuitting..\n");
        return 0;
        break;
	case 'n':
		//get row and col input for new game
		dim_prompt: printf("NEW GAME: Enter dimensions (rows columns):");
		while (NULL == fgets(buf,200,stdin)) {
			printf("\nProgram Terminated.\n");
			return 0;
		}
		
		if (2 != sscanf(buf,"%d%d%1s",&rows,&cols,garbage) ||
		rows < 0 || cols < 0){
			printf("Invalid dimensions.\n");
			goto dim_prompt;
		} 
		
		remake_game(&cur_game,rows,cols);
		
		move_success = 1;
		
    default: //any other input
        printf("Invalid Input. Valid inputs are: w, a, s, d, q, n.\n");
    }

	
	
	
    if(move_success == 1){ //if movement happened, insert new tile and print the game.
         rand_new_tile(cur_game); 
		 print_game(cur_game);
    } 

    if( legal_move_check(cur_game) == 0){  //check if the newly spawned tile results in game over.
        printf("Game Over!\n");
        return 0;
    }
    return 1;
}
