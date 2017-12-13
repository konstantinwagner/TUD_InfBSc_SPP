#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

#define LENGTH 1000000

int sum( int* a, unsigned length )
{
    int result = 0;

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

    for( unsigned i=0; i<length-offset; i++ )
    {
        a[i] = a2[i];
    }


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
    for( unsigned i=0; i<length; i++ )
    {
        a[i] = base + i * offset;
    }
}

int main()
{
	int result = 0;
	#pragma omp parallel shared(result)
    {
        #pragma omp single
		{
                int *a = malloc(LENGTH * sizeof(int));
				init(a, LENGTH, 1, 1);
				result = sum(a, LENGTH);
                shift(a, LENGTH, 1000);
				result += hash(a, LENGTH);
                free(a);			
		}
        #pragma omp single
		{              
				int *b = malloc(LENGTH * sizeof(int));
                init(b, LENGTH, 2, 2);				
				shift(b, LENGTH, 2);
                result += sum(b, LENGTH);
                result += hash(b, LENGTH);
                free(b);
		}
        #pragma omp single
		{
                int *c = malloc(LENGTH * sizeof(int));
                init(c, LENGTH, 1, 1);
				result += hash(c, LENGTH);
                free(c);
        }
		#pragma omp single
        {
                int *d = malloc(LENGTH * sizeof(int));
                init(d, LENGTH, 0, -1);				
                shift(d, LENGTH, 623);
                result += hash(d, LENGTH);						
                free(d);   
        }			
    }
    printf( "Result: %d\n", result );
	return 0;
}
