#include "sparsemat.h"

#include <stdio.h>
#include <stdlib.h>





sp_tuples * load_tuples(char* input_file)
{
	sp_tuples * newTuple = malloc(sizeof(sp_tuples));

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
		if(r = row && c = col)
			return curr->value;
		curr = curr->next;
	}

    return 0;
}



void set_tuples(sp_tuples * mat_t, int row, int col, double value)
{
    return;
}



void save_tuples(char * file_name, sp_tuples * mat_t)
{

	return;
}



sp_tuples * add_tuples(sp_tuples * matA, sp_tuples * matB){

	return retmat;
}



sp_tuples * mult_tuples(sp_tuples * matA, sp_tuples * matB){ 
    return retmat;

}


	
void destroy_tuples(sp_tuples * mat_t){
	
    return;
}  






