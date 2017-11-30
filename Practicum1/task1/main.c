#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include <time.h>
#include <stdlib.h>



int main(int argc, char **argv)
{

    if (argc<3){
        return -1;
    }
    // Starting timer
    time_t start_time;
    time(&start_time);

    long long Anzahl = atoll(argv[1]);
    int Chunk = atoi(argv[2]);
    long long *f= malloc(sizeof(long long)*Anzahl);
#pragma omp parallel for numthreads(2) schedule(static,Chunk)
    for (long long i=0;i<Anzahl; i++){
        f[i]=0;
    }
    long long maxsearch=sqrt(Anzahl);
    for (long long i = 2; i<maxsearch; i++){
        if(f[i]==0){
            printf("%lli \n", i);
#pragma omp parallel for numthreads(2) schedule(static, Chunk)
            for (long long j = i*i; j< Anzahl; j=j+i){
                f[j]=-1;
            }
        }
    }
#pragma omp parallel for schedule numthreads(2) (static,Chunk)
    for (long long i = maxsearch+1; i<Anzahl; i++){
        if(f[i]==0){
            printf("%lli \n", i);
        }
    }
    double needed_time = difftime(time(NULL), start_time); // todo milliseconds would be nice
    printf("Finished after %f seconds!\n", needed_time);
    return 0;
}
  
