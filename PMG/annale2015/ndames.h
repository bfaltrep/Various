#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/time.h>


#define TIME_DIFF() \
        ((_t2.tv_sec - _t1.tv_sec) * 1000000 + (_t2.tv_usec - _t1.tv_usec))

#define TIME(fct) \
	struct timeval _t1, _t2; \
	gettimeofday(&_t1, NULL); \
	fct; \
	gettimeofday(&_t2, NULL);


#define DIM 12



typedef bool echequier[DIM][DIM];



void print_e(echequier e)
{
	for (int i = 0; i < 3 + 0 * DIM; ++i){
		for (int j = 0; j < DIM; ++j)
			printf(" %d ",e[i][j]);
		printf("\n");
	}
}


bool ok(int rangee, int colonne, echequier e)
{
	for (int i = 0; i < DIM; ++i)
		if(e[i][colonne] == true)
			return false;
		
	for (int i = 0; i < DIM; ++i)
		if(e[rangee][i] == true)
			return false;

	//je sais pas comment faire mieux
	for(int i = rangee,j = colonne ; i < DIM && j < DIM; i++, j++)
		if(e[i][j] == true)
			return false;
	
	for(int i = rangee,j = colonne ; i >= 0 && j >= 0; i--, j--)
		if(e[i][j] == true)
			return false;
	
	for(int i = rangee,j = colonne ; i >= 0 && j < DIM; i--, j++)
		if(e[i][j] == true)
			return false;

	for(int i = rangee,j = colonne ; j >= 0 && i < DIM; i++, j--)
		if(e[i][j] == true)
			return false;

	return true;
}


void ndames(int rangee, echequier e, int * cpt)
{
	for (int colonne = 0 ; colonne < DIM ; colonne++)
	{
		if(ok(rangee, colonne, e))
		{
			if(rangee == DIM-1){
				(*cpt)++;
			}
			else
			{
				e[rangee][colonne] = true;
				ndames(rangee+1,e,cpt);
				e[rangee][colonne] = false;
			}
		}
	}
}