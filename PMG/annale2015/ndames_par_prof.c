#include "ndames.h"
#include <omp.h>



void ndames_par_prof(int prof, int rangee, echequier e, int * cpt)
{
	if(prof > 0){
//#pragma omp parallel for schedule(static,1)
		for(int i = 0 ; i < DIM ; i++)
		{
			int par_cpt = 0;
			echequier par_e;
			memcpy(par_e,e,sizeof(echequier));
			par_e[rangee][i]=true;

			ndames_par_prof(prof-1, rangee+1, par_e, &par_cpt);

			for (int _ = 0 ; _ < 3-prof; _ ++)
				printf("  ");
			printf("[%d]   %d\n", i, par_cpt);
			printf("\n");

#pragma omp atomic update
			*cpt += par_cpt;
		}
	}
	else {
		print_e(e);
		ndames(rangee,e,cpt);
	}
}


int main()
{
	int cpt = 0;
	echequier e;
	memset(e,0,sizeof(echequier));

	omp_set_nested(1);

	TIME(ndames_par_prof(2,0,e,&cpt));
	
	printf("\n%d\n",cpt);

	unsigned long temps = TIME_DIFF();
  	fprintf(stderr, "Algorithm time = %ld.%03ldms \n", temps/1000, temps%1000);


	return EXIT_SUCCESS;
}
