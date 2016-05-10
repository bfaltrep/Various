#include "ndames.h"
#include <omp.h>



void ndames_par_1(int * cpt)
{
#pragma omp parallel for schedule(static)
	for(int i = 0 ; i < DIM ; i++) {
		echequier e;
		memset(e, 0, sizeof(echequier));
		int par_cpt=0;
		e[0][i] = true;
		
		ndames(1, e, &par_cpt);
#pragma omp atomic update
	*cpt += par_cpt;
	}

}



int main()
{
	int cpt = 0;
	
	TIME(ndames_par_1(&cpt));
	
	printf("\n%d\n",cpt);

	unsigned long temps = TIME_DIFF();
  	fprintf(stderr, "Algorithm time = %ld.%03ldms \n", temps/1000, temps%1000);

	return EXIT_SUCCESS;
}