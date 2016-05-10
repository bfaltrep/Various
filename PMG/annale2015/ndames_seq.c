#include "ndames.h"



int main()
{
	echequier e;
	int cpt = 0;
	memset(e, 0, sizeof(echequier));

	TIME(ndames(0, e, &cpt));	

	printf("\n%d\n", cpt);

	unsigned long temps = TIME_DIFF();
  	fprintf(stderr, "Algorithm time = %ld.%03ldms \n", temps/1000, temps%1000);

	return EXIT_SUCCESS;
}