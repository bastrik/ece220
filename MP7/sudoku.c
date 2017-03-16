#include "sudoku.h"

//-------------------------------------------------------------------------------------------------
// Start here to work on your MP7
//-------------------------------------------------------------------------------------------------

// You are free to declare any private functions if needed.

// Function: is_val_in_row
// Return true if "val" already existed in ith row of array sudoku.
int is_val_in_row(const int val, const int i, const int sudoku[9][9]) {

  assert(i>=0 && i<9);
  int j;

  for (j = 0; j < 9; j++)
  {
    if (sudoku[i][j] == val)
        return 1;
  }
  
  return 0;
}

// Function: is_val_in_col
// Return true if "val" already existed in jth column of array sudoku.
int is_val_in_col(const int val, const int j, const int sudoku[9][9]) {

  assert(j>=0 && j<9);
  int i;

  for (i = 0; i < 9; i++)
  {
    if (sudoku[i][j] == val)
        return 1;
  }
  
  return 0;
}

// Function: is_val_in_3x3_zone
// Return true if val already existed in the 3x3 zone corresponding to (i, j)
int is_val_in_3x3_zone(const int val, const int i, const int j, const int sudoku[9][9]) {
   
  assert(i>=0 && i<9);
  int norm_i, norm_j, r, c;
  norm_i = i / 3 * 3;
  norm_j = j / 3 * 3;
  
  for (r = norm_i; r < norm_i + 3; r++)
  {
      for (c = norm_j; c < norm_j + 3; c++)
      {
          if (sudoku[r][c] == val)
            return 1;
      }
  }
  return 0;
}

// Function: is_val_valid
// Return true if the val is can be filled in the given entry.
int is_val_valid(const int val, const int i, const int j, const int sudoku[9][9]) {

  assert(i>=0 && i<9 && j>=0 && j<9);

  return (is_val_in_row(val, i, sudoku)==0 && is_val_in_col(val, j, sudoku)==0 &&
   is_val_in_3x3_zone(val, i, j, sudoku)==0);
}

// Procedure: solve_sudoku
// Solve the given sudoku instance.
int solve_sudoku(int sudoku[9][9]) {

  int val, row, col;
  val = is_empty(sudoku, row, col);     // call helper method to find an empty cell
  if (val == 0)
  {
      return 1;
  }

  for (val = 1; val < 10; val++)
  {
    if (is_val_valid(val, row, col, sudoku))
    {
        sudoku[row][col] = val;

        if (solve_sudoku(sudoku))
            return 1;

        sudoku[row][col] = 0;
    }
  }
  return false;
}

// helper function that solves the sudoku
int is_empty(int sudoku[9][9], int &row, int &col)
{
    for (row = 0; row < 9; row++)
        for (col = 0; col < 9; col++)
            if (sudoku[row][col] == 0)
                return 1;
    return 0;
}

// Procedure: print_sudoku  
void print_sudoku(int sudoku[9][9])
{
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      printf("%2d", sudoku[i][j]);
    }
    printf("\n");
  }
}

// Procedure: parse_sudoku
void parse_sudoku(const char fpath[], int sudoku[9][9]) {
  FILE *reader = fopen(fpath, "r");
  assert(reader != NULL);
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      fscanf(reader, "%d", &sudoku[i][j]);
    }
  }
  fclose(reader);
}





