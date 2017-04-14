/*
 *	File that handles IO and manipulates of a sparse matrix. It stores a sparse matrix in a 
 *	linked list data structure, in row major order. IO includes loading and saving of a matrix
 *	to file. It can also do addition and multiplication given two matrices.
 */

#include "sparsemat.h"

#include <stdio.h>
#include <stdlib.h>





sp_tuples * load_tuples(char* input_file)
{
	sp_tuples * newTuple = (sp_tuples *) malloc(sizeof(sp_tuples));

	FILE * file;
	file = fopen(input_file, "r");   // read file, assume file is valid

	int row, col;
	double val;

	fscanf(file, "%d", &row);
    fscanf(file, "%d", &col);
    // init tuples
    newTuple->m = row;
    newTuple->n = col;
    newTuple->nz = 0;
    newTuple->tuples_head = NULL;

    while(feof(file) == 0)
    {
    	fscanf(file, "%d", &row);
    	fscanf(file, "%d", &col);
    	fscanf(file, "%lf", &val);
    	set_tuples(newTuple, row, col, val);
    }
    fclose(file);

    return newTuple;
}



double gv_tuples(sp_tuples * mat_t,int row,int col)

{
	int r, c;
	sp_tuples_node * curr = mat_t->tuples_head;
	// traverse linked list
	while(curr != NULL)
	{
		r = curr->row;
		c = curr->col;
		if(r == row && c == col)
			return curr->value;
		curr = curr->next;
	}

    return 0;	// if it's not in our linked list, it is 0
}



void set_tuples(sp_tuples * mat_t, int row, int col, double value)
{
    sp_tuples_node * curr = mat_t->tuples_head;
    sp_tuples_node * prev = NULL;
    sp_tuples_node * newNode;

    if (curr == NULL && value != 0)		// if empty and not zero, just insert in front
    {   	
    	newNode = (sp_tuples_node *) malloc(sizeof(sp_tuples_node));
    	newNode->row = row;
    	newNode->col = col;
    	newNode->value = value;
    	mat_t->tuples_head = newNode;
    	mat_t->nz++;
    	return;
    }
	while (curr->row < row || (curr->row == row && curr->col <= col))
	{
		if (curr->row == row && curr->col == col)	// if found
		{
			if (value == 0)		// delete if value is 0
			{
				prev->next = curr->next;
				free(curr);
				mat_t->nz--;
				return;
			}
			if (value != 0)		// found and value not 0, update
			{
				curr->value = value;
				return;
			}
		}			
		prev = curr;			// not yet found, traverse
		curr = curr->next;
		if (curr == NULL)
			break;
	}
    
    if (value != 0)		// does not exist yet, need to insert
    {
		newNode = (sp_tuples_node *) malloc(sizeof(sp_tuples_node));
		newNode->row = row;
		newNode->col = col;
		newNode->value = value;
		newNode->next = curr;
		if (prev != NULL)
			prev->next = newNode;
		else
			mat_t->tuples_head = newNode;
		mat_t->nz++;
    }

}



void save_tuples(char * file_name, sp_tuples * mat_t)
{
	FILE * file;
	file = fopen(file_name, "w");   // write file, assume file is valid

	fprintf(file, "%d %d\n", mat_t->m, mat_t->n);	// print rows, cols

	sp_tuples_node * curr = mat_t->tuples_head;
	while (curr != NULL)
	{
		fprintf(file, "%d %d %lf\n", curr->row, curr->col, curr->value);
		curr = curr->next;
	}

	fclose(file);
}



sp_tuples * add_tuples(sp_tuples * matA, sp_tuples * matB)
{
	if ((matA->m != matB->m) || (matA->n != matB->m))		// illegal addition
		return NULL;

	sp_tuples * retmat = (sp_tuples *) malloc(sizeof(sp_tuples));
	retmat->m = matA->m;
	retmat->n = matA->n;
	retmat->nz = 0;
	// use algorithm defined by mp page
	sp_tuples_node * curr = matA->tuples_head;
	while (curr != NULL)
	{
		set_tuples(retmat, curr->row, curr->col, curr->value);
		curr = curr->next;
	}
	curr = matB->tuples_head;
	while (curr != NULL)
	{
		set_tuples(retmat, curr->row, curr->col, curr->value + gv_tuples(matA, curr->row, curr->col));
		curr = curr->next;
	}

	return retmat;
}



sp_tuples * mult_tuples(sp_tuples * matA, sp_tuples * matB)
{ 
	if (matA->n != matB->m)		// illegal mult
		return NULL;

	sp_tuples * retmat = (sp_tuples *) malloc(sizeof(sp_tuples));
	retmat->m = matA->m;
	retmat->n = matB->n;
	retmat->nz = 0;
	// algorithm given by mp
	int i, j, k;
	double value;
	for (i = 0; i < retmat->m; i++)
	{
		for (j = 0; j < retmat->n; j++)
		{
			value = 0;
			for (k = 0; k < matA->n; k++)
			{
				value += gv_tuples(matA, i, k) * gv_tuples(matB, k, j);
			}
			if (value != 0)
				set_tuples(retmat, i, j, value);
		}
	}
    return retmat;

}

	
void destroy_tuples(sp_tuples * mat_t)
{
	sp_tuples_node * curr, * temp;
	curr = mat_t->tuples_head;
	while (curr != NULL)
	{
		temp = curr;
		curr = curr->next;
		free(temp);
	}
	free(mat_t);
}  






