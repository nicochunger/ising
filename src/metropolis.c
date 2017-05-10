#include "metropolis.h"
#include "stdio.h"
#include "stdlib.h"
#include "math.h"

#define e 2.71828           // Constante matematica e

int metropolis(int *lattice, int n, float T)
{
    int idx, delta_e;
    float probabilidad;
    idx = pick_site(lattice,n);
    delta_e = flip(lattice, n, T, idx);

    probabilidad = pow(e,-delta_e/T);
    if(probabilidad > 1)
        probabilidad = 1;

    double rdom = ((double)rand()/(double)RAND_MAX);
    if(rdom>probabilidad)
        lattice[idx] *= -1;

    return 0;
}

int pick_site(int *lattice, int n)
{
    int site;
    double rdom = ((double)rand()/(double)RAND_MAX);
    site = rdom * n * n;
    return site;
}

int flip(int *lattice, int n, float T, int idx)
{
    /* Calcula el delta de energia del supuesto cambio */
    int en0, en1, delta_e;
    en0 = energia(lattice,n);
    lattice[idx] *= -1;
    en1 = energia(lattice,n);
    delta_e = en1 - en0;
    return delta_e;
}

int energia(int *lattice, int n)
{
    int i,j,E;
    E = 0;
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            if(i==n-1 && j==n-1) //Esquina inferior derecha
                E += lattice[i*n+j]*lattice[i*n] + lattice[i*n+j]*lattice[j];
            else if(j==n-1) //Lado derecho
                E += lattice[i*n+j]*lattice[i*n] + lattice[i*n+j]*lattice[(i+1)*n+j];
            else if(i==n-1)
                E += lattice[i*n+j]*lattice[i*n+(j+1)] + lattice[i*n+j]*lattice[j];
            else //resto
                E += lattice[i*n+j]*lattice[i*n+(j+1)] + lattice[i*n+j]*lattice[(i+1)*n+j];
        }
    }
    return -E;
}
