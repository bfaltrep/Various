#include <stdio.h>
#include <stdlib.h>

#include <sys/time.h>
/* macro de mesure de temps, retourne une valeur en µsecondes */
#define TIME_DIFF(t1, t2) \
  ((t2.tv_sec - t1.tv_sec) * 1000000 + (t2.tv_usec - t1.tv_usec))


#define MAX(a,b) ((a)>(b)?(a):(b))

#define DIM 63
#define GRAIN 32

int image[DIM+1][DIM+1];


volatile int celluled[GRAIN][GRAIN];
volatile int cellulem[GRAIN][GRAIN];

volatile int cont = 0;

#include "spirale.c"


void first_touch()
{
  int i,j ;

  for(i = 0; i<=DIM ; i++)
    {
      for(j = 1; j<=DIM ; j+=512)
	image[i][j]= 0 ;
    }
}


void identifier_pixel()
{
  int i,j;
  for(i = 1; i<DIM ; i++)
    for(j = 1; j<DIM ; j++)
      image[i][j]=image[i][j]*(i*DIM+j);
}


void 
afficher()
{
  int i,j;
  for (i=0; i < DIM; i++)
    {
      for(j=0; j < DIM; j++)
	printf("%4d ", image[i][j]);
      putchar('\n');
    }

}



int monter_max(int i_d, int j_d, int i_f, int j_f)
{
  int i,j;
 
  int changement = 0;
  for (i=i_d; i >= i_f; i--)
      for (j=j_d; j >= j_f; j--)
	if (image[i][j])
	  { 
	    int m;
	    m = MAX(image[i+1][j] , image[i][j+1]);
	    if (m > image[i][j])
	      {	    
		changement = 1;
		image[i][j] = m;
	      }
	  }
  return changement;
}


#define TRANCHE ((DIM+1)/GRAIN)


int descendre_max(int i_d, int j_d, int i_f, int j_f)
{
  int i,j;
  int changement = 0;

  for (i=i_d; i <= i_f; i++)
    for (j=j_d; j <= j_f; j++)
      { 
	if (image[i][j])
	  {
	    int m = MAX(image[i-1][j] , image[i][j-1]);
	    if (m > image[i][j])
	      {	    
		changement = 1;
		image[i][j] = m;
	      }
	  }
      }
  
  return changement;
}


void 
lancer_descente(int i, int j)
{
  int i_d = (i == 0) ? 1 : i * TRANCHE ;
  int j_d = (j == 0) ? 1 : j * TRANCHE ;
  int i_f = (i == GRAIN-1) ? DIM-1 : (i+1) * TRANCHE-1 ;
  int j_f = (j == GRAIN-1) ? DIM-1 : (j+1) * TRANCHE-1 ;

  if(descendre_max(i_d,j_d,i_f,j_f))
    cont = 1;
}

void
lancer_monte(int i, int j)
{

  int i_d = (i == GRAIN-1) ? DIM-1 : (i+1) * TRANCHE-1 ;
  int j_d = (j == GRAIN-1) ? DIM-1 : (j+1) * TRANCHE-1 ;
  int i_f = (i == 0) ? 1 : i * TRANCHE ;
  int j_f = (j == 0) ? 1 : j * TRANCHE ;
  
  if (monter_max(i_d,j_d,i_f,j_f))
	cont = 1;
}


int 
main()
{
  int etape = 0;
  unsigned long temps;
  struct timeval t1, t2;
  
  regulier(1,DIM,1,DIM,2,4);
  identifier_pixel();
  gettimeofday(&t1,NULL);
  
  do {
    cont = 0; 

    for (int i=0; i < GRAIN; i++ )
      for (int j=0; j < GRAIN; j++ )
	lancer_descente(i,j);

      for (int i=0; i < GRAIN; i++ )
	for (int j=0; j < GRAIN; j++ )
	    lancer_monte(GRAIN-i-1,GRAIN-j-1);

      printf("********* %d *********\n",etape++);
      //afficher();
  }  while(cont);
  
  gettimeofday(&t2,NULL);
  temps = TIME_DIFF(t1,t2);
  
  printf("time = %ld.%03ldms", temps/1000, temps%1000);
  
  return 0;
}
