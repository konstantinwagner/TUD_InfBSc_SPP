#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

#define LENGTH 1000000

int sum( int* a, unsigned length )
{
    int result = 0;

    #pragma omp parallel for reduction(+: result)
    for( unsigned i=0; i<length; i++ )
    {
        result += a[i];
    }
    return result;
}

void shift( int* a, unsigned length, unsigned offset )
{
    int* a2=a;
    for( unsigned i=0; i<length-offset; i++ )
    {
        a2[i] = a[i + offset];
    }

    #pragma omp parallel for
    for( unsigned i=0; i<length-offset; i++ )
    {
        a[i] = a2[i];
    }


    #pragma omp parallel for
    for( unsigned i=length-offset; i<length; i++){
        a[i] = 0;
    }

}

int hash( int* a, unsigned length )
{
    int hash = 1;
    for( unsigned i=0; i<length; i++ )
    {
        switch( hash % 3 )
	{
	case 0:
	  hash += a[i];
	  break;
	case 1:
	  hash *= a[i];
	  break;
	default:
	  hash -= a[i];
	}
	hash %= 1000;
    }
    return hash;
}

void init( int* a, unsigned length, int base, int offset )
{
    #pragma omp parallel for
    for( unsigned i=0; i<length; i++ )
    {
        a[i] = base + i * offset;
    }
}

int main()
{
    int *a = malloc(LENGTH * sizeof(int));
    int *b = malloc(LENGTH * sizeof(int));
    int *c = malloc(LENGTH * sizeof(int));
    int *d = malloc(LENGTH * sizeof(int));

    init(a, LENGTH, 1, 1);
    init(b, LENGTH, 2, 2);
    init(c, LENGTH, 1, 1);
    init(d, LENGTH, 0, -1);

    int result = sum(a, LENGTH);
    shift(a, LENGTH, 1000);
    result += hash(a, LENGTH);
    shift(b, LENGTH, 2);
    result += sum(b, LENGTH);
    result += hash(b, LENGTH);
    result += hash(c, LENGTH);
    shift(d, LENGTH, 623);
    result += hash(d, LENGTH);

    free(a);
    free(b);
    free(c);
    free(d);

    printf("Result: %d\n", result);
    return 0;
}
