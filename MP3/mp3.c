/**
  *   A program that prints a row in Pascal's triangle. It takes an user input as 
  *   the row index and computes all the coefficients for that row.
  */

#include <stdio.h>
#include <stdlib.h>

double fac(int i)     // helper function for computing n!
{
  double ret;
  ret = 1;
  if (i == 0)
    return ret; 
  while (i > 0)       // iteritive approach to avoid stack overflow
  {
    ret = ret*i;
    i--;
  }
  return ret;
}

int main()
{
  int row_index;
  int i,k;
  double nom, denom, out;

  printf("Enter the row index: ");
  scanf("%d",&row_index);
  
  for (i = 0; i < row_index; i++)
  {
  	k = i;
  	nom = fac(row_index);              // computers (n, k)
  	denom = fac(k) * fac(row_index-k);
  	out = nom/denom;
  	printf("%.0lf ", out);
  }
  
  printf("1\n");                       // add the last 1
  return 0;
}


