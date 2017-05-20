#include "lattice.h"
#include "stdio.h"
#include "stdlib.h"

int fill_lattice(int *lattice, int n, float p)
{
    
    int i;
    for(i=0;i<n*n;i++)
    {
        if(rand()<p*RAND_MAX)
            lattice[i] = 1;
        else
            lattice[i] = -1;
    }
    return 0;

    /*
    for(int i=0; i<n*n; i++)
    {
        if(i%2 == 0) lattice[i] = 1;
        else lattice[i] = -1;
    }
    return 0;
    */
}

int print_lattice(int *lattice, int n)
{
    /* Para los spines para abajo (-1) imprime un 0 para que la red imprimida
    se pueda leer mejor. Pero la red en serio tiene (-1) como debe ser. */
    int i,j;
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            if(lattice[i*n+j]<0)
                printf("%d ", 0);
            else
                printf("%d ", lattice[i*n+j]);
        }
        printf("\n");
    }
    printf("\n");
    return 0;
}
