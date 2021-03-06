#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 1024

#define TIME_DIFF(t1, t2) \
	((t2.tv_sec - t1.tv_sec) * 1000000 + (t2.tv_usec - t1.tv_usec))


void calculer(char a[][N],char b[][N], char c[][N], int tranche) {
	int i,j,k;
	for(i=0;i<tranche;i++) {
	  for(j=0;j<N;j++)
	    c[i][j] = 0;

	  for(k=0;k<N;k++)
	    for(j=0;j<N;j++) {
	      c[i][j]+=a[i][k]*b[k][j];
		}
	}
}

void check(char a[N][N], char c[N][N])
{
  int i,j;
  for(i=0;i<N;i++) 
    for(j=0;j<N;j++) 
      if (c[i][j] != a[i][j])
      {
	fprintf(stderr, "erreur en %d,%d\n", i, j);
	return;
      }
  printf("calcul correct !\n");
}


int main(int argc, char ** argv){
	int i,j;
	int tranche;
	int myid;
	int numprocs;

  /* initialiser MPI, à faire _toujours_ en tout premier du programme */
  MPI_Init(&argc,&argv);

  /* récupérer le nombre de processus lancés */
  MPI_Comm_size(MPI_COMM_WORLD,&numprocs);

  /* récupérer son propre numéro */
  MPI_Comm_rank(MPI_COMM_WORLD,&myid);

  tranche = N / numprocs ;
  
  if (myid == 0)
    {
      char a[N][N], b[N][N], c[N][N];
      
      for(i=0;i<N;i++){
      	for(j=0;j<N;j++){			
      	  a[i][j]=rand()%2;
      	  b[i][j]=i==j; 
      	}
      }

      // envoyer la matrice b à tous
      MPI_Bcast(b,N*N,MPI_CHAR,0,MPI_COMM_WORLD);
      // envoyer la tranche de chacun
      MPI_Scatter(a, N*tranche, MPI_CHAR, MPI_IN_PLACE, N*tranche, MPI_CHAR, 0, MPI_COMM_WORLD);

      calculer(a,b,c,tranche);

      // recevoir la tranche de chacun
      MPI_Gather(MPI_IN_PLACE, N*tranche, MPI_CHAR, c, tranche*N, MPI_CHAR, 0, MPI_COMM_WORLD);

      // verification
      check(a,c);
    }

  else
    {
      char a[tranche][N], b[N][N], c[tranche][N]; 
      
      // recevoir a et b
      MPI_Bcast(b,N*N,MPI_CHAR,0,MPI_COMM_WORLD);

      MPI_Scatter(MPI_IN_PLACE, N*tranche, MPI_CHAR, a, N*tranche, MPI_CHAR, 0, MPI_COMM_WORLD);

      calculer(a,b,c,tranche);

      // envoyer c

      MPI_Gather(c, N*tranche, MPI_CHAR, NULL, tranche*N, MPI_CHAR, 0, MPI_COMM_WORLD);
    }
  
  /* finaliser MPI, à faire _toujours_ à la toute fin du programme */
  MPI_Finalize();
  
  return 0;
}
