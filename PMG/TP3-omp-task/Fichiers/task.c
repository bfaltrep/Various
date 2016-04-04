#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>


int f()
{
  
  int i;
  int k = 666 ;
  
#pragma omp single // nowait
  for(i = 1000; i < 1010 ; i++)
#pragma omp task shared(k)
    {
      printf("DEB [%d] pour %d \n",k,omp_get_thread_num());
      sleep(1);
      printf("FIN [%d] pour %d \n",k,omp_get_thread_num());
    }

  //  #pragma omp taskwait
}



int main()
{

#pragma omp parallel
  {
    f();
    printf("%d fin \n", omp_get_thread_num());
  }
}
  
