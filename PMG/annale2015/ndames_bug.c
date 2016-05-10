#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <string.h>
#include <stdbool.h>
#include <sys/time.h>


#define TIME_DIFF(t1, t2) \
        ((t2.tv_sec - t1.tv_sec) * 1000000 + (t2.tv_usec - t1.tv_usec))

#define DIM 12


typedef bool echequier[DIM][DIM];


void print(echequier e)
{
	for (int i = 0; i < DIM; ++i){
		for (int j = 0; j < DIM; ++j)
			printf(" %d ",e[i][j]);
		printf("\n");
	}
	printf("\n");
}


static bool ok(int rangee, int colonne, echequier e)
{
	for (int i = 0; i < DIM; ++i)
	{
		if(e[i][colonne] == true)
			return false;
	}
	for (int i = 0; i < DIM; ++i)
	{
		if(e[rangee][i] == true)
			return false;
	}

	//je sais pas comment faire mieux
	for(int i = rangee,j = colonne ; i < DIM && j < DIM; i++, j++)
	{
		if(e[i][j] == true)
			return false;
	}
	for(int i = rangee,j = colonne ; i >= 0 && j >= 0; i--, j--)
	{
		if(e[i][j] == true)
			return false;
	}
	for(int i = rangee,j = colonne ; i >= 0 && j < DIM; i--, j++)
	{
		if(e[i][j] == true)
			return false;
	}
	for(int i = rangee,j = colonne ; j >= 0 && i < DIM; i++, j--)
	{
		if(e[i][j] == true)
			return false;
	}
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



void ndames_par_1(int * cpt)
{
	int par_cpt = 0;
	echequier e;
	memset(e, 0, sizeof(echequier));

#pragma omp parallel for firstprivate(e) reduction(+:par_cpt) schedule(static,1) 
	for(int i = 0 ; i < DIM ; i++)
	{
		e[0][i]=true;

		ndames(1,e,&par_cpt);
	}

	*cpt = par_cpt;
}



int main()
{
	int cpt = 0;

	unsigned long temps;
	struct timeval t1, t2;

  	gettimeofday(&t1,NULL);
	ndames_par_1(&cpt);
	gettimeofday(&t2,NULL);

	printf("\n%d\n",cpt);
	temps = TIME_DIFF(t1,t2);
  	printf("Algorithm time = %ld.%03ldms \n", temps/1000, temps%1000);

	return EXIT_SUCCESS;
}