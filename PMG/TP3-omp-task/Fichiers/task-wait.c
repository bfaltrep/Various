#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <omp.h>


int main()
{
#pragma omp parallel
  {
#pragma omp single nowait
    {
      int maman = omp_get_thread_num();
#pragma omp task firstprivate(maman)
      {
	printf("A [fille de %d] executee par %d \n",maman,omp_get_thread_num());
	sleep(1);
	printf("A FIN \n",maman,omp_get_thread_num());
      }
#pragma omp task firstprivate(maman)
      {
	printf("B [fille de %d] executee par %d \n",maman,omp_get_thread_num());
	sleep(1);
	printf("B FIN \n",maman,omp_get_thread_num());
      }

    }
#pragma omp single nowait
    {
      int maman = omp_get_thread_num();
#pragma omp task firstprivate(maman)
      {
	printf("C [fille de %d] executee par %d \n",maman,omp_get_thread_num());
	sleep(1);
	printf("C FIN \n",maman,omp_get_thread_num());
      }
#pragma omp task firstprivate(maman)
      {
	printf("D [fille de %d] executee par %d \n",maman,omp_get_thread_num());
	sleep(1);
	printf("D FIN \n",maman,omp_get_thread_num());
      }

    }
    
#pragma omp taskwait
    printf("%d a passe taskwait \n", omp_get_thread_num());
  }
  return 0;
}
