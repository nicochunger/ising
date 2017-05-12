#include "stdlib.h"
#include "stdio.h"
#include "time.h"

#include "metropolis.h"
#include "lattice.h"

int main(int argc, char **argv)
{
    int n = 32; //Tamano de red
    int *lattice = malloc(n * n * sizeof(int));
    float prob = 0.5;
    float T = 2;
    int niter = 20000;
    srand(time(NULL));
    fill_lattice(lattice, n, prob);
    printf("%d\n", energia(lattice,n));
    print_lattice(lattice, n);

    for (int i = 0; i < niter; i++)
    {
        metropolis(lattice, n, T);
    }

    printf("%d\n", energia(lattice,n));
    print_lattice(lattice, n);

    return 0;
}
