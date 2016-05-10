#include "ndames.h"
#include <omp.h>

void ndames_par_task_inside(int prof, int rangee, echequier e, int * cpt)
{
	if(prof > 0){
		for(int i = 0 ; i < DIM ; i++)
		{
#pragma omp task
			{
				if(ok(rangee,i,e)){
					int par_cpt = 0;
					echequier par_e;
					memcpy(par_e,e,sizeof(echequier));
					par_e[rangee][i]=true;

					ndames_par_task_inside(prof-1, rangee+1, par_e, &par_cpt);

#pragma omp atomic update
			*cpt += par_cpt;
				}				
#pragma omp taskwait
			}
		}
	}
	else {
		ndames(rangee,e,cpt);
	}
}

void ndames_par_task(int prof, int rangee, echequier e, int * cpt)
{
#pragma omp parallel
#pragma omp single
	ndames_par_task_inside(prof, rangee, e, cpt);
}

int main()
{
	int cpt = 0;
	echequier e;
	memset(e,0,sizeof(echequier));
	omp_set_nested(1);

	TIME(ndames_par_task(2,0,e,&cpt));
	
	printf("\n%d\n",cpt);

	unsigned long temps = TIME_DIFF();
  	fprintf(stderr, "Algorithm time = %ld.%03ldms \n", temps/1000, temps%1000);

	return EXIT_SUCCESS;
}